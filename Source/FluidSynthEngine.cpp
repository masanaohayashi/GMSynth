#include "FluidSynthEngine.h"

#include <algorithm>

//==============================================================================
class FluidSynthEngine::ReclaimerThread final : public juce::Thread
{
public:
    explicit ReclaimerThread (FluidSynthEngine& ownerToUse)
        : juce::Thread ("FluidSynthReclaimer"), owner (ownerToUse)
    {
        startThread();
    }

    ~ReclaimerThread() override
    {
        stopThread (2000);
    }

private:
    void run() override
    {
        while (! threadShouldExit())
        {
            owner.reclaimRetired();
            wait (50);
        }

        owner.reclaimRetired();
    }

    FluidSynthEngine& owner;
};

//==============================================================================
FluidSynthEngine::SynthInstance::~SynthInstance()
{
    if (synth != nullptr)
        delete_fluid_synth (synth);

    if (settings != nullptr)
        delete_fluid_settings (settings);
}

FluidSynthEngine::FluidSynthEngine()
    : scratchBuffer (2, 1)
{
    for (auto& muted : channelMuted)
        muted.store (false, std::memory_order_relaxed);

    for (int channel = 0; channel < numMidiChannels; ++channel)
    {
        channelVolume[static_cast<size_t> (channel)].store (127, std::memory_order_relaxed);
        channelPan[static_cast<size_t> (channel)].store (64, std::memory_order_relaxed);
        channelBank[static_cast<size_t> (channel)].store (0, std::memory_order_relaxed);
        channelProgram[static_cast<size_t> (channel)].store (0, std::memory_order_relaxed);
    }

    appliedChannelMute.fill (false);
    appliedChannelVolume.fill (-1);
    appliedChannelPan.fill (-1);
    appliedChannelBank.fill (-1);
    appliedChannelProgram.fill (-1);
    reclaimerThread.reset (new ReclaimerThread (*this));
}

FluidSynthEngine::~FluidSynthEngine()
{
    // The host must have stopped calling processBlock before destroying the
    // processor. Stop the background reclaimer before touching its queue.
    reclaimerThread.reset();
    reclaimRetired();

    destroyChange (pendingChange.exchange (nullptr, std::memory_order_acq_rel));

    delete activeSynth;
    activeSynth = nullptr;
}

void FluidSynthEngine::prepare (double sampleRate, int samplesPerBlock)
{
    currentSampleRate.store (juce::jmax (1.0, sampleRate), std::memory_order_release);
    scratchBuffer.setSize (2, juce::jmax (1, samplesPerBlock), false, true, true);
}

std::unique_ptr<FluidSynthEngine::SynthInstance> FluidSynthEngine::createSynth (const juce::File& file,
                                                                                  double sampleRate,
                                                                                  juce::String& errorMessage)
{
    std::unique_ptr<SynthInstance> instance (new SynthInstance());

    instance->settings = new_fluid_settings();
    if (instance->settings == nullptr)
    {
        errorMessage = "FluidSynth could not create its settings.";
        return {};
    }

    if (fluid_settings_setnum (instance->settings, "synth.sample-rate", sampleRate) != FLUID_OK)
    {
        errorMessage = "FluidSynth rejected the requested sample rate.";
        return {};
    }

    instance->synth = new_fluid_synth (instance->settings);
    if (instance->synth == nullptr)
    {
        errorMessage = "FluidSynth could not create a synthesizer.";
        return {};
    }

    const auto soundFontId = fluid_synth_sfload (instance->synth,
                                                 file.getFullPathName().toRawUTF8(),
                                                 1);
    if (soundFontId < 0)
    {
        errorMessage = "FluidSynth could not load \"" + file.getFileName() + "\".";
        return {};
    }

    // General MIDI reserves channel 10 (zero-based channel 9) for drums.
    // Reassert the type after loading because the SoundFont load/reset path
    // is allowed to initialise channel presets and controller state.
    fluid_synth_set_channel_type (instance->synth, 9, CHANNEL_TYPE_DRUM);

    // Build the immutable bank/program index while the SoundFont is still on
    // the non-real-time loading path. Program changes can then resolve a
    // missing bank without searching or allocating on the audio thread.
    const auto soundFontCount = fluid_synth_sfcount (instance->synth);
    for (int soundFontIndex = 0; soundFontIndex < soundFontCount; ++soundFontIndex)
    {
        auto* soundFont = fluid_synth_get_sfont (instance->synth,
                                                 static_cast<unsigned int> (soundFontIndex));
        if (soundFont == nullptr)
            continue;

        const auto soundFontId = fluid_sfont_get_id (soundFont);
        const auto bankOffset = fluid_synth_get_bank_offset (instance->synth, soundFontId);

        fluid_sfont_iteration_start (soundFont);
        while (auto* preset = fluid_sfont_iteration_next (soundFont))
        {
            const auto bank = fluid_preset_get_banknum (preset) + bankOffset;
            const auto program = fluid_preset_get_num (preset);

            if (bank < 0 || bank > 16383 || program < 0 || program >= 128)
                continue;

            const PresetLocation location { soundFontId, bank, program };
            instance->presetsByProgram[static_cast<size_t> (program)].push_back (location);

            if (! instance->hasLowestPreset || bank < instance->lowestPreset.bank)
            {
                instance->lowestPreset = location;
                instance->hasLowestPreset = true;
            }

            // Bank 128 and above are the conventional SF2 percussion banks.
            // Prefer those for a drum channel, but keep the global fallback
            // available for SoundFonts that do not follow that convention.
            if (bank >= 128)
            {
                instance->percussionPresetsByProgram[static_cast<size_t> (program)].push_back (location);

                if (! instance->hasLowestPercussionPreset || bank < instance->lowestPercussionPreset.bank)
                {
                    instance->lowestPercussionPreset = location;
                    instance->hasLowestPercussionPreset = true;
                }
            }
        }
    }

    for (auto& presets : instance->presetsByProgram)
    {
        std::stable_sort (presets.begin(), presets.end(), [] (const auto& first, const auto& second)
        {
            return first.bank < second.bank;
        });
    }

    for (auto& presets : instance->percussionPresetsByProgram)
    {
        std::stable_sort (presets.begin(), presets.end(), [] (const auto& first, const auto& second)
        {
            return first.bank < second.bank;
        });
    }

    // Keep a little headroom for the plug-in's default output level.
    fluid_synth_set_gain (instance->synth, 0.8f);
    return instance;
}

juce::Result FluidSynthEngine::loadSoundFont (const juce::File& file)
{
    if (! file.existsAsFile())
        return juce::Result::fail ("The selected SoundFont file does not exist.");

    juce::String errorMessage;
    auto instance = createSynth (file, currentSampleRate.load (std::memory_order_acquire), errorMessage);
    if (instance == nullptr)
        return juce::Result::fail (errorMessage);

    // Configure the replacement before publishing it to the audio thread. The
    // audio-thread apply below remains the authoritative final pass, but this
    // removes the default-preset window that otherwise exists after sfload().
    initializeSynthChannelState (*instance);

    auto* change = new SynthChange();
    change->synth = instance.release();
    requestChange (change);
    return juce::Result::ok();
}

void FluidSynthEngine::clearSoundFont()
{
    requestChange (new SynthChange());
}

const FluidSynthEngine::PresetLocation* FluidSynthEngine::findPresetInBank (const std::vector<PresetLocation>& presets,
                                                                              int bank) noexcept
{
    const auto it = std::lower_bound (presets.begin(), presets.end(), bank,
                                      [] (const auto& preset, int bankToFind)
                                      {
                                          return preset.bank < bankToFind;
                                      });

    return it != presets.end() && it->bank == bank ? &*it : nullptr;
}

void FluidSynthEngine::applyProgramChangeToSynth (SynthInstance& instance,
                                                   int channel,
                                                   int program,
                                                   int requestedBank) noexcept
{
    if (instance.synth == nullptr
        || ! juce::isPositiveAndBelow (channel, numMidiChannels)
        || ! juce::isPositiveAndBelow (program, 128))
        return;

    const auto& allPresetsForProgram = instance.presetsByProgram[static_cast<size_t> (program)];
    const auto& percussionPresetsForProgram = instance.percussionPresetsByProgram[static_cast<size_t> (program)];
    const auto isPercussionChannel = channel == 9 || requestedBank >= 128;
    const auto& preferredPresets = isPercussionChannel
        ? percussionPresetsForProgram
        : allPresetsForProgram;

    // A GM drum channel must never select a melodic preset from bank 0. The
    // MIDI program number selects the drum kit (for example, 0 is Standard
    // Kit and 16 is the GM Power/Rock-style kit), while the preset itself
    // must come from the percussion bank.
    const auto& presetsForRequestedBank = isPercussionChannel
        ? percussionPresetsForProgram
        : allPresetsForProgram;

    // Select the exact preset when it exists. Using program_select here avoids
    // relying on the replacement synth's default bank/program after a reload.
    if (const auto* requestedPreset = findPresetInBank (presetsForRequestedBank, requestedBank);
        requestedPreset != nullptr)
    {
        if (fluid_synth_program_select (instance.synth,
                                        channel,
                                        requestedPreset->sfontId,
                                        requestedPreset->bank,
                                        requestedPreset->program) == FLUID_OK)
            return;

        fluid_synth_bank_select (instance.synth, channel, requestedBank);
        if (fluid_synth_program_change (instance.synth, channel, program) == FLUID_OK)
            return;
    }

    const PresetLocation* fallback = preferredPresets.empty() ? nullptr : &preferredPresets.front();

    if (fallback == nullptr)
    {
        if (isPercussionChannel && instance.hasLowestPercussionPreset)
            fallback = &instance.lowestPercussionPreset;
        else if (! isPercussionChannel && instance.hasLowestPreset)
            fallback = &instance.lowestPreset;
    }

    if (fallback == nullptr)
    {
        fluid_synth_program_change (instance.synth, channel, program);
        return;
    }

    if (fluid_synth_program_select (instance.synth,
                                    channel,
                                    fallback->sfontId,
                                    fallback->bank,
                                    fallback->program) == FLUID_OK)
    {
        // Keep the MIDI bank selection intact. This makes the next program
        // change resolve against the original requested bank again.
        if (requestedBank != fallback->bank)
            fluid_synth_bank_select (instance.synth, channel, requestedBank);
        return;
    }

    fluid_synth_program_change (instance.synth, channel, program);
}

void FluidSynthEngine::initializeSynthChannelState (SynthInstance& instance) noexcept
{
    if (instance.synth == nullptr)
        return;

    for (int channel = 0; channel < numMidiChannels; ++channel)
    {
        const auto index = static_cast<size_t> (channel);
        const auto muted = channelMuted[index].load (std::memory_order_acquire);
        const auto volume = juce::jlimit (0, 127, channelVolume[index].load (std::memory_order_acquire));
        const auto pan = juce::jlimit (0, 127, channelPan[index].load (std::memory_order_acquire));
        const auto bank = juce::jlimit (0, 16383, channelBank[index].load (std::memory_order_acquire));
        const auto program = juce::jlimit (0, 127, channelProgram[index].load (std::memory_order_acquire));

        fluid_synth_cc (instance.synth, channel, 7, muted ? 0 : volume);
        fluid_synth_cc (instance.synth, channel, 10, pan);
        fluid_synth_bank_select (instance.synth, channel, bank);

        int selectedSfont = 0;
        int selectedBank = bank;
        int selectedProgram = 0;
        fluid_synth_get_program (instance.synth,
                                 channel,
                                 &selectedSfont,
                                 &selectedBank,
                                 &selectedProgram);
        applyProgramChangeToSynth (instance, channel, program, selectedBank);
    }
}

void FluidSynthEngine::requestChange (SynthChange* change)
{
    destroyChange (pendingChange.exchange (change, std::memory_order_acq_rel));
}

void FluidSynthEngine::adoptPendingChange() noexcept
{
    if (pendingChange.load (std::memory_order_acquire) == nullptr
        || retiredFifo.getFreeSpace() == 0)
        return;

    auto* change = pendingChange.exchange (nullptr, std::memory_order_acq_rel);
    if (change == nullptr)
        return;

    auto* oldSynth = activeSynth;
    activeSynth = change->synth;
    channelStateNeedsApply = true;

    auto write = retiredFifo.write (1);
    if (write.blockSize1 > 0)
    {
        retiredChanges[write.startIndex1] = { oldSynth, change };
    }
    else if (write.blockSize2 > 0)
    {
        retiredChanges[write.startIndex2] = { oldSynth, change };
    }
}

void FluidSynthEngine::setChannelMuted (int channel, bool muted) noexcept
{
    if (juce::isPositiveAndBelow (channel, numMidiChannels))
        channelMuted[static_cast<size_t> (channel)].store (muted, std::memory_order_release);
}

bool FluidSynthEngine::isChannelMuted (int channel) const noexcept
{
    return juce::isPositiveAndBelow (channel, numMidiChannels)
        && channelMuted[static_cast<size_t> (channel)].load (std::memory_order_acquire);
}

FluidSynthEngine::ChannelState FluidSynthEngine::getChannelState (int channel) const noexcept
{
    ChannelState state;
    if (! juce::isPositiveAndBelow (channel, numMidiChannels))
        return state;

    const auto index = static_cast<size_t> (channel);
    state.volume = channelVolume[index].load (std::memory_order_acquire);
    state.pan = channelPan[index].load (std::memory_order_acquire);
    state.bank = channelBank[index].load (std::memory_order_acquire);
    state.program = channelProgram[index].load (std::memory_order_acquire);
    return state;
}

void FluidSynthEngine::setChannelVolume (int channel, int value) noexcept
{
    if (juce::isPositiveAndBelow (channel, numMidiChannels))
        channelVolume[static_cast<size_t> (channel)].store (juce::jlimit (0, 127, value),
                                                             std::memory_order_release);
}

void FluidSynthEngine::setChannelPan (int channel, int value) noexcept
{
    if (juce::isPositiveAndBelow (channel, numMidiChannels))
        channelPan[static_cast<size_t> (channel)].store (juce::jlimit (0, 127, value),
                                                          std::memory_order_release);
}

void FluidSynthEngine::setChannelBank (int channel, int value) noexcept
{
    if (juce::isPositiveAndBelow (channel, numMidiChannels))
        channelBank[static_cast<size_t> (channel)].store (juce::jlimit (0, 16383, value),
                                                           std::memory_order_release);
}

void FluidSynthEngine::setChannelProgram (int channel, int value) noexcept
{
    if (juce::isPositiveAndBelow (channel, numMidiChannels))
        channelProgram[static_cast<size_t> (channel)].store (juce::jlimit (0, 127, value),
                                                              std::memory_order_release);
}

void FluidSynthEngine::setMasterGain (float gain) noexcept
{
    masterGain.store (juce::jmax (0.0f, gain), std::memory_order_release);
}

float FluidSynthEngine::getMasterGain() const noexcept
{
    return masterGain.load (std::memory_order_acquire);
}

void FluidSynthEngine::resetChannelState (int channel) noexcept
{
    if (! juce::isPositiveAndBelow (channel, numMidiChannels))
        return;

    const auto index = static_cast<size_t> (channel);
    channelVolume[index].store (127, std::memory_order_release);
    channelPan[index].store (64, std::memory_order_release);
    channelBank[index].store (0, std::memory_order_release);
    channelProgram[index].store (0, std::memory_order_release);
}

void FluidSynthEngine::handleSysEx (const juce::uint8* data, int numBytes) noexcept
{
    if (data == nullptr || numBytes <= 0)
        return;

    const auto isGmReset = numBytes >= 4
        && data[0] == 0x7e
        && data[2] == 0x09
        && (data[3] == 0x01 || data[3] == 0x03);

    const auto isGsReset = numBytes >= 9
        && data[0] == 0x41
        && data[2] == 0x42
        && data[3] == 0x12
        && data[4] == 0x40
        && data[5] == 0x00
        && data[6] == 0x7f
        && data[7] == 0x00;

    if (! isGmReset && ! isGsReset)
        return;

    if (activeSynth != nullptr)
    {
        int handled = 0;
        fluid_synth_sysex (activeSynth->synth,
                           reinterpret_cast<const char*> (data),
                           numBytes,
                           nullptr,
                           nullptr,
                           &handled,
                           0);
        fluid_synth_set_channel_type (activeSynth->synth, 9, CHANNEL_TYPE_DRUM);
    }

    for (int channel = 0; channel < numMidiChannels; ++channel)
        resetChannelState (channel);

    channelStateNeedsApply = true;
}

void FluidSynthEngine::applyChannelState() noexcept
{
    if (activeSynth == nullptr)
        return;

    fluid_synth_set_channel_type (activeSynth->synth, 9, CHANNEL_TYPE_DRUM);

    const auto needsApply = channelStateNeedsApply;
    const auto desiredMasterGain = masterGain.load (std::memory_order_acquire);
    if (needsApply || desiredMasterGain != appliedMasterGain)
    {
        fluid_synth_set_gain (activeSynth->synth, desiredMasterGain);
        appliedMasterGain = desiredMasterGain;
    }

    for (int channel = 0; channel < numMidiChannels; ++channel)
    {
        const auto index = static_cast<size_t> (channel);
        const auto muted = channelMuted[index].load (std::memory_order_acquire);
        const auto volume = juce::jlimit (0, 127, channelVolume[index].load (std::memory_order_acquire));
        const auto pan = juce::jlimit (0, 127, channelPan[index].load (std::memory_order_acquire));
        const auto bank = juce::jlimit (0, 16383, channelBank[index].load (std::memory_order_acquire));
        const auto program = juce::jlimit (0, 127, channelProgram[index].load (std::memory_order_acquire));

        if (needsApply || volume != appliedChannelVolume[index]
            || muted != appliedChannelMute[index])
        {
            fluid_synth_cc (activeSynth->synth, channel, 7, muted ? 0 : volume);
            appliedChannelVolume[index] = volume;
            appliedChannelMute[index] = muted;
        }

        if (needsApply || pan != appliedChannelPan[index])
        {
            fluid_synth_cc (activeSynth->synth, channel, 10, pan);
            appliedChannelPan[index] = pan;
        }

        const auto bankChanged = needsApply || bank != appliedChannelBank[index];
        if (bankChanged)
        {
            fluid_synth_bank_select (activeSynth->synth, channel, bank);
            appliedChannelBank[index] = bank;
        }

        if (bankChanged || needsApply || program != appliedChannelProgram[index])
        {
            handleProgramChange (channel, program);
            appliedChannelProgram[index] = program;
        }
    }

    channelStateNeedsApply = false;
}

void FluidSynthEngine::handleProgramChange (int channel, int program) noexcept
{
    if (activeSynth == nullptr || ! juce::isPositiveAndBelow (program, 128))
        return;

    int currentSfont = 0;
    int requestedBank = 0;
    int currentProgram = 0;

    if (fluid_synth_get_program (activeSynth->synth,
                                 channel,
                                 &currentSfont,
                                 &requestedBank,
                                 &currentProgram) != FLUID_OK)
    {
        requestedBank = channelBank[static_cast<size_t> (channel)].load (std::memory_order_acquire);
    }

    applyProgramChangeToSynth (*activeSynth, channel, program, requestedBank);
}

void FluidSynthEngine::handleMidiMessage (const juce::MidiMessage& message) noexcept
{
    if (message.isSysEx())
    {
        handleSysEx (message.getSysExData(), message.getSysExDataSize());
        return;
    }

    const auto channel = message.getChannel() - 1;
    if (! juce::isPositiveAndBelow (channel, numMidiChannels))
        return;

    if (message.isNoteOn())
    {
        if (activeSynth != nullptr)
            fluid_synth_noteon (activeSynth->synth, channel, message.getNoteNumber(), message.getVelocity());
    }
    else if (message.isNoteOff())
    {
        if (activeSynth != nullptr)
            fluid_synth_noteoff (activeSynth->synth, channel, message.getNoteNumber());
    }
    else if (message.isController())
    {
        const auto controller = message.getControllerNumber();
        auto value = message.getControllerValue();
        const auto index = static_cast<size_t> (channel);

        if (message.isAllNotesOff())
        {
            if (activeSynth != nullptr)
                fluid_synth_all_notes_off (activeSynth->synth, channel);
            return;
        }

        if (message.isAllSoundOff())
        {
            if (activeSynth != nullptr)
                fluid_synth_all_sounds_off (activeSynth->synth, channel);
            return;
        }

        // This engine is a fixed 16-channel GM synth. FluidSynth treats
        // channel-mode messages (CC124-127) as basic-channel group commands;
        // for example, CC126 on channel 1 can disable channels 2-16. Keep
        // the channel routing stable and only perform the required cleanup.
        if (controller >= 124 && controller <= 127)
        {
            if (activeSynth != nullptr)
                fluid_synth_all_notes_off (activeSynth->synth, channel);
            return;
        }

        if (message.isResetAllControllers())
        {
            channelVolume[index].store (127, std::memory_order_release);
            channelPan[index].store (64, std::memory_order_release);
            if (activeSynth != nullptr)
                fluid_synth_cc (activeSynth->synth, channel, controller, value);
            channelStateNeedsApply = true;
            return;
        }

        if (controller == 0)
        {
            const auto currentBank = channelBank[index].load (std::memory_order_acquire);
            channelBank[index].store ((value << 7) | (currentBank & 0x7f),
                                      std::memory_order_release);
        }
        else if (controller == 32)
        {
            const auto currentBank = channelBank[index].load (std::memory_order_acquire);
            channelBank[index].store ((currentBank & 0x3f80) | value,
                                      std::memory_order_release);
        }

        if (controller == 7)
        {
            channelVolume[index].store (value, std::memory_order_release);

            if (channelMuted[index].load (std::memory_order_acquire))
                value = 0;
        }
        else if (controller == 10)
        {
            channelPan[index].store (message.getControllerValue(), std::memory_order_release);
        }

        if (activeSynth == nullptr)
            return;

        fluid_synth_cc (activeSynth->synth, channel, controller, value);
        if (channel == 9 && (controller == 0 || controller == 32))
            fluid_synth_set_channel_type (activeSynth->synth, 9, CHANNEL_TYPE_DRUM);
        if (controller == 7)
            appliedChannelVolume[index] = channelVolume[index].load (std::memory_order_acquire);
        else if (controller == 10)
            appliedChannelPan[index] = channelPan[index].load (std::memory_order_acquire);
        else if (controller == 0 || controller == 32)
            appliedChannelBank[index] = channelBank[index].load (std::memory_order_acquire);
    }
    else if (message.isProgramChange())
    {
        const auto program = message.getProgramChangeNumber();
        channelProgram[static_cast<size_t> (channel)].store (program, std::memory_order_release);
        if (activeSynth != nullptr)
        {
            handleProgramChange (channel, program);
            appliedChannelProgram[static_cast<size_t> (channel)] = program;
        }
    }
    else if (message.isPitchWheel())
    {
        if (activeSynth != nullptr)
            fluid_synth_pitch_bend (activeSynth->synth, channel, message.getPitchWheelValue());
    }
    else if (message.isChannelPressure())
    {
        if (activeSynth != nullptr)
            fluid_synth_channel_pressure (activeSynth->synth, channel, message.getChannelPressureValue());
    }
    else if (message.isAftertouch())
    {
        if (activeSynth != nullptr)
            fluid_synth_key_pressure (activeSynth->synth,
                                      channel,
                                      message.getNoteNumber(),
                                      message.getAfterTouchValue());
    }
}

void FluidSynthEngine::renderRange (const juce::MidiBuffer& midiMessages,
                                    int rangeStart,
                                    int rangeLength,
                                    float* left,
                                    float* right) noexcept
{
    if (activeSynth == nullptr || rangeLength <= 0)
        return;

    const auto rangeEnd = rangeStart + rangeLength;
    auto renderedUntil = rangeStart;

    for (const auto metadata : midiMessages)
    {
        if (metadata.samplePosition >= rangeEnd)
            break;

        // In the mono/no-output fallback this function is called once per
        // chunk. Events handled by an earlier chunk must not be replayed.
        if (rangeStart > 0 && metadata.samplePosition < rangeStart)
            continue;

        if (metadata.numBytes <= 0 || metadata.data == nullptr)
            continue;

        const auto eventPosition = juce::jmax (rangeStart, metadata.samplePosition);
        if (eventPosition > renderedUntil)
        {
            fluid_synth_write_float (activeSynth->synth,
                                     eventPosition - renderedUntil,
                                     left + (renderedUntil - rangeStart),
                                     0,
                                     1,
                                     right + (renderedUntil - rangeStart),
                                     0,
                                     1);
            renderedUntil = eventPosition;
        }

        if (metadata.data[0] == 0xf0)
        {
            if (metadata.numBytes >= 2 && metadata.data[metadata.numBytes - 1] == 0xf7)
                handleSysEx (metadata.data + 1, metadata.numBytes - 2);
        }
        else if (metadata.numBytes <= 4)
        {
            handleMidiMessage (juce::MidiMessage (metadata.data, metadata.numBytes));
        }
    }

    if (renderedUntil < rangeEnd)
    {
        fluid_synth_write_float (activeSynth->synth,
                                 rangeEnd - renderedUntil,
                                 left + (renderedUntil - rangeStart),
                                 0,
                                 1,
                                 right + (renderedUntil - rangeStart),
                                 0,
                                 1);
    }
}

void FluidSynthEngine::processBlock (juce::AudioBuffer<float>& buffer,
                                     const juce::MidiBuffer& midiMessages,
                                     const juce::MidiMessage* keyboardMessages,
                                     int numKeyboardMessages) noexcept
{
    adoptPendingChange();
    buffer.clear();

    if (activeSynth == nullptr)
    {
        for (const auto metadata : midiMessages)
        {
            if (metadata.numBytes <= 0 || metadata.data == nullptr)
                continue;

            if (metadata.data[0] == 0xf0)
            {
                if (metadata.numBytes >= 2 && metadata.data[metadata.numBytes - 1] == 0xf7)
                    handleSysEx (metadata.data + 1, metadata.numBytes - 2);
            }
            else if (metadata.numBytes <= 4)
            {
                handleMidiMessage (juce::MidiMessage (metadata.data, metadata.numBytes));
            }
        }

        for (int i = 0; i < numKeyboardMessages; ++i)
            handleMidiMessage (keyboardMessages[i]);

        return;
    }

    applyChannelState();

    for (int i = 0; i < numKeyboardMessages; ++i)
        handleMidiMessage (keyboardMessages[i]);

    const auto numSamples = buffer.getNumSamples();
    if (numSamples <= 0)
        return;

    if (buffer.getNumChannels() >= 2)
    {
        renderRange (midiMessages,
                     0,
                     numSamples,
                     buffer.getWritePointer (0),
                     buffer.getWritePointer (1));
        return;
    }

    const auto chunkCapacity = juce::jmax (1, scratchBuffer.getNumSamples());
    for (int offset = 0; offset < numSamples; offset += chunkCapacity)
    {
        const auto chunkSize = juce::jmin (chunkCapacity, numSamples - offset);
        scratchBuffer.clear (0, 0, chunkSize);
        scratchBuffer.clear (1, 0, chunkSize);
        renderRange (midiMessages,
                     offset,
                     chunkSize,
                     scratchBuffer.getWritePointer (0),
                     scratchBuffer.getWritePointer (1));

        if (buffer.getNumChannels() == 1)
            buffer.copyFrom (0, offset, scratchBuffer, 0, 0, chunkSize);
    }
}

void FluidSynthEngine::reclaimRetired() noexcept
{
    auto read = retiredFifo.read (maxRetiredChanges);

    for (int i = 0; i < read.blockSize1; ++i)
    {
        auto& retired = retiredChanges[read.startIndex1 + i];
        delete retired.synth;
        delete retired.change;
        retired = {};
    }

    for (int i = 0; i < read.blockSize2; ++i)
    {
        auto& retired = retiredChanges[read.startIndex2 + i];
        delete retired.synth;
        delete retired.change;
        retired = {};
    }
}

void FluidSynthEngine::destroyChange (SynthChange* change) noexcept
{
    if (change == nullptr)
        return;

    delete change->synth;
    delete change;
}
