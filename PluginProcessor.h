/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class CustomChorusAudioProcessor  : public AudioProcessor
{
public:
	float volume[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float delay[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	bool voiceEnabled[4] = { false, false, false, false };
	bool lfoEnabled[4][3] = { {false, false, false},{ false, false, false },{ false, false, false },{ false, false, false } };
	int voiceDelaySamples[4] = { 0, 0, 0, 0 };
	float maxDelay = 1.0f;
	int maxDelaySamples;
	double currentSampleRate;
	int elapsedSamples = 0;

	AudioSampleBuffer delayBuffer;

    //==============================================================================
    CustomChorusAudioProcessor();
    ~CustomChorusAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomChorusAudioProcessor)
};
