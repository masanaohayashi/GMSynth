#pragma once

#include <JuceHeader.h>
#include <fluidsynth.h>

#include <array>
#include <atomic>
#include <memory>
#include <vector>

class FluidSynthEngine
{
public:
    FluidSynthEngine();
    ~FluidSynthEngine();

    void prepare (double sampleRate, int samplesPerBlock);

    // Loading and clearing are intentionally non-real-time operations. The
    // newly-created synth is handed to the audio thread at the next block
    // boundary.
    juce::Result loadSoundFont (const juce::File& file);
    void clearSoundFont();

    void processBlock (juce::AudioBuffer<float>& buffer,
                       const juce::MidiBuffer& midiMessages,
                       const juce::MidiMessage* keyboardMessages,
                       int numKeyboardMessages) noexcept;

    void setChannelMuted (int channel, bool muted) noexcept;
    bool isChannelMuted (int channel) const noexcept;

    struct ChannelState
    {
        int volume = 127;
        int pan = 64;
        int bank = 0;
        int program = 0;
    };

    ChannelState getChannelState (int channel) const noexcept;
    void setChannelVolume (int channel, int value) noexcept;
    void setChannelPan (int channel, int value) noexcept;
    void setChannelBank (int channel, int value) noexcept;
    void setChannelProgram (int channel, int value) noexcept;

    void setMasterGain (float gain) noexcept;
    float getMasterGain() const noexcept;

private:
    struct PresetLocation
    {
        int sfontId = 0;
        int bank = 0;
        int program = 0;
    };

    struct SynthInstance
    {
        fluid_settings_t* settings = nullptr;
        fluid_synth_t* synth = nullptr;

        std::array<std::vector<PresetLocation>, 128> presetsByProgram;
        std::array<std::vector<PresetLocation>, 128> percussionPresetsByProgram;
        PresetLocation lowestPreset;
        PresetLocation lowestPercussionPreset;
        bool hasLowestPreset = false;
        bool hasLowestPercussionPreset = false;

        ~SynthInstance();
    };

    struct SynthChange
    {
        SynthInstance* synth = nullptr;
    };

    struct RetiredChange
    {
        SynthInstance* synth = nullptr;
        SynthChange* change = nullptr;
    };

    class ReclaimerThread;

    enum
    {
        numMidiChannels = 16,
        maxRetiredChanges = 8
    };

    static std::unique_ptr<SynthInstance> createSynth (const juce::File& file,
                                                        double sampleRate,
                                                        juce::String& errorMessage);
    static void destroyChange (SynthChange* change) noexcept;
    static const PresetLocation* findPresetInBank (const std::vector<PresetLocation>& presets,
                                                   int bank) noexcept;
    static void applyProgramChangeToSynth (SynthInstance& instance,
                                           int channel,
                                           int program,
                                           int requestedBank) noexcept;

    void requestChange (SynthChange* change);
    void adoptPendingChange() noexcept;
    void initializeSynthChannelState (SynthInstance& instance) noexcept;
    void applyChannelState() noexcept;
    void handleMidiMessage (const juce::MidiMessage& message) noexcept;
    void handleProgramChange (int channel, int program) noexcept;
    void handleSysEx (const juce::uint8* data, int numBytes) noexcept;
    void resetChannelState (int channel) noexcept;
    void renderRange (const juce::MidiBuffer& midiMessages,
                      int rangeStart,
                      int rangeLength,
                      float* left,
                      float* right) noexcept;
    void reclaimRetired() noexcept;

    std::atomic<SynthChange*> pendingChange { nullptr };
    std::atomic<double> currentSampleRate { 44100.0 };
    std::array<std::atomic<bool>, numMidiChannels> channelMuted;
    std::array<std::atomic<int>, numMidiChannels> channelVolume;
    std::array<std::atomic<int>, numMidiChannels> channelPan;
    std::array<std::atomic<int>, numMidiChannels> channelBank;
    std::array<std::atomic<int>, numMidiChannels> channelProgram;
    std::atomic<float> masterGain { 0.8f };

    juce::AbstractFifo retiredFifo { maxRetiredChanges };
    std::array<RetiredChange, maxRetiredChanges> retiredChanges;
    std::unique_ptr<ReclaimerThread> reclaimerThread;

    SynthInstance* activeSynth = nullptr;
    bool channelStateNeedsApply = true;
    std::array<bool, numMidiChannels> appliedChannelMute;
    std::array<int, numMidiChannels> appliedChannelVolume;
    std::array<int, numMidiChannels> appliedChannelPan;
    std::array<int, numMidiChannels> appliedChannelBank;
    std::array<int, numMidiChannels> appliedChannelProgram;
    float appliedMasterGain = 0.8f;
    juce::AudioBuffer<float> scratchBuffer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FluidSynthEngine)
};
