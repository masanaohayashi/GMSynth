/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 9.0.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GMSynthAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                     public juce::Button::Listener,
                                     public juce::Slider::Listener,
                                     public juce::MidiKeyboardState::Listener
{
public:
    //==============================================================================
    GMSynthAudioProcessorEditor (GMSynthAudioProcessor& p);
    ~GMSynthAudioProcessorEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void configureChannelButton (juce::TextButton& button, int channel);
    void updateSoundFontLabel();
    void chooseSoundFont();
    void updateChannelStateControls();
    void configureChannelStateLabels();
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GMSynthAudioProcessor& audioProcessor;
    std::unique_ptr<juce::FileChooser> soundFontChooser;

    class StateUpdateTimer final : private juce::Timer
    {
    public:
        explicit StateUpdateTimer (GMSynthAudioProcessorEditor& ownerToUse)
            : owner (ownerToUse)
        {
        }

        ~StateUpdateTimer() override
        {
            stopTimer();
        }

        void start()
        {
            startTimerHz (30);
        }

    private:
        void timerCallback() override
        {
            owner.updateChannelStateControls();
            owner.updateSoundFontLabel();
        }

        GMSynthAudioProcessorEditor& owner;
    };

    std::unique_ptr<StateUpdateTimer> stateUpdateTimer;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> labelVolume;
    std::unique_ptr<juce::TextButton> buttonSelectSF2;
    std::unique_ptr<juce::Label> labelSoundFontCaption;
    std::unique_ptr<juce::Label> labelSoundFontName;
    std::unique_ptr<juce::Slider> sliderVolume;
    juce::MidiKeyboardState juce__midiKeyboardComponentState;
    std::unique_ptr<juce::MidiKeyboardComponent> juce__midiKeyboardComponent;
    std::unique_ptr<juce::TextButton> buttonCh1;
    std::unique_ptr<juce::TextButton> buttonCh2;
    std::unique_ptr<juce::TextButton> buttonCh3;
    std::unique_ptr<juce::TextButton> buttonCh4;
    std::unique_ptr<juce::TextButton> buttonCh5;
    std::unique_ptr<juce::TextButton> buttonCh6;
    std::unique_ptr<juce::TextButton> buttonCh7;
    std::unique_ptr<juce::TextButton> buttonCh8;
    std::unique_ptr<juce::TextButton> buttonCh9;
    std::unique_ptr<juce::TextButton> buttonCh10;
    std::unique_ptr<juce::TextButton> buttonCh11;
    std::unique_ptr<juce::TextButton> buttonCh12;
    std::unique_ptr<juce::TextButton> buttonCh13;
    std::unique_ptr<juce::TextButton> buttonCh14;
    std::unique_ptr<juce::TextButton> buttonCh15;
    std::unique_ptr<juce::TextButton> buttonCh16;
    std::unique_ptr<juce::Slider> sliderCh1Vol;
    std::unique_ptr<juce::Slider> sliderCh1Vol2;
    std::unique_ptr<juce::Slider> sliderCh1Vol3;
    std::unique_ptr<juce::Slider> sliderCh1Vol4;
    std::unique_ptr<juce::Slider> sliderCh1Vol5;
    std::unique_ptr<juce::Slider> sliderCh1Vol6;
    std::unique_ptr<juce::Slider> sliderCh1Vol7;
    std::unique_ptr<juce::Slider> sliderCh1Vol8;
    std::unique_ptr<juce::Slider> sliderCh1Vol9;
    std::unique_ptr<juce::Slider> sliderCh1Vol10;
    std::unique_ptr<juce::Slider> sliderCh1Vol11;
    std::unique_ptr<juce::Slider> sliderCh1Vol12;
    std::unique_ptr<juce::Slider> sliderCh1Vol13;
    std::unique_ptr<juce::Slider> sliderCh1Vol14;
    std::unique_ptr<juce::Slider> sliderCh1Vol15;
    std::unique_ptr<juce::Slider> sliderCh1Vol16;
    std::unique_ptr<juce::Slider> sliderPan1;
    std::unique_ptr<juce::Slider> sliderPan2;
    std::unique_ptr<juce::Slider> sliderPan3;
    std::unique_ptr<juce::Slider> sliderPan4;
    std::unique_ptr<juce::Slider> sliderPan5;
    std::unique_ptr<juce::Slider> sliderPan6;
    std::unique_ptr<juce::Slider> sliderPan7;
    std::unique_ptr<juce::Slider> sliderPan8;
    std::unique_ptr<juce::Slider> sliderPan9;
    std::unique_ptr<juce::Slider> sliderPan10;
    std::unique_ptr<juce::Slider> sliderPan11;
    std::unique_ptr<juce::Slider> sliderPan12;
    std::unique_ptr<juce::Slider> sliderPan13;
    std::unique_ptr<juce::Slider> sliderPan14;
    std::unique_ptr<juce::Slider> sliderPan15;
    std::unique_ptr<juce::Slider> sliderPan16;
    std::unique_ptr<juce::Label> labelCh;
    std::unique_ptr<juce::Label> labelPAN;
    std::unique_ptr<juce::Label> labelPAN2;
    std::unique_ptr<juce::Label> labelPrg1;
    std::unique_ptr<juce::Label> labelPrg2;
    std::unique_ptr<juce::Label> labelPrg3;
    std::unique_ptr<juce::Label> labelPrg4;
    std::unique_ptr<juce::Label> labelPrg5;
    std::unique_ptr<juce::Label> labelPrg6;
    std::unique_ptr<juce::Label> labelPrg7;
    std::unique_ptr<juce::Label> labelPrg8;
    std::unique_ptr<juce::Label> labelPrg9;
    std::unique_ptr<juce::Label> labelPrg10;
    std::unique_ptr<juce::Label> labelPrg11;
    std::unique_ptr<juce::Label> labelPrg12;
    std::unique_ptr<juce::Label> labelPrg13;
    std::unique_ptr<juce::Label> labelPrg14;
    std::unique_ptr<juce::Label> labelPrg15;
    std::unique_ptr<juce::Label> labelPrg16;
    std::unique_ptr<juce::Label> labelPrg;
    std::unique_ptr<juce::Label> labelBnk1;
    std::unique_ptr<juce::Label> labelBNK;
    std::unique_ptr<juce::Label> labelBnk2;
    std::unique_ptr<juce::Label> labelBnk3;
    std::unique_ptr<juce::Label> labelBnk4;
    std::unique_ptr<juce::Label> labelBnk5;
    std::unique_ptr<juce::Label> labelBnk6;
    std::unique_ptr<juce::Label> labelBnk7;
    std::unique_ptr<juce::Label> labelBnk8;
    std::unique_ptr<juce::Label> labelBnk9;
    std::unique_ptr<juce::Label> labelBnk10;
    std::unique_ptr<juce::Label> labelBnk11;
    std::unique_ptr<juce::Label> labelBnk12;
    std::unique_ptr<juce::Label> labelBnk13;
    std::unique_ptr<juce::Label> labelBnk14;
    std::unique_ptr<juce::Label> labelBnk15;
    std::unique_ptr<juce::Label> labelBnk16;
    std::unique_ptr<juce::TextButton> buttonLog;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GMSynthAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
