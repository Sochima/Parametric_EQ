/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Omenkeukwu_Sochima_hw6AudioProcessor::Omenkeukwu_Sochima_hw6AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
//Initilialzing the gain, frequency, and toggle button parameters for each band in the ValueTreeState
, parameters(*this,
             nullptr, juce::Identifier("EQ"),
             {std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lowgain", 1), "Low-band Gain", -20, 20, 0),  /*Parameter 1 with parameter name and ID, parameter label, min valu, max value, default value. The parameter has been made unique*/
            std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("lowfrequency", 1), "Low-band Frequency", 10,1000,500), /*Parameter 2 with parameter name and ID, parameter value, default boolean value */
            std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("midgain",1), "Mid-band Gain", -20, 20, 0),
            std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("midfrequency",1), "Mid-band Frequency", 500, 5000, 2000),
    
            std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("highgain",1), "High-band Gain", -20, 20, 0),
           std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("highfrequency",1), "High-band Frequency", 2000, 10000, 5000),
    
           std::make_unique<juce::AudioParameterBool>(juce::ParameterID("lowshelf",1), "Low Shelf", false),
          std::make_unique<juce::AudioParameterBool>(juce::ParameterID("highshelf",1), "High Shelf", false)
    
})
    
    

#endif
{
    
    //Initialzing highshelf and lowshelf parameters with their respective rawvalues in the ValueTreeState
    DBG("PluginProcessor Constructor");
    lowShelfParameter = parameters.getRawParameterValue("lowshelf");
    highShelfParameter = parameters.getRawParameterValue("highshelf");
    
    DBG("Low Shelf Default: " << lowShelfParameter->load());
    
    
    //Initialzing gain and freqeuncy parameters for each band  with their respective rawvalues in the ValueTreeState
    lowGainParameter = parameters.getRawParameterValue("lowgain");
    midGainParameter = parameters.getRawParameterValue("midgain");
    highGainParameter = parameters.getRawParameterValue("highgain");
    
    lowFreqParameter = parameters.getRawParameterValue("lowfrequency");
    midFreqParameter = parameters.getRawParameterValue("midfrequency");
    highFreqParameter = parameters.getRawParameterValue("highfrequency");
    
   
}

Omenkeukwu_Sochima_hw6AudioProcessor::~Omenkeukwu_Sochima_hw6AudioProcessor()
{
}

//==============================================================================
const juce::String Omenkeukwu_Sochima_hw6AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Omenkeukwu_Sochima_hw6AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Omenkeukwu_Sochima_hw6AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Omenkeukwu_Sochima_hw6AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Omenkeukwu_Sochima_hw6AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Omenkeukwu_Sochima_hw6AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Omenkeukwu_Sochima_hw6AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Omenkeukwu_Sochima_hw6AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Omenkeukwu_Sochima_hw6AudioProcessor::getProgramName (int index)
{
    return {};
}

void Omenkeukwu_Sochima_hw6AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Omenkeukwu_Sochima_hw6AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    
    //Initializing the processSpec object with the processor's sample rate, block size and number of channels
    
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    
    //Callin the prepare and reset function for each of the 3 StateVariableTPTFilter objects
    
    lowBand.prepare(spec);
    midBand.prepare(spec);
    highBand.prepare(spec);
    
    
    updateParameters();
    
    
    lowBand.reset();
    midBand.reset();
    highBand.reset();
    
    
}

void Omenkeukwu_Sochima_hw6AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Omenkeukwu_Sochima_hw6AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void Omenkeukwu_Sochima_hw6AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    
    //Obtaining the gain parameter for each of the 3 bands
    float lowGain = *lowGainParameter;
    float midGain = *midGainParameter;
    float highGain = *highGainParameter;
    
    //Converting the decibel gain for each of he three bands to linear gain
    float linearLowGain = juce::Decibels::decibelsToGain(lowGain);
    float linearMidGain = juce::Decibels::decibelsToGain(midGain);
    float linearHighGain = juce::Decibels::decibelsToGain(highGain);
    
   
    
    DBG("Total Input Channels: " << totalNumInputChannels);
    DBG("Total Output Channels: " << totalNumOutputChannels);
    DBG("Num Samples: " << buffer.getNumSamples());
    
    
    //Update parameters function is used to detect and update the parameters when the user makes a change
    updateParameters();

    //audio proceesing nested loop
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //creating read and write pointers the the audio processors buffer
        auto* channelData = buffer.getWritePointer (channel);
        auto* channelInputData = buffer.getReadPointer(channel);

        /*Processing each sample in the buffer by calling the processsample function of each of the filters and passing the sample as input.
         Then the gain for each band is applied to tits respective filter.*/
        for(int sample = 0; sample < numSamples; ++sample)
        {
            
            channelData[sample] = (lowBand.processSample(channel, channelInputData[sample]) * linearLowGain) + (midBand.processSample(channel, channelData[sample])*linearMidGain) + (highBand.processSample(channel, channelInputData[sample])*linearHighGain);
        }
        
        
       
    }
}

//==============================================================================
bool Omenkeukwu_Sochima_hw6AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Omenkeukwu_Sochima_hw6AudioProcessor::createEditor()
{
    return new Omenkeukwu_Sochima_hw6AudioProcessorEditor (*this);
}

//==============================================================================
void Omenkeukwu_Sochima_hw6AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    DBG("getStateInformation");         // SP [P9]
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Omenkeukwu_Sochima_hw6AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    DBG("setStateInformation");         // SP [10]
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr) {
        if (xmlState->hasTagName(parameters.state.getType())) {
            parameters.replaceState (juce::ValueTree::fromXml(*xmlState));
        }
    }
}

void Omenkeukwu_Sochima_hw6AudioProcessor::updateParameters()
{
    
    //getting tand updating the frequency values ofr each of the bands when the chnaged by the user
    float lowFreq = *parameters.getRawParameterValue("lowfrequency");
    float midFreq = *parameters.getRawParameterValue("midfrequency");
    float highFreq = *parameters.getRawParameterValue("highfrequency");
    
    
    //Setting the filter type for the mid band EQ
    
    midBand.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    
    
    /*checking if the lowshelf toggle button has been clciked
     and setting the filter type of the low band EQ based on the resukt
    */
    if(lowShelfParameter->load())
    {
       lowBand.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    }
    else
    {
        lowBand.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    }
    
    
    /*checking if the highshelf toggle button has been clciked
     and setting the filter type of the high band EQ based on the resukt
    */
    if(highShelfParameter->load())
    {
       highBand.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    }
    else
    {
        highBand.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    }
    
    //Setting the cutoff freqeuncy for each of the bands
    lowBand.setCutoffFrequency(lowFreq);
    midBand.setCutoffFrequency(midFreq);
    highBand.setCutoffFrequency(highFreq);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Omenkeukwu_Sochima_hw6AudioProcessor();
}
