/*
  ==============================================================================

    VoiceComponent.h
    Created: 22 Nov 2017 3:41:13pm
    Author:  spens

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VoiceComponent : public Component
{
public:
	//Voice Component parameters that change from component to component.
	char* voiceTitle = "Voice 1";   

	//Constant Voice Component Parameters.
	int voiceWidth = 300;
	int voiceHeight;
	int voicePadding = 5;
	int voiceLabelWidth = 80;
	int voiceTitleHeight = 35;
	char* voiceLabels[4] = { "Volume", "Delay", "EQ", "LFO" };
	int voiceLabelHeights[4] = { 30, 30, 70, 70 };
	int lfoToggleWidth = 25;

	//Calculated GUI Positions
	int voiceLabelYs[4];
	int subComponentWidth = voiceWidth - voiceLabelWidth - voicePadding * 3;
	int subComponentX = voiceLabelWidth + voicePadding * 2;

	//Sub-Component Declarations
	ToggleButton voiceToggle;
	ToggleButton lfoToggle[3];
	Slider volumeSlider;
	Slider delaySlider;
	Slider lfoRateSlider;
	Slider lfoDepthSlider;

	VoiceComponent() {
		voiceLabelYs[0] = voiceTitleHeight + voicePadding;
		for (int label = 1; label < 4; ++label) {
			voiceLabelYs[label] = voiceLabelYs[label - 1] + voiceLabelHeights[label - 1] + voicePadding;
		}
		voiceHeight = voiceLabelYs[3] + voiceLabelHeights[3] + voicePadding;

		//Set sub-component parameters
		for (int label = 0; label < 3; ++label) {
			addAndMakeVisible(lfoToggle[label]);
			lfoToggle[label].setBounds(voicePadding, voiceLabelYs[label], lfoToggleWidth, voiceLabelHeights[label]);
		}

		addAndMakeVisible(voiceToggle);
		voiceToggle.setBounds(voiceWidth - 50, voicePadding, 50, voiceTitleHeight - voicePadding*2);

		addAndMakeVisible(volumeSlider);
		volumeSlider.setRange(0.0, 1.0);
		volumeSlider.setBounds(subComponentX, voiceLabelYs[0], subComponentWidth, voiceLabelHeights[0]);

		addAndMakeVisible(delaySlider);
		delaySlider.setRange(0.0, 0.1);
		delaySlider.setBounds(subComponentX, voiceLabelYs[1], subComponentWidth, voiceLabelHeights[1]);

		addAndMakeVisible(lfoRateSlider);
		lfoRateSlider.setRange(0.0, 1.0);
		lfoRateSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		lfoRateSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
		lfoRateSlider.setBounds(subComponentX, voiceLabelYs[3], subComponentWidth/2, voiceLabelHeights[3]);
		
		addAndMakeVisible(lfoDepthSlider);
		lfoDepthSlider.setRange(0.0, 1.0);
		lfoDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
		lfoDepthSlider.setBounds(subComponentX + subComponentWidth / 2, voiceLabelYs[3], subComponentWidth/2, voiceLabelHeights[3]);
		lfoDepthSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
	}

	~VoiceComponent() {
	}

	//==============================================================================
	void paint(Graphics& g) override {
		Font font1("Lovelo Line", 60.0f, Font::plain);
		Font font2("Caviar Dreams", 30.0f, Font::bold);
		Font font3("Caviar Dreams", 20.0f, Font::plain);

		//Re-used Gui Paint Objects
		Rectangle<float> voiceRectangle(0, 0, voiceWidth, voiceHeight);
		Rectangle<float> voiceTitleRectangle(0, 0, voiceWidth, voiceTitleHeight);

		//Draw Module Background
		g.setColour(Colours::darkcyan);
		g.fillRoundedRectangle(voiceRectangle, voicePadding);

		//Draw module title background
		g.setColour(Colours::cadetblue);
		g.fillRoundedRectangle(voiceTitleRectangle, voicePadding);

		//Draw LFO strips
		//g.setColour(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
		//g.setColour(Colour(91, 117, 142));
		g.setColour(Colour(73, 86, 89));
		//Vertical
		g.fillRoundedRectangle(voicePadding, voiceTitleHeight + voicePadding, lfoToggleWidth, voiceHeight - voiceTitleHeight - voicePadding * 2, voicePadding);
		//Horizontal
		g.fillRoundedRectangle(voicePadding, voiceLabelYs[3], voiceWidth - voicePadding * 2, voiceLabelHeights[3], voicePadding);

		g.setColour(Colours::antiquewhite);
		g.setFont(font2);
		g.drawText(voiceTitle, voicePadding, 0, voiceWidth, voiceTitleHeight, Justification::centredLeft, true);

		g.setFont(font3);
		for (int label = 0; label < 4; ++label) {
			g.drawText(voiceLabels[label], voicePadding*2 + lfoToggleWidth, voiceLabelYs[label], voiceLabelWidth, voiceLabelHeights[label], Justification::centredLeft, true);
		}
	}
	void resized() override {

	}

private:


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VoiceComponent)
};