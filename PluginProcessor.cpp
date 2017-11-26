/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


CustomChorusAudioProcessor::CustomChorusAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

CustomChorusAudioProcessor::~CustomChorusAudioProcessor()
{
}

const String CustomChorusAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CustomChorusAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CustomChorusAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CustomChorusAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CustomChorusAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CustomChorusAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CustomChorusAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CustomChorusAudioProcessor::setCurrentProgram (int index)
{
}

const String CustomChorusAudioProcessor::getProgramName (int index)
{
    return {};
}

void CustomChorusAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void CustomChorusAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	currentSampleRate = sampleRate;
	maxDelaySamples = (int)(maxDelay * currentSampleRate) + 1;
	for (int voice = 0; voice < 4; ++voice) {
		voiceDelaySamples[voice] = (int)(currentSampleRate * delay[voice]);
	}
	delayBuffer.setSize(getNumInputChannels(), maxDelaySamples, true, true, false);
}

void CustomChorusAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CustomChorusAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CustomChorusAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
	// audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
		int index;
		int delayIndex;
		float currentSample;
        float* channelData = buffer.getWritePointer (channel);
		float* delayChannelData = delayBuffer.getWritePointer(channel);
		for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
			currentSample = channelData[sample];
			channelData[sample] = 0;
			index = (elapsedSamples + sample + 1) % maxDelaySamples;
			delayChannelData[index] = currentSample;
			for (int voice = 0; voice < 4; ++voice) {
				if (elapsedSamples > voiceDelaySamples[voice]) {
					delayIndex = (elapsedSamples - voiceDelaySamples[voice] + sample) % maxDelaySamples;
					channelData[sample] += volume[voice] * delayChannelData[delayIndex];
				}
			}
		}
    }
	elapsedSamples += buffer.getNumSamples();
}

//==============================================================================
bool CustomChorusAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CustomChorusAudioProcessor::createEditor()
{
    return new CustomChorusAudioProcessorEditor (*this);
}

//==============================================================================
void CustomChorusAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CustomChorusAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CustomChorusAudioProcessor();
}
