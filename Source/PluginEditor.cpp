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

//[Headers] You can add your own extra header files here...
#include <array>
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GMSynthAudioProcessorEditor::GMSynthAudioProcessorEditor (GMSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    labelVolume.reset (new juce::Label (juce::String(),
                                        TRANS ("VOLUME")));
    addAndMakeVisible (labelVolume.get());
    labelVolume->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelVolume->setJustificationType (juce::Justification::centredLeft);
    labelVolume->setEditable (false, false, false);
    labelVolume->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelVolume->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelVolume->setBounds (400, 16, 72, 24);

    buttonSelectSF2.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonSelectSF2.get());
    buttonSelectSF2->setButtonText (TRANS ("Load Sound Font"));
    buttonSelectSF2->addListener (this);

    buttonSelectSF2->setBounds (216, 16, 152, 24);

    labelSoundFontCaption.reset (new juce::Label (juce::String(),
                                                  TRANS ("Sound Font")));
    addAndMakeVisible (labelSoundFontCaption.get());
    labelSoundFontCaption->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelSoundFontCaption->setJustificationType (juce::Justification::centredLeft);
    labelSoundFontCaption->setEditable (false, false, false);
    labelSoundFontCaption->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelSoundFontCaption->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelSoundFontCaption->setBounds (16, 16, 96, 24);

    labelSoundFontName.reset (new juce::Label (juce::String(),
                                               TRANS ("(placeholder)")));
    addAndMakeVisible (labelSoundFontName.get());
    labelSoundFontName->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelSoundFontName->setJustificationType (juce::Justification::centredLeft);
    labelSoundFontName->setEditable (false, false, false);
    labelSoundFontName->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelSoundFontName->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelSoundFontName->setBounds (16, 40, 352, 24);

    sliderVolume.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderVolume.get());
    sliderVolume->setRange (-96, 0, 0.5);
    sliderVolume->setSliderStyle (juce::Slider::LinearHorizontal);
    sliderVolume->setTextBoxStyle (juce::Slider::TextBoxRight, false, 80, 20);
    sliderVolume->addListener (this);
    sliderVolume->setSkewFactor (3);

    sliderVolume->setBounds (472, 16, 216, 24);

    juce__midiKeyboardComponent.reset (new juce::MidiKeyboardComponent (juce__midiKeyboardComponentState,
                                                                        juce::MidiKeyboardComponent::horizontalKeyboard));
    addAndMakeVisible (juce__midiKeyboardComponent.get());
    juce__midiKeyboardComponent->setMidiChannel (1);
    juce__midiKeyboardComponentState.addListener (this);

    buttonCh1.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh1.get());
    buttonCh1->setButtonText (TRANS ("1"));
    buttonCh1->setConnectedEdges (juce::Button::ConnectedOnRight);
    buttonCh1->addListener (this);

    buttonCh1->setBounds (48, 72, 40, 24);

    buttonCh2.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh2.get());
    buttonCh2->setButtonText (TRANS ("2"));
    buttonCh2->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh2->addListener (this);

    buttonCh2->setBounds (88, 72, 40, 24);

    buttonCh3.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh3.get());
    buttonCh3->setButtonText (TRANS ("3"));
    buttonCh3->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh3->addListener (this);

    buttonCh3->setBounds (128, 72, 40, 24);

    buttonCh4.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh4.get());
    buttonCh4->setButtonText (TRANS ("4"));
    buttonCh4->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh4->addListener (this);

    buttonCh4->setBounds (168, 72, 40, 24);

    buttonCh5.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh5.get());
    buttonCh5->setButtonText (TRANS ("5"));
    buttonCh5->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh5->addListener (this);

    buttonCh5->setBounds (208, 72, 40, 24);

    buttonCh6.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh6.get());
    buttonCh6->setButtonText (TRANS ("6"));
    buttonCh6->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh6->addListener (this);

    buttonCh6->setBounds (248, 72, 40, 24);

    buttonCh7.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh7.get());
    buttonCh7->setButtonText (TRANS ("7"));
    buttonCh7->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh7->addListener (this);

    buttonCh7->setBounds (288, 72, 40, 24);

    buttonCh8.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh8.get());
    buttonCh8->setButtonText (TRANS ("8"));
    buttonCh8->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh8->addListener (this);

    buttonCh8->setBounds (328, 72, 40, 24);

    buttonCh9.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh9.get());
    buttonCh9->setButtonText (TRANS ("9"));
    buttonCh9->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh9->addListener (this);

    buttonCh9->setBounds (368, 72, 40, 24);

    buttonCh10.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh10.get());
    buttonCh10->setButtonText (TRANS ("10"));
    buttonCh10->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh10->addListener (this);

    buttonCh10->setBounds (408, 72, 40, 24);

    buttonCh11.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh11.get());
    buttonCh11->setButtonText (TRANS ("11"));
    buttonCh11->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh11->addListener (this);

    buttonCh11->setBounds (448, 72, 40, 24);

    buttonCh12.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh12.get());
    buttonCh12->setButtonText (TRANS ("12"));
    buttonCh12->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh12->addListener (this);

    buttonCh12->setBounds (488, 72, 40, 24);

    buttonCh13.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh13.get());
    buttonCh13->setButtonText (TRANS ("13"));
    buttonCh13->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh13->addListener (this);

    buttonCh13->setBounds (528, 72, 40, 24);

    buttonCh14.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh14.get());
    buttonCh14->setButtonText (TRANS ("14"));
    buttonCh14->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh14->addListener (this);

    buttonCh14->setBounds (568, 72, 40, 24);

    buttonCh15.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh15.get());
    buttonCh15->setButtonText (TRANS ("15"));
    buttonCh15->setConnectedEdges (juce::Button::ConnectedOnLeft | juce::Button::ConnectedOnRight);
    buttonCh15->addListener (this);

    buttonCh15->setBounds (608, 72, 40, 24);

    buttonCh16.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonCh16.get());
    buttonCh16->setButtonText (TRANS ("16"));
    buttonCh16->setConnectedEdges (juce::Button::ConnectedOnLeft);
    buttonCh16->addListener (this);

    buttonCh16->setBounds (648, 72, 40, 24);

    sliderCh1Vol.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol.get());
    sliderCh1Vol->setRange (0, 127, 1);
    sliderCh1Vol->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol->addListener (this);

    sliderCh1Vol->setBounds (48, 232, 40, 107);

    sliderCh1Vol2.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol2.get());
    sliderCh1Vol2->setRange (0, 127, 1);
    sliderCh1Vol2->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol2->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol2->addListener (this);

    sliderCh1Vol2->setBounds (88, 232, 40, 107);

    sliderCh1Vol3.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol3.get());
    sliderCh1Vol3->setRange (0, 127, 1);
    sliderCh1Vol3->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol3->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol3->addListener (this);

    sliderCh1Vol3->setBounds (128, 232, 40, 107);

    sliderCh1Vol4.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol4.get());
    sliderCh1Vol4->setRange (0, 127, 1);
    sliderCh1Vol4->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol4->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol4->addListener (this);

    sliderCh1Vol4->setBounds (168, 232, 40, 107);

    sliderCh1Vol5.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol5.get());
    sliderCh1Vol5->setRange (0, 127, 1);
    sliderCh1Vol5->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol5->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol5->addListener (this);

    sliderCh1Vol5->setBounds (208, 232, 40, 107);

    sliderCh1Vol6.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol6.get());
    sliderCh1Vol6->setRange (0, 127, 1);
    sliderCh1Vol6->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol6->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol6->addListener (this);

    sliderCh1Vol6->setBounds (248, 232, 40, 107);

    sliderCh1Vol7.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol7.get());
    sliderCh1Vol7->setRange (0, 127, 1);
    sliderCh1Vol7->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol7->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol7->addListener (this);

    sliderCh1Vol7->setBounds (288, 232, 40, 107);

    sliderCh1Vol8.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol8.get());
    sliderCh1Vol8->setRange (0, 127, 1);
    sliderCh1Vol8->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol8->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol8->addListener (this);

    sliderCh1Vol8->setBounds (328, 232, 40, 107);

    sliderCh1Vol9.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol9.get());
    sliderCh1Vol9->setRange (0, 127, 1);
    sliderCh1Vol9->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol9->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol9->addListener (this);

    sliderCh1Vol9->setBounds (368, 232, 40, 107);

    sliderCh1Vol10.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol10.get());
    sliderCh1Vol10->setRange (0, 127, 1);
    sliderCh1Vol10->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol10->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol10->addListener (this);

    sliderCh1Vol10->setBounds (408, 232, 40, 107);

    sliderCh1Vol11.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol11.get());
    sliderCh1Vol11->setRange (0, 127, 1);
    sliderCh1Vol11->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol11->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol11->addListener (this);

    sliderCh1Vol11->setBounds (448, 232, 40, 107);

    sliderCh1Vol12.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol12.get());
    sliderCh1Vol12->setRange (0, 127, 1);
    sliderCh1Vol12->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol12->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol12->addListener (this);

    sliderCh1Vol12->setBounds (488, 232, 40, 107);

    sliderCh1Vol13.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol13.get());
    sliderCh1Vol13->setRange (0, 127, 1);
    sliderCh1Vol13->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol13->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol13->addListener (this);

    sliderCh1Vol13->setBounds (528, 232, 40, 107);

    sliderCh1Vol14.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol14.get());
    sliderCh1Vol14->setRange (0, 127, 1);
    sliderCh1Vol14->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol14->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol14->addListener (this);

    sliderCh1Vol14->setBounds (568, 232, 40, 107);

    sliderCh1Vol15.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol15.get());
    sliderCh1Vol15->setRange (0, 127, 1);
    sliderCh1Vol15->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol15->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol15->addListener (this);

    sliderCh1Vol15->setBounds (608, 232, 40, 107);

    sliderCh1Vol16.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderCh1Vol16.get());
    sliderCh1Vol16->setRange (0, 127, 1);
    sliderCh1Vol16->setSliderStyle (juce::Slider::LinearVertical);
    sliderCh1Vol16->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCh1Vol16->addListener (this);

    sliderCh1Vol16->setBounds (648, 232, 40, 107);

    sliderPan1.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan1.get());
    sliderPan1->setRange (0, 127, 1);
    sliderPan1->setSliderStyle (juce::Slider::Rotary);
    sliderPan1->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan1->addListener (this);

    sliderPan1->setBounds (48, 160, 40, 64);

    sliderPan2.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan2.get());
    sliderPan2->setRange (0, 127, 1);
    sliderPan2->setSliderStyle (juce::Slider::Rotary);
    sliderPan2->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan2->addListener (this);

    sliderPan2->setBounds (88, 160, 40, 64);

    sliderPan3.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan3.get());
    sliderPan3->setRange (0, 127, 1);
    sliderPan3->setSliderStyle (juce::Slider::Rotary);
    sliderPan3->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan3->addListener (this);

    sliderPan3->setBounds (128, 160, 40, 64);

    sliderPan4.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan4.get());
    sliderPan4->setRange (0, 127, 1);
    sliderPan4->setSliderStyle (juce::Slider::Rotary);
    sliderPan4->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan4->addListener (this);

    sliderPan4->setBounds (168, 160, 40, 64);

    sliderPan5.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan5.get());
    sliderPan5->setRange (0, 127, 1);
    sliderPan5->setSliderStyle (juce::Slider::Rotary);
    sliderPan5->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan5->addListener (this);

    sliderPan5->setBounds (208, 160, 40, 64);

    sliderPan6.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan6.get());
    sliderPan6->setRange (0, 127, 1);
    sliderPan6->setSliderStyle (juce::Slider::Rotary);
    sliderPan6->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan6->addListener (this);

    sliderPan6->setBounds (248, 160, 40, 64);

    sliderPan7.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan7.get());
    sliderPan7->setRange (0, 127, 1);
    sliderPan7->setSliderStyle (juce::Slider::Rotary);
    sliderPan7->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan7->addListener (this);

    sliderPan7->setBounds (288, 160, 40, 64);

    sliderPan8.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan8.get());
    sliderPan8->setRange (0, 127, 1);
    sliderPan8->setSliderStyle (juce::Slider::Rotary);
    sliderPan8->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan8->addListener (this);

    sliderPan8->setBounds (328, 160, 40, 64);

    sliderPan9.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan9.get());
    sliderPan9->setRange (0, 127, 1);
    sliderPan9->setSliderStyle (juce::Slider::Rotary);
    sliderPan9->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan9->addListener (this);

    sliderPan9->setBounds (368, 160, 40, 64);

    sliderPan10.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan10.get());
    sliderPan10->setRange (0, 127, 1);
    sliderPan10->setSliderStyle (juce::Slider::Rotary);
    sliderPan10->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan10->addListener (this);

    sliderPan10->setBounds (408, 160, 40, 64);

    sliderPan11.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan11.get());
    sliderPan11->setRange (0, 127, 1);
    sliderPan11->setSliderStyle (juce::Slider::Rotary);
    sliderPan11->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan11->addListener (this);

    sliderPan11->setBounds (448, 160, 40, 64);

    sliderPan12.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan12.get());
    sliderPan12->setRange (0, 127, 1);
    sliderPan12->setSliderStyle (juce::Slider::Rotary);
    sliderPan12->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan12->addListener (this);

    sliderPan12->setBounds (488, 160, 40, 64);

    sliderPan13.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan13.get());
    sliderPan13->setRange (0, 127, 1);
    sliderPan13->setSliderStyle (juce::Slider::Rotary);
    sliderPan13->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan13->addListener (this);

    sliderPan13->setBounds (528, 160, 40, 64);

    sliderPan14.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan14.get());
    sliderPan14->setRange (0, 127, 1);
    sliderPan14->setSliderStyle (juce::Slider::Rotary);
    sliderPan14->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan14->addListener (this);

    sliderPan14->setBounds (568, 160, 40, 64);

    sliderPan15.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan15.get());
    sliderPan15->setRange (0, 127, 1);
    sliderPan15->setSliderStyle (juce::Slider::Rotary);
    sliderPan15->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan15->addListener (this);

    sliderPan15->setBounds (608, 160, 40, 64);

    sliderPan16.reset (new juce::Slider (juce::String()));
    addAndMakeVisible (sliderPan16.get());
    sliderPan16->setRange (0, 127, 1);
    sliderPan16->setSliderStyle (juce::Slider::Rotary);
    sliderPan16->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderPan16->addListener (this);

    sliderPan16->setBounds (648, 160, 40, 64);

    labelCh.reset (new juce::Label (juce::String(),
                                    TRANS ("CH")));
    addAndMakeVisible (labelCh.get());
    labelCh->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelCh->setJustificationType (juce::Justification::centredRight);
    labelCh->setEditable (false, false, false);
    labelCh->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelCh->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelCh->setBounds (8, 72, 40, 24);

    labelPAN.reset (new juce::Label (juce::String(),
                                     TRANS ("PAN")));
    addAndMakeVisible (labelPAN.get());
    labelPAN->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPAN->setJustificationType (juce::Justification::centredRight);
    labelPAN->setEditable (false, false, false);
    labelPAN->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPAN->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPAN->setBounds (8, 160, 40, 64);

    labelPAN2.reset (new juce::Label (juce::String(),
                                      TRANS ("VOL")));
    addAndMakeVisible (labelPAN2.get());
    labelPAN2->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPAN2->setJustificationType (juce::Justification::centredRight);
    labelPAN2->setEditable (false, false, false);
    labelPAN2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPAN2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPAN2->setBounds (8, 232, 40, 112);

    labelPrg1.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg1.get());
    labelPrg1->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg1->setJustificationType (juce::Justification::centred);
    labelPrg1->setEditable (false, false, false);
    labelPrg1->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg1->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg1->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg1->setBounds (48, 136, 40, 24);

    labelPrg2.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg2.get());
    labelPrg2->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg2->setJustificationType (juce::Justification::centred);
    labelPrg2->setEditable (false, false, false);
    labelPrg2->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg2->setBounds (88, 136, 40, 24);

    labelPrg3.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg3.get());
    labelPrg3->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg3->setJustificationType (juce::Justification::centred);
    labelPrg3->setEditable (false, false, false);
    labelPrg3->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg3->setBounds (128, 136, 40, 24);

    labelPrg4.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg4.get());
    labelPrg4->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg4->setJustificationType (juce::Justification::centred);
    labelPrg4->setEditable (false, false, false);
    labelPrg4->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg4->setBounds (168, 136, 40, 24);

    labelPrg5.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg5.get());
    labelPrg5->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg5->setJustificationType (juce::Justification::centred);
    labelPrg5->setEditable (false, false, false);
    labelPrg5->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg5->setBounds (208, 136, 40, 24);

    labelPrg6.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg6.get());
    labelPrg6->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg6->setJustificationType (juce::Justification::centred);
    labelPrg6->setEditable (false, false, false);
    labelPrg6->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg6->setBounds (248, 136, 40, 24);

    labelPrg7.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg7.get());
    labelPrg7->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg7->setJustificationType (juce::Justification::centred);
    labelPrg7->setEditable (false, false, false);
    labelPrg7->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg7->setBounds (288, 136, 40, 24);

    labelPrg8.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg8.get());
    labelPrg8->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg8->setJustificationType (juce::Justification::centred);
    labelPrg8->setEditable (false, false, false);
    labelPrg8->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg8->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg8->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg8->setBounds (328, 136, 40, 24);

    labelPrg9.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelPrg9.get());
    labelPrg9->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg9->setJustificationType (juce::Justification::centred);
    labelPrg9->setEditable (false, false, false);
    labelPrg9->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg9->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg9->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg9->setBounds (368, 136, 40, 24);

    labelPrg10.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg10.get());
    labelPrg10->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg10->setJustificationType (juce::Justification::centred);
    labelPrg10->setEditable (false, false, false);
    labelPrg10->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg10->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg10->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg10->setBounds (408, 136, 40, 24);

    labelPrg11.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg11.get());
    labelPrg11->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg11->setJustificationType (juce::Justification::centred);
    labelPrg11->setEditable (false, false, false);
    labelPrg11->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg11->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg11->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg11->setBounds (448, 136, 40, 24);

    labelPrg12.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg12.get());
    labelPrg12->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg12->setJustificationType (juce::Justification::centred);
    labelPrg12->setEditable (false, false, false);
    labelPrg12->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg12->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg12->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg12->setBounds (488, 136, 40, 24);

    labelPrg13.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg13.get());
    labelPrg13->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg13->setJustificationType (juce::Justification::centred);
    labelPrg13->setEditable (false, false, false);
    labelPrg13->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg13->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg13->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg13->setBounds (528, 136, 40, 24);

    labelPrg14.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg14.get());
    labelPrg14->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg14->setJustificationType (juce::Justification::centred);
    labelPrg14->setEditable (false, false, false);
    labelPrg14->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg14->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg14->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg14->setBounds (568, 136, 40, 24);

    labelPrg15.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg15.get());
    labelPrg15->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg15->setJustificationType (juce::Justification::centred);
    labelPrg15->setEditable (false, false, false);
    labelPrg15->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg15->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg15->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg15->setBounds (608, 136, 40, 24);

    labelPrg16.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelPrg16.get());
    labelPrg16->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg16->setJustificationType (juce::Justification::centred);
    labelPrg16->setEditable (false, false, false);
    labelPrg16->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelPrg16->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg16->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg16->setBounds (648, 136, 40, 24);

    labelPrg.reset (new juce::Label (juce::String(),
                                     TRANS ("PRG")));
    addAndMakeVisible (labelPrg.get());
    labelPrg->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelPrg->setJustificationType (juce::Justification::centredRight);
    labelPrg->setEditable (false, false, false);
    labelPrg->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelPrg->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelPrg->setBounds (8, 136, 40, 24);

    labelBnk1.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk1.get());
    labelBnk1->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk1->setJustificationType (juce::Justification::centred);
    labelBnk1->setEditable (false, false, false);
    labelBnk1->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk1->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk1->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk1->setBounds (48, 112, 40, 24);

    labelBNK.reset (new juce::Label (juce::String(),
                                     TRANS ("BNK")));
    addAndMakeVisible (labelBNK.get());
    labelBNK->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBNK->setJustificationType (juce::Justification::centredRight);
    labelBNK->setEditable (false, false, false);
    labelBNK->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBNK->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBNK->setBounds (8, 112, 40, 24);

    labelBnk2.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk2.get());
    labelBnk2->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk2->setJustificationType (juce::Justification::centred);
    labelBnk2->setEditable (false, false, false);
    labelBnk2->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk2->setBounds (88, 112, 40, 24);

    labelBnk3.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk3.get());
    labelBnk3->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk3->setJustificationType (juce::Justification::centred);
    labelBnk3->setEditable (false, false, false);
    labelBnk3->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk3->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk3->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk3->setBounds (128, 112, 40, 24);

    labelBnk4.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk4.get());
    labelBnk4->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk4->setJustificationType (juce::Justification::centred);
    labelBnk4->setEditable (false, false, false);
    labelBnk4->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk4->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk4->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk4->setBounds (168, 112, 40, 24);

    labelBnk5.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk5.get());
    labelBnk5->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk5->setJustificationType (juce::Justification::centred);
    labelBnk5->setEditable (false, false, false);
    labelBnk5->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk5->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk5->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk5->setBounds (208, 112, 40, 24);

    labelBnk6.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk6.get());
    labelBnk6->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk6->setJustificationType (juce::Justification::centred);
    labelBnk6->setEditable (false, false, false);
    labelBnk6->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk6->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk6->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk6->setBounds (248, 112, 40, 24);

    labelBnk7.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk7.get());
    labelBnk7->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk7->setJustificationType (juce::Justification::centred);
    labelBnk7->setEditable (false, false, false);
    labelBnk7->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk7->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk7->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk7->setBounds (288, 112, 40, 24);

    labelBnk8.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk8.get());
    labelBnk8->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk8->setJustificationType (juce::Justification::centred);
    labelBnk8->setEditable (false, false, false);
    labelBnk8->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk8->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk8->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk8->setBounds (328, 112, 40, 24);

    labelBnk9.reset (new juce::Label (juce::String(),
                                      TRANS ("0")));
    addAndMakeVisible (labelBnk9.get());
    labelBnk9->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk9->setJustificationType (juce::Justification::centred);
    labelBnk9->setEditable (false, false, false);
    labelBnk9->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk9->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk9->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk9->setBounds (368, 112, 40, 24);

    labelBnk10.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk10.get());
    labelBnk10->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk10->setJustificationType (juce::Justification::centred);
    labelBnk10->setEditable (false, false, false);
    labelBnk10->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk10->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk10->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk10->setBounds (408, 112, 40, 24);

    labelBnk11.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk11.get());
    labelBnk11->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk11->setJustificationType (juce::Justification::centred);
    labelBnk11->setEditable (false, false, false);
    labelBnk11->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk11->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk11->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk11->setBounds (448, 112, 40, 24);

    labelBnk12.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk12.get());
    labelBnk12->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk12->setJustificationType (juce::Justification::centred);
    labelBnk12->setEditable (false, false, false);
    labelBnk12->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk12->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk12->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk12->setBounds (488, 112, 40, 24);

    labelBnk13.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk13.get());
    labelBnk13->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk13->setJustificationType (juce::Justification::centred);
    labelBnk13->setEditable (false, false, false);
    labelBnk13->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk13->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk13->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk13->setBounds (528, 112, 40, 24);

    labelBnk14.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk14.get());
    labelBnk14->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk14->setJustificationType (juce::Justification::centred);
    labelBnk14->setEditable (false, false, false);
    labelBnk14->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk14->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk14->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk14->setBounds (568, 112, 40, 24);

    labelBnk15.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk15.get());
    labelBnk15->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk15->setJustificationType (juce::Justification::centred);
    labelBnk15->setEditable (false, false, false);
    labelBnk15->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk15->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk15->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk15->setBounds (608, 112, 40, 24);

    labelBnk16.reset (new juce::Label (juce::String(),
                                       TRANS ("0")));
    addAndMakeVisible (labelBnk16.get());
    labelBnk16->setFont (juce::Font (juce::FontOptions { 15.00f, juce::Font::plain }.withStyle ("Regular").withMetricsKind (juce::TypefaceMetricsKind::legacy)));
    labelBnk16->setJustificationType (juce::Justification::centred);
    labelBnk16->setEditable (false, false, false);
    labelBnk16->setColour (juce::Label::outlineColourId, juce::Colour (0xff8e989b));
    labelBnk16->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    labelBnk16->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    labelBnk16->setBounds (648, 112, 40, 24);

    buttonLog.reset (new juce::TextButton (juce::String()));
    addAndMakeVisible (buttonLog.get());
    buttonLog->setButtonText (TRANS ("Start Logging"));
    buttonLog->addListener (this);

    buttonLog->setBounds (392, 40, 136, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (706, 384);


    //[Constructor] You can add your own custom stuff here..
    const std::array<juce::TextButton*, 16> channelButtons
    {
        buttonCh1.get(), buttonCh2.get(), buttonCh3.get(), buttonCh4.get(),
        buttonCh5.get(), buttonCh6.get(), buttonCh7.get(), buttonCh8.get(),
        buttonCh9.get(), buttonCh10.get(), buttonCh11.get(), buttonCh12.get(),
        buttonCh13.get(), buttonCh14.get(), buttonCh15.get(), buttonCh16.get()
    };

    for (int channel = 0; channel < static_cast<int> (channelButtons.size()); ++channel)
        configureChannelButton (*channelButtons[static_cast<size_t> (channel)], channel);

    configureChannelStateLabels();
    stateUpdateTimer = std::make_unique<StateUpdateTimer> (*this);
    stateUpdateTimer->start();
    buttonLog->setButtonText (audioProcessor.isMidiLogging() ? "Stop Logging" : "Start Logging");
    updateChannelStateControls();
    updateSoundFontLabel();
    //[/Constructor]
}

GMSynthAudioProcessorEditor::~GMSynthAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    stateUpdateTimer.reset();
    //[/Destructor_pre]

    labelVolume = nullptr;
    buttonSelectSF2 = nullptr;
    labelSoundFontCaption = nullptr;
    labelSoundFontName = nullptr;
    sliderVolume = nullptr;
    juce__midiKeyboardComponentState.removeListener (this);
    juce__midiKeyboardComponent = nullptr;
    buttonCh1 = nullptr;
    buttonCh2 = nullptr;
    buttonCh3 = nullptr;
    buttonCh4 = nullptr;
    buttonCh5 = nullptr;
    buttonCh6 = nullptr;
    buttonCh7 = nullptr;
    buttonCh8 = nullptr;
    buttonCh9 = nullptr;
    buttonCh10 = nullptr;
    buttonCh11 = nullptr;
    buttonCh12 = nullptr;
    buttonCh13 = nullptr;
    buttonCh14 = nullptr;
    buttonCh15 = nullptr;
    buttonCh16 = nullptr;
    sliderCh1Vol = nullptr;
    sliderCh1Vol2 = nullptr;
    sliderCh1Vol3 = nullptr;
    sliderCh1Vol4 = nullptr;
    sliderCh1Vol5 = nullptr;
    sliderCh1Vol6 = nullptr;
    sliderCh1Vol7 = nullptr;
    sliderCh1Vol8 = nullptr;
    sliderCh1Vol9 = nullptr;
    sliderCh1Vol10 = nullptr;
    sliderCh1Vol11 = nullptr;
    sliderCh1Vol12 = nullptr;
    sliderCh1Vol13 = nullptr;
    sliderCh1Vol14 = nullptr;
    sliderCh1Vol15 = nullptr;
    sliderCh1Vol16 = nullptr;
    sliderPan1 = nullptr;
    sliderPan2 = nullptr;
    sliderPan3 = nullptr;
    sliderPan4 = nullptr;
    sliderPan5 = nullptr;
    sliderPan6 = nullptr;
    sliderPan7 = nullptr;
    sliderPan8 = nullptr;
    sliderPan9 = nullptr;
    sliderPan10 = nullptr;
    sliderPan11 = nullptr;
    sliderPan12 = nullptr;
    sliderPan13 = nullptr;
    sliderPan14 = nullptr;
    sliderPan15 = nullptr;
    sliderPan16 = nullptr;
    labelCh = nullptr;
    labelPAN = nullptr;
    labelPAN2 = nullptr;
    labelPrg1 = nullptr;
    labelPrg2 = nullptr;
    labelPrg3 = nullptr;
    labelPrg4 = nullptr;
    labelPrg5 = nullptr;
    labelPrg6 = nullptr;
    labelPrg7 = nullptr;
    labelPrg8 = nullptr;
    labelPrg9 = nullptr;
    labelPrg10 = nullptr;
    labelPrg11 = nullptr;
    labelPrg12 = nullptr;
    labelPrg13 = nullptr;
    labelPrg14 = nullptr;
    labelPrg15 = nullptr;
    labelPrg16 = nullptr;
    labelPrg = nullptr;
    labelBnk1 = nullptr;
    labelBNK = nullptr;
    labelBnk2 = nullptr;
    labelBnk3 = nullptr;
    labelBnk4 = nullptr;
    labelBnk5 = nullptr;
    labelBnk6 = nullptr;
    labelBnk7 = nullptr;
    labelBnk8 = nullptr;
    labelBnk9 = nullptr;
    labelBnk10 = nullptr;
    labelBnk11 = nullptr;
    labelBnk12 = nullptr;
    labelBnk13 = nullptr;
    labelBnk14 = nullptr;
    labelBnk15 = nullptr;
    labelBnk16 = nullptr;
    buttonLog = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GMSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GMSynthAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    juce__midiKeyboardComponent->setBounds (48, getHeight() - 32, getWidth() - 64, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GMSynthAudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == buttonSelectSF2.get())
    {
        //[UserButtonCode_buttonSelectSF2] -- add your button handler code here..
        chooseSoundFont();
        //[/UserButtonCode_buttonSelectSF2]
    }
    else if (buttonThatWasClicked == buttonCh1.get())
    {
        //[UserButtonCode_buttonCh1] -- add your button handler code here..
        audioProcessor.setChannelMuted (0, buttonCh1->getToggleState());
        //[/UserButtonCode_buttonCh1]
    }
    else if (buttonThatWasClicked == buttonCh2.get())
    {
        //[UserButtonCode_buttonCh2] -- add your button handler code here..
        audioProcessor.setChannelMuted (1, buttonCh2->getToggleState());
        //[/UserButtonCode_buttonCh2]
    }
    else if (buttonThatWasClicked == buttonCh3.get())
    {
        //[UserButtonCode_buttonCh3] -- add your button handler code here..
        audioProcessor.setChannelMuted (2, buttonCh3->getToggleState());
        //[/UserButtonCode_buttonCh3]
    }
    else if (buttonThatWasClicked == buttonCh4.get())
    {
        //[UserButtonCode_buttonCh4] -- add your button handler code here..
        audioProcessor.setChannelMuted (3, buttonCh4->getToggleState());
        //[/UserButtonCode_buttonCh4]
    }
    else if (buttonThatWasClicked == buttonCh5.get())
    {
        //[UserButtonCode_buttonCh5] -- add your button handler code here..
        audioProcessor.setChannelMuted (4, buttonCh5->getToggleState());
        //[/UserButtonCode_buttonCh5]
    }
    else if (buttonThatWasClicked == buttonCh6.get())
    {
        //[UserButtonCode_buttonCh6] -- add your button handler code here..
        audioProcessor.setChannelMuted (5, buttonCh6->getToggleState());
        //[/UserButtonCode_buttonCh6]
    }
    else if (buttonThatWasClicked == buttonCh7.get())
    {
        //[UserButtonCode_buttonCh7] -- add your button handler code here..
        audioProcessor.setChannelMuted (6, buttonCh7->getToggleState());
        //[/UserButtonCode_buttonCh7]
    }
    else if (buttonThatWasClicked == buttonCh8.get())
    {
        //[UserButtonCode_buttonCh8] -- add your button handler code here..
        audioProcessor.setChannelMuted (7, buttonCh8->getToggleState());
        //[/UserButtonCode_buttonCh8]
    }
    else if (buttonThatWasClicked == buttonCh9.get())
    {
        //[UserButtonCode_buttonCh9] -- add your button handler code here..
        audioProcessor.setChannelMuted (8, buttonCh9->getToggleState());
        //[/UserButtonCode_buttonCh9]
    }
    else if (buttonThatWasClicked == buttonCh10.get())
    {
        //[UserButtonCode_buttonCh10] -- add your button handler code here..
        audioProcessor.setChannelMuted (9, buttonCh10->getToggleState());
        //[/UserButtonCode_buttonCh10]
    }
    else if (buttonThatWasClicked == buttonCh11.get())
    {
        //[UserButtonCode_buttonCh11] -- add your button handler code here..
        audioProcessor.setChannelMuted (10, buttonCh11->getToggleState());
        //[/UserButtonCode_buttonCh11]
    }
    else if (buttonThatWasClicked == buttonCh12.get())
    {
        //[UserButtonCode_buttonCh12] -- add your button handler code here..
        audioProcessor.setChannelMuted (11, buttonCh12->getToggleState());
        //[/UserButtonCode_buttonCh12]
    }
    else if (buttonThatWasClicked == buttonCh13.get())
    {
        //[UserButtonCode_buttonCh13] -- add your button handler code here..
        audioProcessor.setChannelMuted (12, buttonCh13->getToggleState());
        //[/UserButtonCode_buttonCh13]
    }
    else if (buttonThatWasClicked == buttonCh14.get())
    {
        //[UserButtonCode_buttonCh14] -- add your button handler code here..
        audioProcessor.setChannelMuted (13, buttonCh14->getToggleState());
        //[/UserButtonCode_buttonCh14]
    }
    else if (buttonThatWasClicked == buttonCh15.get())
    {
        //[UserButtonCode_buttonCh15] -- add your button handler code here..
        audioProcessor.setChannelMuted (14, buttonCh15->getToggleState());
        //[/UserButtonCode_buttonCh15]
    }
    else if (buttonThatWasClicked == buttonCh16.get())
    {
        //[UserButtonCode_buttonCh16] -- add your button handler code here..
        audioProcessor.setChannelMuted (15, buttonCh16->getToggleState());
        //[/UserButtonCode_buttonCh16]
    }
    else if (buttonThatWasClicked == buttonLog.get())
    {
        //[UserButtonCode_buttonLog] -- add your button handler code here..
        if (! audioProcessor.isMidiLogging())
        {
            audioProcessor.startMidiLogging();
            buttonLog->setButtonText ("Stop Logging");
        }
        else
        {
            const auto result = audioProcessor.stopMidiLoggingAndSave();
            buttonLog->setButtonText ("Start Logging");

            if (result.failed())
            {
                juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                                        "MIDI Log",
                                                        result.getErrorMessage());
            }
            else
            {
                juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::InfoIcon,
                                                        "MIDI Log",
                                                        "Saved to:\n"
                                                          + audioProcessor.getLastMidiLogPath());
            }
        }
        //[/UserButtonCode_buttonLog]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GMSynthAudioProcessorEditor::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    if (sliderThatWasMoved == sliderVolume.get())
    {
        audioProcessor.setMasterVolumeDb (static_cast<float> (sliderVolume->getValue()));
        return;
    }

    const std::array<juce::Slider*, 16> volumeSliders
    {
        sliderCh1Vol.get(), sliderCh1Vol2.get(), sliderCh1Vol3.get(), sliderCh1Vol4.get(),
        sliderCh1Vol5.get(), sliderCh1Vol6.get(), sliderCh1Vol7.get(), sliderCh1Vol8.get(),
        sliderCh1Vol9.get(), sliderCh1Vol10.get(), sliderCh1Vol11.get(), sliderCh1Vol12.get(),
        sliderCh1Vol13.get(), sliderCh1Vol14.get(), sliderCh1Vol15.get(), sliderCh1Vol16.get()
    };

    for (int channel = 0; channel < static_cast<int> (volumeSliders.size()); ++channel)
    {
        if (sliderThatWasMoved == volumeSliders[static_cast<size_t> (channel)])
        {
            audioProcessor.setChannelVolume (channel, juce::roundToInt (sliderThatWasMoved->getValue()));
            return;
        }
    }

    const std::array<juce::Slider*, 16> panSliders
    {
        sliderPan1.get(), sliderPan2.get(), sliderPan3.get(), sliderPan4.get(),
        sliderPan5.get(), sliderPan6.get(), sliderPan7.get(), sliderPan8.get(),
        sliderPan9.get(), sliderPan10.get(), sliderPan11.get(), sliderPan12.get(),
        sliderPan13.get(), sliderPan14.get(), sliderPan15.get(), sliderPan16.get()
    };

    for (int channel = 0; channel < static_cast<int> (panSliders.size()); ++channel)
    {
        if (sliderThatWasMoved == panSliders[static_cast<size_t> (channel)])
        {
            audioProcessor.setChannelPan (channel, juce::roundToInt (sliderThatWasMoved->getValue()));
            return;
        }
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderVolume.get())
    {
        //[UserSliderCode_sliderVolume] -- add your slider handling code here..
        //[/UserSliderCode_sliderVolume]
    }
    else if (sliderThatWasMoved == sliderCh1Vol.get())
    {
        //[UserSliderCode_sliderCh1Vol] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol]
    }
    else if (sliderThatWasMoved == sliderCh1Vol2.get())
    {
        //[UserSliderCode_sliderCh1Vol2] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol2]
    }
    else if (sliderThatWasMoved == sliderCh1Vol3.get())
    {
        //[UserSliderCode_sliderCh1Vol3] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol3]
    }
    else if (sliderThatWasMoved == sliderCh1Vol4.get())
    {
        //[UserSliderCode_sliderCh1Vol4] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol4]
    }
    else if (sliderThatWasMoved == sliderCh1Vol5.get())
    {
        //[UserSliderCode_sliderCh1Vol5] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol5]
    }
    else if (sliderThatWasMoved == sliderCh1Vol6.get())
    {
        //[UserSliderCode_sliderCh1Vol6] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol6]
    }
    else if (sliderThatWasMoved == sliderCh1Vol7.get())
    {
        //[UserSliderCode_sliderCh1Vol7] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol7]
    }
    else if (sliderThatWasMoved == sliderCh1Vol8.get())
    {
        //[UserSliderCode_sliderCh1Vol8] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol8]
    }
    else if (sliderThatWasMoved == sliderCh1Vol9.get())
    {
        //[UserSliderCode_sliderCh1Vol9] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol9]
    }
    else if (sliderThatWasMoved == sliderCh1Vol10.get())
    {
        //[UserSliderCode_sliderCh1Vol10] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol10]
    }
    else if (sliderThatWasMoved == sliderCh1Vol11.get())
    {
        //[UserSliderCode_sliderCh1Vol11] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol11]
    }
    else if (sliderThatWasMoved == sliderCh1Vol12.get())
    {
        //[UserSliderCode_sliderCh1Vol12] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol12]
    }
    else if (sliderThatWasMoved == sliderCh1Vol13.get())
    {
        //[UserSliderCode_sliderCh1Vol13] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol13]
    }
    else if (sliderThatWasMoved == sliderCh1Vol14.get())
    {
        //[UserSliderCode_sliderCh1Vol14] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol14]
    }
    else if (sliderThatWasMoved == sliderCh1Vol15.get())
    {
        //[UserSliderCode_sliderCh1Vol15] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol15]
    }
    else if (sliderThatWasMoved == sliderCh1Vol16.get())
    {
        //[UserSliderCode_sliderCh1Vol16] -- add your slider handling code here..
        //[/UserSliderCode_sliderCh1Vol16]
    }
    else if (sliderThatWasMoved == sliderPan1.get())
    {
        //[UserSliderCode_sliderPan1] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan1]
    }
    else if (sliderThatWasMoved == sliderPan2.get())
    {
        //[UserSliderCode_sliderPan2] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan2]
    }
    else if (sliderThatWasMoved == sliderPan3.get())
    {
        //[UserSliderCode_sliderPan3] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan3]
    }
    else if (sliderThatWasMoved == sliderPan4.get())
    {
        //[UserSliderCode_sliderPan4] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan4]
    }
    else if (sliderThatWasMoved == sliderPan5.get())
    {
        //[UserSliderCode_sliderPan5] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan5]
    }
    else if (sliderThatWasMoved == sliderPan6.get())
    {
        //[UserSliderCode_sliderPan6] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan6]
    }
    else if (sliderThatWasMoved == sliderPan7.get())
    {
        //[UserSliderCode_sliderPan7] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan7]
    }
    else if (sliderThatWasMoved == sliderPan8.get())
    {
        //[UserSliderCode_sliderPan8] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan8]
    }
    else if (sliderThatWasMoved == sliderPan9.get())
    {
        //[UserSliderCode_sliderPan9] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan9]
    }
    else if (sliderThatWasMoved == sliderPan10.get())
    {
        //[UserSliderCode_sliderPan10] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan10]
    }
    else if (sliderThatWasMoved == sliderPan11.get())
    {
        //[UserSliderCode_sliderPan11] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan11]
    }
    else if (sliderThatWasMoved == sliderPan12.get())
    {
        //[UserSliderCode_sliderPan12] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan12]
    }
    else if (sliderThatWasMoved == sliderPan13.get())
    {
        //[UserSliderCode_sliderPan13] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan13]
    }
    else if (sliderThatWasMoved == sliderPan14.get())
    {
        //[UserSliderCode_sliderPan14] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan14]
    }
    else if (sliderThatWasMoved == sliderPan15.get())
    {
        //[UserSliderCode_sliderPan15] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan15]
    }
    else if (sliderThatWasMoved == sliderPan16.get())
    {
        //[UserSliderCode_sliderPan16] -- add your slider handling code here..
        //[/UserSliderCode_sliderPan16]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GMSynthAudioProcessorEditor::handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    //[UserhandleNoteOn_Pre]
    //[/UserhandleNoteOn_Pre]

    if (source == &juce__midiKeyboardComponentState)
    {
        //[UserMidiKeyboardCode_juce__midiKeyboardComponent_NoteOn] -- add your midi keyboard note-on handling code here..
        audioProcessor.enqueueKeyboardMidiMessage (juce::MidiMessage::noteOn (midiChannel, midiNoteNumber, velocity));
        //[/UserMidiKeyboardCode_juce__midiKeyboardComponent_NoteOn]
    }

    //[UserhandleNoteOn_Post]
    //[/UserhandleNoteOn_Post]
}

void GMSynthAudioProcessorEditor::handleNoteOff (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    //[UserhandleNoteOff_Pre]
    //[/UserhandleNoteOff_Pre]

    if (source == &juce__midiKeyboardComponentState)
    {
        //[UserMidiKeyboardCode_juce__midiKeyboardComponent_NoteOff] -- add your midi keyboard note-off handling code here..
        audioProcessor.enqueueKeyboardMidiMessage (juce::MidiMessage::noteOff (midiChannel, midiNoteNumber, velocity));
        //[/UserMidiKeyboardCode_juce__midiKeyboardComponent_NoteOff]
    }

    //[UserhandleNoteOff_Post]
    //[/UserhandleNoteOff_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GMSynthAudioProcessorEditor::configureChannelButton (juce::TextButton& button, int channel)
{
    button.setClickingTogglesState (true);
    button.setToggleState (audioProcessor.isChannelMuted (channel), juce::dontSendNotification);
    button.setColour (juce::TextButton::buttonColourId, juce::Colour (0xff50616a));
    button.setColour (juce::TextButton::buttonOnColourId, juce::Colour (0xff72dce8));
    button.setColour (juce::TextButton::textColourOffId, juce::Colours::white);
    button.setColour (juce::TextButton::textColourOnId, juce::Colours::black);
    button.setTooltip ("Mute MIDI channel " + juce::String (channel + 1));
}

void GMSynthAudioProcessorEditor::updateSoundFontLabel()
{
    const auto path = audioProcessor.getSoundFontPath();
    if (path.isEmpty())
    {
        labelSoundFontName->setText ("(not selected)", juce::dontSendNotification);
        labelSoundFontName->setTooltip ({});
        return;
    }

    const juce::File file (path);
    const auto displayName = file.existsAsFile()
        ? file.getFileName()
        : file.getFileName() + " (missing)";
    labelSoundFontName->setText (displayName, juce::dontSendNotification);
    labelSoundFontName->setTooltip (path);
}

void GMSynthAudioProcessorEditor::chooseSoundFont()
{
    if (soundFontChooser == nullptr)
        soundFontChooser.reset (new juce::FileChooser ("Select a SoundFont", {}, "*.sf2;*.SF2"));

    const auto safeThis = juce::Component::SafePointer<GMSynthAudioProcessorEditor> (this);
    const auto flags = juce::FileBrowserComponent::openMode
                     | juce::FileBrowserComponent::canSelectFiles;

    soundFontChooser->launchAsync (flags, [safeThis] (const juce::FileChooser& chooser)
    {
        if (safeThis == nullptr)
            return;

        const auto file = chooser.getResult();
        if (file.existsAsFile())
        {
            const auto result = safeThis->audioProcessor.loadSoundFontFile (file);
            if (result.wasOk())
                safeThis->updateSoundFontLabel();
            else
                juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon,
                                                        "SoundFont",
                                                        result.getErrorMessage());
        }
    });
}

void GMSynthAudioProcessorEditor::configureChannelStateLabels()
{
    const std::array<juce::Label*, 16> bankLabels
    {
        labelBnk1.get(), labelBnk2.get(), labelBnk3.get(), labelBnk4.get(),
        labelBnk5.get(), labelBnk6.get(), labelBnk7.get(), labelBnk8.get(),
        labelBnk9.get(), labelBnk10.get(), labelBnk11.get(), labelBnk12.get(),
        labelBnk13.get(), labelBnk14.get(), labelBnk15.get(), labelBnk16.get()
    };

    const std::array<juce::Label*, 16> programLabels
    {
        labelPrg1.get(), labelPrg2.get(), labelPrg3.get(), labelPrg4.get(),
        labelPrg5.get(), labelPrg6.get(), labelPrg7.get(), labelPrg8.get(),
        labelPrg9.get(), labelPrg10.get(), labelPrg11.get(), labelPrg12.get(),
        labelPrg13.get(), labelPrg14.get(), labelPrg15.get(), labelPrg16.get()
    };

    for (int channel = 0; channel < static_cast<int> (bankLabels.size()); ++channel)
    {
        auto* bankLabel = bankLabels[static_cast<size_t> (channel)];
        auto* programLabel = programLabels[static_cast<size_t> (channel)];

        bankLabel->setEditable (false, true, false);
        bankLabel->setTooltip ("MIDI bank for channel " + juce::String (channel + 1)
                               + " (double-click to edit)");
        bankLabel->onTextChange = [this, channel, bankLabel]
        {
            audioProcessor.setChannelBank (channel,
                                           juce::jlimit (0,
                                                        16383,
                                                        bankLabel->getText().getIntValue()));
        };

        programLabel->setEditable (false, true, false);
        programLabel->setTooltip ("MIDI program for channel " + juce::String (channel + 1)
                                  + " (double-click to edit)");
        programLabel->onTextChange = [this, channel, programLabel]
        {
            audioProcessor.setChannelProgram (channel,
                                              juce::jlimit (0,
                                                           127,
                                                           programLabel->getText().getIntValue()));
        };
    }
}

void GMSynthAudioProcessorEditor::updateChannelStateControls()
{
    if (sliderVolume != nullptr && ! sliderVolume->isMouseButtonDown())
        sliderVolume->setValue (audioProcessor.getMasterVolumeDb(), juce::dontSendNotification);

    const std::array<juce::TextButton*, 16> channelButtons
    {
        buttonCh1.get(), buttonCh2.get(), buttonCh3.get(), buttonCh4.get(),
        buttonCh5.get(), buttonCh6.get(), buttonCh7.get(), buttonCh8.get(),
        buttonCh9.get(), buttonCh10.get(), buttonCh11.get(), buttonCh12.get(),
        buttonCh13.get(), buttonCh14.get(), buttonCh15.get(), buttonCh16.get()
    };

    const std::array<juce::Slider*, 16> volumeSliders
    {
        sliderCh1Vol.get(), sliderCh1Vol2.get(), sliderCh1Vol3.get(), sliderCh1Vol4.get(),
        sliderCh1Vol5.get(), sliderCh1Vol6.get(), sliderCh1Vol7.get(), sliderCh1Vol8.get(),
        sliderCh1Vol9.get(), sliderCh1Vol10.get(), sliderCh1Vol11.get(), sliderCh1Vol12.get(),
        sliderCh1Vol13.get(), sliderCh1Vol14.get(), sliderCh1Vol15.get(), sliderCh1Vol16.get()
    };

    const std::array<juce::Slider*, 16> panSliders
    {
        sliderPan1.get(), sliderPan2.get(), sliderPan3.get(), sliderPan4.get(),
        sliderPan5.get(), sliderPan6.get(), sliderPan7.get(), sliderPan8.get(),
        sliderPan9.get(), sliderPan10.get(), sliderPan11.get(), sliderPan12.get(),
        sliderPan13.get(), sliderPan14.get(), sliderPan15.get(), sliderPan16.get()
    };

    const std::array<juce::Label*, 16> bankLabels
    {
        labelBnk1.get(), labelBnk2.get(), labelBnk3.get(), labelBnk4.get(),
        labelBnk5.get(), labelBnk6.get(), labelBnk7.get(), labelBnk8.get(),
        labelBnk9.get(), labelBnk10.get(), labelBnk11.get(), labelBnk12.get(),
        labelBnk13.get(), labelBnk14.get(), labelBnk15.get(), labelBnk16.get()
    };

    const std::array<juce::Label*, 16> programLabels
    {
        labelPrg1.get(), labelPrg2.get(), labelPrg3.get(), labelPrg4.get(),
        labelPrg5.get(), labelPrg6.get(), labelPrg7.get(), labelPrg8.get(),
        labelPrg9.get(), labelPrg10.get(), labelPrg11.get(), labelPrg12.get(),
        labelPrg13.get(), labelPrg14.get(), labelPrg15.get(), labelPrg16.get()
    };

    for (int channel = 0; channel < static_cast<int> (channelButtons.size()); ++channel)
    {
        const auto index = static_cast<size_t> (channel);
        if (! channelButtons[index]->isMouseButtonDown())
            channelButtons[index]->setToggleState (audioProcessor.isChannelMuted (channel),
                                                   juce::dontSendNotification);

        const auto state = audioProcessor.getChannelState (channel);
        if (! volumeSliders[index]->isMouseButtonDown())
            volumeSliders[index]->setValue (state.volume, juce::dontSendNotification);

        if (! panSliders[index]->isMouseButtonDown())
            panSliders[index]->setValue (state.pan, juce::dontSendNotification);

        if (! bankLabels[index]->isBeingEdited())
            bankLabels[index]->setText (juce::String (state.bank), juce::dontSendNotification);

        if (! programLabels[index]->isBeingEdited())
            programLabels[index]->setText (juce::String (state.program), juce::dontSendNotification);
    }

    if (buttonLog != nullptr)
        buttonLog->setButtonText (audioProcessor.isMidiLogging() ? "Stop Logging" : "Start Logging");
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GMSynthAudioProcessorEditor"
                 componentName="" parentClasses="public juce::AudioProcessorEditor"
                 constructorParams="GMSynthAudioProcessor&amp; p" variableInitialisers="AudioProcessorEditor (&amp;p), audioProcessor (p)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="706" initialHeight="384">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="" id="1ed530db359d1113" memberName="labelVolume" virtualName=""
         explicitFocusOrder="0" pos="400 16 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VOLUME" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="db15a5c69625a385" memberName="buttonSelectSF2" virtualName=""
              explicitFocusOrder="0" pos="216 16 152 24" buttonText="Load Sound Font"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="cc552c74e7abe3e1" memberName="labelSoundFontCaption"
         virtualName="" explicitFocusOrder="0" pos="16 16 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sound Font" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="85041d57ec61717e" memberName="labelSoundFontName"
         virtualName="" explicitFocusOrder="0" pos="16 40 352 24" edTextCol="ff000000"
         edBkgCol="0" labelText="(placeholder)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="5a6b251a7e4f30a0" memberName="sliderVolume" virtualName=""
          explicitFocusOrder="0" pos="472 16 216 24" min="-96.0" max="0.0"
          int="0.5" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="3.0"
          needsCallback="1" filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <MIDIKEYBOARDCOMPONENT name="new midi keyboard" id="c17108a4011f6bb3" memberName="juce__midiKeyboardComponent"
                         virtualName="" explicitFocusOrder="0" pos="48 0Rr 64M 32" orientation="horizontalKeyboard"
                         midiChannel="1" midiChannelsToDisplay="65535" velocity="1.0"
                         useMousePositionForVelocity="1" rangeStart="0" rangeEnd="127"
                         keyWidth="16.0" needsCallback="1"/>
  <TEXTBUTTON name="" id="78ec3bcdba845aea" memberName="buttonCh1" virtualName=""
              explicitFocusOrder="0" pos="48 72 40 24" buttonText="1" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="38d2a804fbf85548" memberName="buttonCh2" virtualName=""
              explicitFocusOrder="0" pos="88 72 40 24" buttonText="2" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c2f62dacc213f9be" memberName="buttonCh3" virtualName=""
              explicitFocusOrder="0" pos="128 72 40 24" buttonText="3" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="aa04960b255b7528" memberName="buttonCh4" virtualName=""
              explicitFocusOrder="0" pos="168 72 40 24" buttonText="4" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="7e00860e40df360e" memberName="buttonCh5" virtualName=""
              explicitFocusOrder="0" pos="208 72 40 24" buttonText="5" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="40145dd05593311a" memberName="buttonCh6" virtualName=""
              explicitFocusOrder="0" pos="248 72 40 24" buttonText="6" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="f5d679f3875bccc2" memberName="buttonCh7" virtualName=""
              explicitFocusOrder="0" pos="288 72 40 24" buttonText="7" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="39ea2d6f65a2a436" memberName="buttonCh8" virtualName=""
              explicitFocusOrder="0" pos="328 72 40 24" buttonText="8" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="3d89ed1e61c2dbe" memberName="buttonCh9" virtualName=""
              explicitFocusOrder="0" pos="368 72 40 24" buttonText="9" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="10de864d796b1d2e" memberName="buttonCh10" virtualName=""
              explicitFocusOrder="0" pos="408 72 40 24" buttonText="10" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="7db5182785886b35" memberName="buttonCh11" virtualName=""
              explicitFocusOrder="0" pos="448 72 40 24" buttonText="11" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="cf4f197dd11d2960" memberName="buttonCh12" virtualName=""
              explicitFocusOrder="0" pos="488 72 40 24" buttonText="12" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="db030d7910f7e946" memberName="buttonCh13" virtualName=""
              explicitFocusOrder="0" pos="528 72 40 24" buttonText="13" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="7df15639227653a0" memberName="buttonCh14" virtualName=""
              explicitFocusOrder="0" pos="568 72 40 24" buttonText="14" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="afa464001eb1a337" memberName="buttonCh15" virtualName=""
              explicitFocusOrder="0" pos="608 72 40 24" buttonText="15" connectedEdges="3"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="e3d813ff860b8f02" memberName="buttonCh16" virtualName=""
              explicitFocusOrder="0" pos="648 72 40 24" buttonText="16" connectedEdges="1"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="b26d9759f51d2eb3" memberName="sliderCh1Vol" virtualName=""
          explicitFocusOrder="0" pos="48 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="f5ddf2abedcacb8b" memberName="sliderCh1Vol2" virtualName=""
          explicitFocusOrder="0" pos="88 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="763f2410e5aab966" memberName="sliderCh1Vol3" virtualName=""
          explicitFocusOrder="0" pos="128 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="4d5d28d359facbdc" memberName="sliderCh1Vol4" virtualName=""
          explicitFocusOrder="0" pos="168 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="6470758a828da5b4" memberName="sliderCh1Vol5" virtualName=""
          explicitFocusOrder="0" pos="208 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="6bf3cc39c56d7352" memberName="sliderCh1Vol6" virtualName=""
          explicitFocusOrder="0" pos="248 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="69adb876d1e8d16c" memberName="sliderCh1Vol7" virtualName=""
          explicitFocusOrder="0" pos="288 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="f86f45eeff6fbcd7" memberName="sliderCh1Vol8" virtualName=""
          explicitFocusOrder="0" pos="328 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="1e6475394fcfe4b0" memberName="sliderCh1Vol9" virtualName=""
          explicitFocusOrder="0" pos="368 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="cfc662557826380d" memberName="sliderCh1Vol10" virtualName=""
          explicitFocusOrder="0" pos="408 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="8a0245f72aac90eb" memberName="sliderCh1Vol11" virtualName=""
          explicitFocusOrder="0" pos="448 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="3e648c7f03360142" memberName="sliderCh1Vol12" virtualName=""
          explicitFocusOrder="0" pos="488 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="bcf220d08e0ef91b" memberName="sliderCh1Vol13" virtualName=""
          explicitFocusOrder="0" pos="528 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="f93d7107268354e1" memberName="sliderCh1Vol14" virtualName=""
          explicitFocusOrder="0" pos="568 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="f9fa79a08146082" memberName="sliderCh1Vol15" virtualName=""
          explicitFocusOrder="0" pos="608 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="91caabad96437b44" memberName="sliderCh1Vol16" virtualName=""
          explicitFocusOrder="0" pos="648 232 40 107" min="0.0" max="127.0"
          int="1.0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="fcb94658e8642317" memberName="sliderPan1" virtualName=""
          explicitFocusOrder="0" pos="48 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="702be6f012d37550" memberName="sliderPan2" virtualName=""
          explicitFocusOrder="0" pos="88 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="26b8364eadd39218" memberName="sliderPan3" virtualName=""
          explicitFocusOrder="0" pos="128 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="95d92954e7d60dfd" memberName="sliderPan4" virtualName=""
          explicitFocusOrder="0" pos="168 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="ddca73a8e72becb7" memberName="sliderPan5" virtualName=""
          explicitFocusOrder="0" pos="208 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="20ff4b439158287c" memberName="sliderPan6" virtualName=""
          explicitFocusOrder="0" pos="248 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="81fbb2fd4e1ca3af" memberName="sliderPan7" virtualName=""
          explicitFocusOrder="0" pos="288 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="6527779880597f0b" memberName="sliderPan8" virtualName=""
          explicitFocusOrder="0" pos="328 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="4c84427dc39a20a9" memberName="sliderPan9" virtualName=""
          explicitFocusOrder="0" pos="368 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="a863ad6ebe77a607" memberName="sliderPan10" virtualName=""
          explicitFocusOrder="0" pos="408 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="28a63c4f99de9829" memberName="sliderPan11" virtualName=""
          explicitFocusOrder="0" pos="448 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="919d50d6f1b030f8" memberName="sliderPan12" virtualName=""
          explicitFocusOrder="0" pos="488 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="e8799395ffc7b6b2" memberName="sliderPan13" virtualName=""
          explicitFocusOrder="0" pos="528 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="8e6bd3304393aeca" memberName="sliderPan14" virtualName=""
          explicitFocusOrder="0" pos="568 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="8532115bfdfa0d58" memberName="sliderPan15" virtualName=""
          explicitFocusOrder="0" pos="608 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <SLIDER name="" id="209231fe136a8ce4" memberName="sliderPan16" virtualName=""
          explicitFocusOrder="0" pos="648 160 40 64" min="0.0" max="127.0"
          int="1.0" style="Rotary" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"
          filmstripImage="" filmstripFrames="1" filmstripVertical="1"/>
  <LABEL name="" id="d39505f9aee4d339" memberName="labelCh" virtualName=""
         explicitFocusOrder="0" pos="8 72 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="CH" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="ecf35aa435cf98d8" memberName="labelPAN" virtualName=""
         explicitFocusOrder="0" pos="8 160 40 64" edTextCol="ff000000"
         edBkgCol="0" labelText="PAN" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="f7dbd6a74abeba33" memberName="labelPAN2" virtualName=""
         explicitFocusOrder="0" pos="8 232 40 112" edTextCol="ff000000"
         edBkgCol="0" labelText="VOL" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="cff78b87765e08d0" memberName="labelPrg1" virtualName=""
         explicitFocusOrder="0" pos="48 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="e1ecd271b3529993" memberName="labelPrg2" virtualName=""
         explicitFocusOrder="0" pos="88 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="2af027bed579072e" memberName="labelPrg3" virtualName=""
         explicitFocusOrder="0" pos="128 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="f9c74e2dc37cb327" memberName="labelPrg4" virtualName=""
         explicitFocusOrder="0" pos="168 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="8682736061b8261b" memberName="labelPrg5" virtualName=""
         explicitFocusOrder="0" pos="208 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="4471ec727c3f31e" memberName="labelPrg6" virtualName=""
         explicitFocusOrder="0" pos="248 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="6ce3a1496aa92603" memberName="labelPrg7" virtualName=""
         explicitFocusOrder="0" pos="288 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="24bb3fbd97582e95" memberName="labelPrg8" virtualName=""
         explicitFocusOrder="0" pos="328 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="5bffafbb3281c0fd" memberName="labelPrg9" virtualName=""
         explicitFocusOrder="0" pos="368 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="b3a9f093c4584a3f" memberName="labelPrg10" virtualName=""
         explicitFocusOrder="0" pos="408 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="c680593f64106947" memberName="labelPrg11" virtualName=""
         explicitFocusOrder="0" pos="448 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="f94c1d1a542c7145" memberName="labelPrg12" virtualName=""
         explicitFocusOrder="0" pos="488 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="4ea73855e09b4e83" memberName="labelPrg13" virtualName=""
         explicitFocusOrder="0" pos="528 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="1da924370a81a979" memberName="labelPrg14" virtualName=""
         explicitFocusOrder="0" pos="568 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="59e2fd79065a5d30" memberName="labelPrg15" virtualName=""
         explicitFocusOrder="0" pos="608 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="dfbea42a6873cc9c" memberName="labelPrg16" virtualName=""
         explicitFocusOrder="0" pos="648 136 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="1e8baf64e375d884" memberName="labelPrg" virtualName=""
         explicitFocusOrder="0" pos="8 136 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PRG" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="55dd4b2149a5c4ee" memberName="labelBnk1" virtualName=""
         explicitFocusOrder="0" pos="48 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="48e9ee514e4b3670" memberName="labelBNK" virtualName=""
         explicitFocusOrder="0" pos="8 112 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BNK" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="2a14217077f3fb5c" memberName="labelBnk2" virtualName=""
         explicitFocusOrder="0" pos="88 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="17c3aa451bddb26f" memberName="labelBnk3" virtualName=""
         explicitFocusOrder="0" pos="128 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="caa4800d3931f41a" memberName="labelBnk4" virtualName=""
         explicitFocusOrder="0" pos="168 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="91953c4fbb1c2d01" memberName="labelBnk5" virtualName=""
         explicitFocusOrder="0" pos="208 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="83ea8c83ea5e5f4" memberName="labelBnk6" virtualName=""
         explicitFocusOrder="0" pos="248 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="27e47ee4a1a6d83f" memberName="labelBnk7" virtualName=""
         explicitFocusOrder="0" pos="288 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="bcc16070840e5c1a" memberName="labelBnk8" virtualName=""
         explicitFocusOrder="0" pos="328 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="baf8161e644198c8" memberName="labelBnk9" virtualName=""
         explicitFocusOrder="0" pos="368 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="212a591bdc7d497d" memberName="labelBnk10" virtualName=""
         explicitFocusOrder="0" pos="408 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="dddd4b1d34084ebf" memberName="labelBnk11" virtualName=""
         explicitFocusOrder="0" pos="448 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="e2860bcf2e2d25db" memberName="labelBnk12" virtualName=""
         explicitFocusOrder="0" pos="488 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="11dafcc96282fd9d" memberName="labelBnk13" virtualName=""
         explicitFocusOrder="0" pos="528 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="c562e8cca00a202d" memberName="labelBnk14" virtualName=""
         explicitFocusOrder="0" pos="568 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="f5322b11a10743e" memberName="labelBnk15" virtualName=""
         explicitFocusOrder="0" pos="608 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="5af56723212cab72" memberName="labelBnk16" virtualName=""
         explicitFocusOrder="0" pos="648 112 40 24" outlineCol="ff8e989b"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="" id="fce1d63e56e9c7d7" memberName="buttonLog" virtualName=""
              explicitFocusOrder="0" pos="392 40 136 24" buttonText="Start Logging"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

