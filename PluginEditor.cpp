/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CustomChorusAudioProcessorEditor::CustomChorusAudioProcessorEditor (CustomChorusAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setSize(width, height);

	for (int voice = 0; voice < numVoices; ++voice) {
		addAndMakeVisible(voices[voice]);
		voices[voice].setBounds(padding * (voice + 1) + voices[voice].voiceWidth * voice , headerHeight, voices[0].voiceWidth, voices[0].voiceHeight);
		voices[voice].delaySlider.addListener(this);
		voices[voice].volumeSlider.addListener(this);
		voices[voice].voiceToggle.addListener(this);
		for (int label = 0; label < 3; ++label) {
			voices[voice].lfoToggle[label].addListener(this);
		}
	}
	voices[1].voiceTitle = "Voice 2";
	voices[2].voiceTitle = "Voice 3";
	voices[3].voiceTitle = "Voice 4";

	addAndMakeVisible(debugLabel);
	debugLabel.setBounds(600, 15, 100, 30);
	debugLabel.setText("hello", dontSendNotification);
}

CustomChorusAudioProcessorEditor::~CustomChorusAudioProcessorEditor()
{
}

//==============================================================================
void CustomChorusAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

	Font font1("Lovelo Line", 60.0f, Font::plain);
	Font font2("Caviar Dreams", 30.0f, Font::bold);
	Font font3("Caviar Dreams", 20.0f, Font::plain);

	g.setColour(Colours::antiquewhite);
	g.setFont(font1);
	g.drawText("Custom Chorus", padding, 0.0, width, headerHeight, Justification::centredLeft);
	g.setFont(font3);
	g.drawText("~Saling To Mars", 0.0, headerHeight + voices[0].voiceHeight, width - padding, footerHeight, Justification::centredRight);
}

void CustomChorusAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void CustomChorusAudioProcessorEditor::buttonClicked(Button* button) {
	for (int voice = 0; voice < numVoices; ++voice) {
		if (button == &voices[voice].voiceToggle) {
			processor.voiceEnabled[voice] = button->getToggleState();
			debugLabel.setText(juce::String((int)processor.voiceEnabled[voice]), dontSendNotification);
		}
		else {
			for (int label = 0; label < 3; ++label) {
				if (button == &voices[voice].lfoToggle[label]) {
					processor.lfoEnabled[voice][label] = button->getToggleState();
					debugLabel.setText(juce::String((int)processor.lfoEnabled[voice][label]), dontSendNotification);
				}
			}
		}
	}
}

void CustomChorusAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	//Check for volume sliders.
	for (int voice = 0; voice < numVoices; ++voice) {
		if (slider == &voices[voice].volumeSlider) {
			processor.volume[voice] = voices[voice].volumeSlider.getValue();
			debugLabel.setText(juce::String(processor.volume[voice]), dontSendNotification);
		}
		else if (slider == &voices[voice].delaySlider) {
			processor.delay[voice] = voices[voice].delaySlider.getValue();
			processor.voiceDelaySamples[voice] = processor.currentSampleRate * processor.delay[voice];
			debugLabel.setText(juce::String(processor.voiceDelaySamples[voice]), dontSendNotification);
		}
	}
}