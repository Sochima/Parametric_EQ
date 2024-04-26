/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Omenkeukwu_Sochima_hw6AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Omenkeukwu_Sochima_hw6AudioProcessorEditor (Omenkeukwu_Sochima_hw6AudioProcessor&);
    ~Omenkeukwu_Sochima_hw6AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
//    enum
//    {
//        paramControlHeight = 60,
//        paramLabelWidth = 60,
//        paramSliderWidth = 300
//    };
    
    //Guving the ValuetreeState Slider Attachment component an alias
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
    
    

    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Omenkeukwu_Sochima_hw6AudioProcessor& audioProcessor;
    
    
    //Decalaring the various objects for the low band GUI
    juce::Label pluginLabel;
    
    juce::Label lowBandLabel;
    juce::Label lowGainLabel;
    juce::Label lowFreqLabel;
    juce::Slider lowGainSlider;
    juce::Slider lowFreqSlider;
    juce::ToggleButton lowShelfButton;
    
    //Declaring attachment components which would connect the UI to the parameters for the low band
    std::unique_ptr<SliderAttachment> lowGainAttachment;
    std::unique_ptr<SliderAttachment> lowFreqAttachment;
    std::unique_ptr<ButtonAttachment> lowShelfAttachment;
    
    
    
    //Decalaring the various objects for the mid band GUI
    juce::Label midBandLabel;
    juce::Label midGainLabel;
    juce::Label midFreqLabel;
    juce::Slider midGainSlider;
    juce::Slider midFreqSlider;
    
    //Declaring attachment components which would connect the UI to the parameters for the mid band
    std::unique_ptr<SliderAttachment> midGainAttachment;
    std::unique_ptr<SliderAttachment> midFreqAttachment;
    
    
    //Decalaring the various objects for the high band GUI
    juce::Label highBandLabel;
    juce::Label highGainLabel;
    juce::Label highFreqLabel;
    juce::Slider highGainSlider;
    juce::Slider highFreqSlider;
    juce::ToggleButton highShelfButton;
    
    //Declaring attachment components which would connect the UI to the parameters for the high band
    std::unique_ptr<SliderAttachment> highGainAttachment;
    std::unique_ptr<SliderAttachment> highFreqAttachment;
    std::unique_ptr<ButtonAttachment> highShelfAttachment;
    
    
    //Declaring Image object for the background image of the plugin
    juce::Image backgroundImage;
    
    
    

   
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Omenkeukwu_Sochima_hw6AudioProcessorEditor)
};
