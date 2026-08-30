/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FluidSynthEngine.h"

#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <vector>

//==============================================================================
/**
*/
class GMSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    GMSynthAudioProcessor();
    ~GMSynthAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::Result loadSoundFontFile (const juce::File& file);
    juce::String getSoundFontPath() const;

    void setChannelMuted (int channel, bool muted) noexcept;
    bool isChannelMuted (int channel) const noexcept;

    FluidSynthEngine::ChannelState getChannelState (int channel) const noexcept;
    void setChannelVolume (int channel, int value) noexcept;
    void setChannelPan (int channel, int value) noexcept;
    void setChannelBank (int channel, int value) noexcept;
    void setChannelProgram (int channel, int value) noexcept;

    void setMasterVolumeDb (float decibels) noexcept;
    float getMasterVolumeDb() const noexcept;

    bool isMidiLogging() const noexcept;
    void startMidiLogging();
    juce::Result stopMidiLoggingAndSave();
    juce::String getLastMidiLogPath() const;

    void enqueueKeyboardMidiMessage (const juce::MidiMessage& message) noexcept;

private:
    //==============================================================================
    static constexpr int keyboardQueueSize = 128;
    static constexpr int midiLogQueueSize = 16384;
    static constexpr int maxMidiLogBytes = 1024;

    struct MidiLogEvent
    {
        std::uint64_t session = 0;
        juce::int64 framePosition = 0;
        int samplePosition = 0;
        int blockSize = 0;
        int numBytes = 0;
        int storedBytes = 0;
        std::uint8_t source = 0;
        bool truncated = false;
        std::array<juce::uint8, maxMidiLogBytes> data {};
    };

    class MidiLogTimer;

    void restoreSoundFontFromPath (const juce::String& path,
                                   const juce::String& bookmarkData);
    void notifyHostOfSoundFontStateChange();
    void recordMidiLogMessage (const juce::uint8* data,
                               int numBytes,
                               int samplePosition,
                               int blockSize,
                               juce::int64 blockFrameStart,
                               std::uint8_t source,
                               std::uint64_t session) noexcept;
    void drainMidiLogQueue();
    void discardMidiLogQueue() noexcept;
    juce::Result writeMidiLogFile();

    FluidSynthEngine synthEngine;
    juce::CriticalSection stateLock;
    juce::String soundFontPath;
    juce::String soundFontBookmark;

    juce::AbstractFifo keyboardMidiFifo { keyboardQueueSize };
    std::array<juce::MidiMessage, keyboardQueueSize> keyboardMidiQueue;
    std::array<juce::MidiMessage, keyboardQueueSize> keyboardMessagesForBlock;

    std::atomic<bool> midiLoggingActive { false };
    std::atomic<std::uint64_t> midiLogSession { 0 };
    std::atomic<int> midiLogWriters { 0 };
    std::atomic<std::uint64_t> midiLogDroppedCount { 0 };
    std::atomic<double> processingSampleRate { 44100.0 };
    juce::AbstractFifo midiLogFifo { midiLogQueueSize };
    std::array<MidiLogEvent, midiLogQueueSize> midiLogQueue;
    std::vector<MidiLogEvent> midiLogEvents;
    std::unique_ptr<MidiLogTimer> midiLogTimer;
    std::uint64_t midiLogRecordingSession = 0;
    juce::Time midiLogStartTime;
    double midiLogSampleRate = 44100.0;
    juce::File lastMidiLogFile;
    std::uint64_t audioMidiLogSession = 0;
    juce::int64 audioMidiLogFramePosition = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GMSynthAudioProcessor)
};
