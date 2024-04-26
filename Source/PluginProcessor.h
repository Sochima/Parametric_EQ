/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Omenkeukwu_Sochima_hw6AudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Omenkeukwu_Sochima_hw6AudioProcessor();
    ~Omenkeukwu_Sochima_hw6AudioProcessor() override;

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
    
    //Value tree state parameter function
    juce::AudioProcessorValueTreeState parameters;
    
    
    //Update Parameters Function prototype
    void updateParameters();

private:
    
    //Initializing ProcessSpec Parameter
    juce::dsp::ProcessSpec spec;
    
    
    //Declaring StateVariableTPTFilter class objects for the 3 freq bands
    juce::dsp::StateVariableTPTFilter<float> lowBand;
    juce::dsp::StateVariableTPTFilter<float> midBand;
    juce::dsp::StateVariableTPTFilter<float> highBand;
    

   //Decalring atomic parameter pointers for accessing togglebutton, gain and freqeuncy parameters for each band in ValueTreeState
    
    std::atomic<float> * lowShelfParameter = nullptr;
    std::atomic<float> * highShelfParameter = nullptr;
    
    std::atomic<float> * lowGainParameter = nullptr;
    std::atomic<float> * midGainParameter = nullptr;
    std::atomic<float> * highGainParameter = nullptr;
    
    std::atomic<float> * lowFreqParameter = nullptr;
    std::atomic<float> * midFreqParameter = nullptr;
    std::atomic<float> * highFreqParameter = nullptr;
   
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Omenkeukwu_Sochima_hw6AudioProcessor)
};
