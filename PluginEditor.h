/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "VoiceComponent.h"


//==============================================================================
/**
*/
class CustomChorusAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, Button::Listener
{
public:

	VoiceComponent voices[4];
	Label debugLabel;

	int numVoices = 4;
	int padding = 10;
	int headerHeight = 60;
	int footerHeight = 30;
	int height = headerHeight + voices[0].voiceHeight + footerHeight;
	int width = padding*(numVoices + 1) + voices[0].voiceWidth * numVoices;

    CustomChorusAudioProcessorEditor (CustomChorusAudioProcessor&);
    ~CustomChorusAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CustomChorusAudioProcessor& processor;

	void sliderValueChanged(Slider* slider) override;
	
	void buttonClicked(Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomChorusAudioProcessorEditor)
};
