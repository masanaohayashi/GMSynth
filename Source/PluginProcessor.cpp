/*
  ================================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ================================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SecurityScopedFile.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <thread>

class GMSynthAudioProcessor::MidiLogTimer final : private juce::Timer
{
public:
    explicit MidiLogTimer (GMSynthAudioProcessor& ownerToUse)
        : owner (ownerToUse)
    {
    }

    ~MidiLogTimer() override
    {
        stopTimer();
    }

    void start()
    {
        startTimer (20);
    }

    void stop()
    {
        stopTimer();
    }

private:
    void timerCallback() override
    {
        owner.drainMidiLogQueue();
    }

    GMSynthAudioProcessor& owner;
};

//==============================================================================
GMSynthAudioProcessor::GMSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input", juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

GMSynthAudioProcessor::~GMSynthAudioProcessor()
{
    if (midiLogTimer != nullptr)
        midiLogTimer->stop();

    midiLoggingActive.store (false, std::memory_order_release);
    midiLogSession.fetch_add (1, std::memory_order_acq_rel);
    while (midiLogWriters.load (std::memory_order_acquire) != 0)
        std::this_thread::yield();

    discardMidiLogQueue();
}

//==============================================================================
const juce::String GMSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GMSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GMSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GMSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GMSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GMSynthAudioProcessor::getNumPrograms()
{
    return 1;
}

int GMSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GMSynthAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String GMSynthAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void GMSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void GMSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    processingSampleRate.store (juce::jmax (1.0, sampleRate), std::memory_order_release);
    synthEngine.prepare (sampleRate, samplesPerBlock);

    juce::String path;
    juce::String bookmarkData;
    {
        const juce::ScopedLock lock (stateLock);
        path = soundFontPath;
        bookmarkData = soundFontBookmark;
    }

    if (path.isNotEmpty())
        restoreSoundFontFromPath (path, bookmarkData);
}

void GMSynthAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GMSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GMSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    int numKeyboardMessages = 0;
    auto read = keyboardMidiFifo.read (keyboardQueueSize - 1);
    for (int i = 0; i < read.blockSize1; ++i)
    {
        keyboardMessagesForBlock[static_cast<size_t> (numKeyboardMessages++)]
            = keyboardMidiQueue[static_cast<size_t> (read.startIndex1 + i)];
    }

    for (int i = 0; i < read.blockSize2; ++i)
    {
        keyboardMessagesForBlock[static_cast<size_t> (numKeyboardMessages++)]
            = keyboardMidiQueue[static_cast<size_t> (read.startIndex2 + i)];
    }

    const auto currentSession = midiLogSession.load (std::memory_order_acquire);
    if (currentSession != audioMidiLogSession)
    {
        audioMidiLogSession = currentSession;
        audioMidiLogFramePosition = 0;
    }

    auto loggingThisBlock = midiLoggingActive.load (std::memory_order_acquire);
    if (loggingThisBlock)
    {
        midiLogWriters.fetch_add (1, std::memory_order_acq_rel);
        if (! midiLoggingActive.load (std::memory_order_acquire)
            || midiLogSession.load (std::memory_order_acquire) != currentSession)
        {
            midiLogWriters.fetch_sub (1, std::memory_order_release);
            loggingThisBlock = false;
        }
    }

    if (loggingThisBlock)
    {
        const auto blockSize = buffer.getNumSamples();
        for (const auto metadata : midiMessages)
        {
            recordMidiLogMessage (metadata.data,
                                  metadata.numBytes,
                                  metadata.samplePosition,
                                  blockSize,
                                  audioMidiLogFramePosition,
                                  0,
                                  currentSession);
        }

        for (int i = 0; i < numKeyboardMessages; ++i)
        {
            const auto& message = keyboardMessagesForBlock[static_cast<size_t> (i)];
            recordMidiLogMessage (message.getRawData(),
                                  message.getRawDataSize(),
                                  0,
                                  blockSize,
                                  audioMidiLogFramePosition,
                                  1,
                                  currentSession);
        }
    }

    synthEngine.processBlock (buffer,
                              midiMessages,
                              keyboardMessagesForBlock.data(),
                              numKeyboardMessages);

    if (loggingThisBlock)
    {
        audioMidiLogFramePosition += juce::jmax (0, buffer.getNumSamples());
        midiLogWriters.fetch_sub (1, std::memory_order_release);
    }
}

//==============================================================================
bool GMSynthAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* GMSynthAudioProcessor::createEditor()
{
    return new GMSynthAudioProcessorEditor (*this);
}

//==============================================================================
void GMSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::XmlElement state ("GMSynthState");
    state.setAttribute ("version", 3);

    {
        const juce::ScopedLock lock (stateLock);
        state.setAttribute ("soundFontPath", soundFontPath);
        state.setAttribute ("soundFontBookmark", soundFontBookmark);
    }

    for (int channel = 0; channel < 16; ++channel)
    {
        state.setAttribute ("channelMute" + juce::String (channel + 1), isChannelMuted (channel));

        const auto channelState = getChannelState (channel);
        state.setAttribute ("channelVolume" + juce::String (channel + 1), channelState.volume);
        state.setAttribute ("channelPan" + juce::String (channel + 1), channelState.pan);
        state.setAttribute ("channelBank" + juce::String (channel + 1), channelState.bank);
        state.setAttribute ("channelProgram" + juce::String (channel + 1), channelState.program);
    }

    state.setAttribute ("masterVolumeDb", getMasterVolumeDb());

    copyXmlToBinary (state, destData);
}

void GMSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> state (getXmlFromBinary (data, sizeInBytes));
    if (state == nullptr || ! state->hasTagName ("GMSynthState"))
        return;

    const auto version = state->getIntAttribute ("version", 1);
    if (version < 1 || version > 3)
        return;

    const auto path = state->getStringAttribute ("soundFontPath");
    const auto bookmarkData = state->getStringAttribute ("soundFontBookmark");
    {
        const juce::ScopedLock lock (stateLock);
        soundFontPath = path;
        soundFontBookmark = bookmarkData;
    }

    for (int channel = 0; channel < 16; ++channel)
    {
        const auto attributeName = "channelMute" + juce::String (channel + 1);
        setChannelMuted (channel, state->getBoolAttribute (attributeName, false));

        if (version >= 3)
        {
            setChannelVolume (channel,
                              state->getIntAttribute ("channelVolume" + juce::String (channel + 1), 127));
            setChannelPan (channel,
                           state->getIntAttribute ("channelPan" + juce::String (channel + 1), 64));
            setChannelBank (channel,
                            state->getIntAttribute ("channelBank" + juce::String (channel + 1), 0));
            setChannelProgram (channel,
                               state->getIntAttribute ("channelProgram" + juce::String (channel + 1), 0));
        }
    }

    if (version >= 3)
        setMasterVolumeDb (state->getDoubleAttribute ("masterVolumeDb", getMasterVolumeDb()));

    restoreSoundFontFromPath (path, bookmarkData);
}

juce::Result GMSynthAudioProcessor::loadSoundFontFile (const juce::File& file)
{
    GMSynthSecurity::ScopedSoundFontFileAccess access (file, {});
    if (! access.isUsable())
        return juce::Result::fail ("The selected SoundFont file is not accessible.");

    const auto bookmarkData = GMSynthSecurity::createSecurityScopedBookmark (access.getFile());
    const auto result = synthEngine.loadSoundFont (access.getFile());
    if (result.wasOk())
    {
        {
            const juce::ScopedLock lock (stateLock);
            soundFontPath = access.getFile().getFullPathName();
            soundFontBookmark = bookmarkData;
        }

        notifyHostOfSoundFontStateChange();
    }

    return result;
}

void GMSynthAudioProcessor::notifyHostOfSoundFontStateChange()
{
    // JUCE's AUv3 wrapper currently does not act on nonParameterStateChanged,
    // but it does invalidate the AU state when programChanged is reported.
    // Send both flags so hosts with native non-parameter-state support and
    // the current JUCE AUv3 wrapper receive the change notification.
    updateHostDisplay (juce::AudioProcessor::ChangeDetails{}
                           .withNonParameterStateChanged (true)
                           .withProgramChanged (true));
}

juce::String GMSynthAudioProcessor::getSoundFontPath() const
{
    const juce::ScopedLock lock (stateLock);
    return soundFontPath;
}

void GMSynthAudioProcessor::setChannelMuted (int channel, bool muted) noexcept
{
    synthEngine.setChannelMuted (channel, muted);
}

bool GMSynthAudioProcessor::isChannelMuted (int channel) const noexcept
{
    return synthEngine.isChannelMuted (channel);
}

FluidSynthEngine::ChannelState GMSynthAudioProcessor::getChannelState (int channel) const noexcept
{
    return synthEngine.getChannelState (channel);
}

void GMSynthAudioProcessor::setChannelVolume (int channel, int value) noexcept
{
    synthEngine.setChannelVolume (channel, value);
}

void GMSynthAudioProcessor::setChannelPan (int channel, int value) noexcept
{
    synthEngine.setChannelPan (channel, value);
}

void GMSynthAudioProcessor::setChannelBank (int channel, int value) noexcept
{
    synthEngine.setChannelBank (channel, value);
}

void GMSynthAudioProcessor::setChannelProgram (int channel, int value) noexcept
{
    synthEngine.setChannelProgram (channel, value);
}

void GMSynthAudioProcessor::setMasterVolumeDb (float decibels) noexcept
{
    const auto clampedDecibels = juce::jlimit (-96.0f, 0.0f, decibels);
    synthEngine.setMasterGain (juce::Decibels::decibelsToGain (clampedDecibels, -96.0f));
}

float GMSynthAudioProcessor::getMasterVolumeDb() const noexcept
{
    return juce::jmax (-96.0f,
                       juce::Decibels::gainToDecibels (synthEngine.getMasterGain(), -96.0f));
}

bool GMSynthAudioProcessor::isMidiLogging() const noexcept
{
    return midiLoggingActive.load (std::memory_order_acquire);
}

void GMSynthAudioProcessor::startMidiLogging()
{
    if (midiLoggingActive.load (std::memory_order_acquire))
        return;

    midiLoggingActive.store (false, std::memory_order_release);
    midiLogSession.fetch_add (1, std::memory_order_acq_rel);
    while (midiLogWriters.load (std::memory_order_acquire) != 0)
        std::this_thread::yield();

    discardMidiLogQueue();
    midiLogEvents.clear();
    midiLogDroppedCount.store (0, std::memory_order_release);
    midiLogStartTime = juce::Time::getCurrentTime();
    midiLogSampleRate = juce::jmax (1.0, processingSampleRate.load (std::memory_order_acquire));
    midiLogSession.fetch_add (1, std::memory_order_acq_rel);
    midiLogRecordingSession = midiLogSession.load (std::memory_order_acquire);
    lastMidiLogFile = juce::File();

    if (midiLogTimer == nullptr)
        midiLogTimer = std::make_unique<MidiLogTimer> (*this);

    midiLogTimer->start();
    midiLoggingActive.store (true, std::memory_order_release);
}

juce::Result GMSynthAudioProcessor::stopMidiLoggingAndSave()
{
    if (! midiLoggingActive.load (std::memory_order_acquire))
        return juce::Result::fail ("MIDI logging is not active.");

    midiLoggingActive.store (false, std::memory_order_release);
    midiLogSession.fetch_add (1, std::memory_order_acq_rel);
    while (midiLogWriters.load (std::memory_order_acquire) != 0)
        std::this_thread::yield();

    if (midiLogTimer != nullptr)
        midiLogTimer->stop();

    drainMidiLogQueue();
    midiLogRecordingSession = 0;
    return writeMidiLogFile();
}

juce::String GMSynthAudioProcessor::getLastMidiLogPath() const
{
    return lastMidiLogFile.getFullPathName();
}

void GMSynthAudioProcessor::recordMidiLogMessage (const juce::uint8* data,
                                                   int numBytes,
                                                   int samplePosition,
                                                   int blockSize,
                                                   juce::int64 blockFrameStart,
                                                   std::uint8_t source,
                                                   std::uint64_t session) noexcept
{
    auto write = midiLogFifo.write (1);
    if (write.blockSize1 <= 0 && write.blockSize2 <= 0)
    {
        midiLogDroppedCount.fetch_add (1, std::memory_order_relaxed);
        return;
    }

    auto& event = write.blockSize1 > 0
                    ? midiLogQueue[static_cast<size_t> (write.startIndex1)]
                    : midiLogQueue[static_cast<size_t> (write.startIndex2)];

    event.session = session;
    event.framePosition = blockFrameStart + static_cast<juce::int64> (samplePosition);
    event.samplePosition = samplePosition;
    event.blockSize = blockSize;
    event.numBytes = juce::jmax (0, numBytes);
    event.storedBytes = data == nullptr
                          ? 0
                          : juce::jmin (event.numBytes, maxMidiLogBytes);
    event.source = source;
    event.truncated = event.storedBytes < event.numBytes;

    if (event.storedBytes > 0)
        std::memcpy (event.data.data(), data, static_cast<size_t> (event.storedBytes));
}

void GMSynthAudioProcessor::drainMidiLogQueue()
{
    auto read = midiLogFifo.read (midiLogQueueSize);
    const auto consume = [this] (int startIndex, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            const auto& event = midiLogQueue[static_cast<size_t> (startIndex + i)];
            if (event.session == midiLogRecordingSession)
                midiLogEvents.push_back (event);
        }
    };

    consume (read.startIndex1, read.blockSize1);
    consume (read.startIndex2, read.blockSize2);
}

void GMSynthAudioProcessor::discardMidiLogQueue() noexcept
{
    auto read = midiLogFifo.read (midiLogQueueSize);
    juce::ignoreUnused (read);
}

juce::Result GMSynthAudioProcessor::writeMidiLogFile()
{
    const auto writeToDirectory = [this] (const juce::File& directory) -> juce::Result
    {
        if (! directory.isDirectory() && directory.createDirectory().failed())
            return juce::Result::fail ("Could not create the MIDI log directory.");

        const auto baseName = "GMSynth_MIDI_Log_"
                            + midiLogStartTime.formatted ("%Y%m%d_%H%M%S");
        const auto file = directory.getNonexistentChildFile (baseName, ".csv", false);
        auto stream = file.createOutputStream();
        if (stream == nullptr || ! stream->openedOk())
            return juce::Result::fail ("Could not open the MIDI log file for writing.");

        const auto droppedCount = midiLogDroppedCount.load (std::memory_order_acquire);
        if (! stream->writeText ("# GMSynth MIDI log\n", false, false, nullptr)
            || ! stream->writeText ("# dropped_events=" + juce::String (droppedCount) + "\n",
                                    false,
                                    false,
                                    nullptr)
            || ! stream->writeText ("timestamp,frame,block_sample_position,block_size,source,num_bytes,stored_bytes,truncated,data_hex\n",
                                    false,
                                    false,
                                    nullptr))
            return juce::Result::fail ("Could not write the MIDI log header.");

        for (const auto& event : midiLogEvents)
        {
            const auto timestampMilliseconds = midiLogStartTime.toMilliseconds()
                                             + static_cast<juce::int64> (std::llround (
                                                   static_cast<double> (event.framePosition)
                                                   * 1000.0
                                                   / midiLogSampleRate));
            const auto timestamp = juce::Time (timestampMilliseconds).toISO8601 (true);
            const auto source = event.source == 0 ? "Host" : "Keyboard";
            const auto dataHex = juce::String::toHexString (event.data.data(),
                                                             event.storedBytes,
                                                             1);
            const auto line = timestamp + ","
                            + juce::String (event.framePosition) + ","
                            + juce::String (event.samplePosition) + ","
                            + juce::String (event.blockSize) + ","
                            + source + ","
                            + juce::String (event.numBytes) + ","
                            + juce::String (event.storedBytes) + ","
                            + (event.truncated ? "1" : "0") + ","
                            + dataHex + "\n";

            if (! stream->writeText (line, false, false, nullptr))
                return juce::Result::fail ("Could not write the MIDI log data.");
        }

        stream->flush();
        if (! stream->getStatus().wasOk())
            return juce::Result::fail ("Could not finish writing the MIDI log file.");

        lastMidiLogFile = file;
        return juce::Result::ok();
    };

    const auto downloads = juce::File::getSpecialLocation (juce::File::userHomeDirectory)
                             .getChildFile ("Downloads");
    auto result = writeToDirectory (downloads);
    if (result.wasOk())
        return result;

    const auto fallbackDirectory = juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory)
                                     .getChildFile ("GMSynth");
    const auto fallbackResult = writeToDirectory (fallbackDirectory);
    if (fallbackResult.wasOk())
        return fallbackResult;

    return juce::Result::fail (result.getErrorMessage() + " " + fallbackResult.getErrorMessage());
}

void GMSynthAudioProcessor::enqueueKeyboardMidiMessage (const juce::MidiMessage& message) noexcept
{
    auto write = keyboardMidiFifo.write (1);
    if (write.blockSize1 > 0)
        keyboardMidiQueue[static_cast<size_t> (write.startIndex1)] = message;
    else if (write.blockSize2 > 0)
        keyboardMidiQueue[static_cast<size_t> (write.startIndex2)] = message;
}

void GMSynthAudioProcessor::restoreSoundFontFromPath (const juce::String& path,
                                                       const juce::String& bookmarkData)
{
    if (path.isEmpty())
    {
        synthEngine.clearSoundFont();
        return;
    }

    GMSynthSecurity::ScopedSoundFontFileAccess access (juce::File (path), bookmarkData);
    if (! access.isUsable())
    {
        synthEngine.clearSoundFont();
        return;
    }

    const auto result = synthEngine.loadSoundFont (access.getFile());
    if (result.wasOk())
    {
        auto refreshedBookmark = access.getRefreshedBookmark();
        if (refreshedBookmark.isEmpty())
            refreshedBookmark = GMSynthSecurity::createSecurityScopedBookmark (access.getFile());

        const juce::ScopedLock lock (stateLock);
        soundFontPath = access.getFile().getFullPathName();
        if (refreshedBookmark.isNotEmpty())
            soundFontBookmark = refreshedBookmark;
    }
    else
    {
        synthEngine.clearSoundFont();
    }
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GMSynthAudioProcessor();
}
