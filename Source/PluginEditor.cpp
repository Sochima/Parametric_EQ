/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Omenkeukwu_Sochima_hw6AudioProcessorEditor::Omenkeukwu_Sochima_hw6AudioProcessorEditor (Omenkeukwu_Sochima_hw6AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    //Creating the width and size of the editor
    auto width = 800;
    auto height = 400;
    setSize (width, height);
    
    //Custom colours for the text
    auto myMainColour = 0xff591408;
    auto mySubColour = 0xffe4430c;
    
    //Customizing the look and feel of the knob sliders and textbox
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(myMainColour));
    getLookAndFeel().setColour(juce::Slider::textBoxTextColourId, juce::Colour(myMainColour));
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour(myMainColour));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(mySubColour));


    //Plugin Label
    pluginLabel.setText("3-Band Parametric EQ", juce::dontSendNotification);
    pluginLabel.setFont(juce::Font("Gill Sans", 36, juce::Font::bold));
    pluginLabel.setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(pluginLabel);
    pluginLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    
    
    //Band Labels
    lowBandLabel.setText("Low", juce::dontSendNotification);
    lowBandLabel.setFont(juce::Font("Montserrat", 24, juce::Font::bold));
    lowBandLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(lowBandLabel);
    lowBandLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    
    midBandLabel.setText("Mid", juce::dontSendNotification);
    midBandLabel.setFont(juce::Font("Montserrat", 24, juce::Font::bold));
    midBandLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(midBandLabel);
    midBandLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    
    highBandLabel.setText("High", juce::dontSendNotification);
    highBandLabel.setFont(juce::Font("Montserrat", 24, juce::Font::bold));
    highBandLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(highBandLabel);
    highBandLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    
    
    //Gain knob Labels
    lowGainLabel.setText("Gain", juce::dontSendNotification);
    lowGainLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    lowGainLabel.setJustificationType(juce::Justification::centred);
    lowGainLabel.setColour(juce::Label::textColourId, juce::Colour(mySubColour));
    addAndMakeVisible(lowGainLabel);
    
    midGainLabel.setText("Gain", juce::dontSendNotification);
    midGainLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    midGainLabel.setJustificationType(juce::Justification::centred);
    midGainLabel.setColour(juce::Label::textColourId, juce::Colour(mySubColour));
    addAndMakeVisible(midGainLabel);
    
    highGainLabel.setText("Gain", juce::dontSendNotification);
    highGainLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    highGainLabel.setJustificationType(juce::Justification::centred);
    highGainLabel.setColour(juce::Label::textColourId, juce::Colour(mySubColour));
    addAndMakeVisible(highGainLabel);
    
    
    //Band Gain Knobs
    lowGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    lowGainSlider.setTextValueSuffix(" dB");
    lowGainAttachment.reset(new SliderAttachment(audioProcessor.parameters, "lowgain", lowGainSlider));
    addAndMakeVisible(lowGainSlider);
    
   midGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midGainSlider.setTextValueSuffix(" dB");
    midGainAttachment.reset(new SliderAttachment(audioProcessor.parameters, "midgain", midGainSlider));
    addAndMakeVisible(midGainSlider);
    
    highGainSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    highGainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    highGainSlider.setTextValueSuffix(" dB");
   highGainAttachment.reset(new SliderAttachment(audioProcessor.parameters, "highgain", highGainSlider));
    addAndMakeVisible(highGainSlider);
    
    
    //Frequency Knob labels
    lowFreqLabel.setText("Frequency", juce::dontSendNotification);
    lowFreqLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    lowFreqLabel.setJustificationType(juce::Justification::horizontallyCentred);
    lowFreqLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    addAndMakeVisible(lowFreqLabel);
    
    midFreqLabel.setText("Frequency", juce::dontSendNotification);
    midFreqLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    midFreqLabel.setJustificationType(juce::Justification::horizontallyCentred);
    midFreqLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    addAndMakeVisible(midFreqLabel);
   
    highFreqLabel.setText("Frequency", juce::dontSendNotification);
    highFreqLabel.setFont(juce::Font("Montserrat", 16.0f,juce::Font::bold));
    highFreqLabel.setJustificationType(juce::Justification::horizontallyCentred);
    highFreqLabel.setColour(juce::Label::textColourId, juce::Colour(myMainColour));
    addAndMakeVisible(highFreqLabel);
    
    
    //Band Frequency Knobs
    lowFreqSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    lowFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    lowFreqSlider.setTextValueSuffix(" Hz");
    lowFreqAttachment.reset(new SliderAttachment(audioProcessor.parameters, "lowfrequency", lowFreqSlider));
    addAndMakeVisible(lowFreqSlider);

   midFreqSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    midFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    midFreqSlider.setTextValueSuffix(" Hz");
    midFreqAttachment.reset(new SliderAttachment(audioProcessor.parameters, "midfrequency", midFreqSlider));
    addAndMakeVisible(midFreqSlider);

    highFreqSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    highFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    highFreqSlider.setTextValueSuffix(" Hz");
   highFreqAttachment.reset(new SliderAttachment(audioProcessor.parameters, "highfrequency", highFreqSlider));
    addAndMakeVisible(highFreqSlider);
    
    
    //Low and High Shelf Buttons
    lowShelfButton.setButtonText("Low Shelf");
    lowShelfButton.setColour(juce::ToggleButton::textColourId, juce::Colour(mySubColour));
    lowShelfButton.setColour(juce::ToggleButton::tickColourId, juce::Colour(mySubColour));
    lowShelfButton.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colour(mySubColour));
    lowShelfAttachment.reset(new ButtonAttachment(audioProcessor.parameters, "lowshelf", lowShelfButton));
    addAndMakeVisible(lowShelfButton);
    
    highShelfButton.setButtonText("High Shelf");
    highShelfButton.setColour(juce::ToggleButton::textColourId, juce::Colour(mySubColour));
    highShelfButton.setColour(juce::ToggleButton::tickColourId, juce::Colour(mySubColour));
    highShelfButton.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colour(mySubColour));
    highShelfAttachment.reset(new ButtonAttachment(audioProcessor.parameters, "highshelf", highShelfButton));
    addAndMakeVisible(highShelfButton);

    //Background Image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_image_png, BinaryData::background_image_pngSize);
    
    
}

Omenkeukwu_Sochima_hw6AudioProcessorEditor::~Omenkeukwu_Sochima_hw6AudioProcessorEditor()
{
}

//==============================================================================
void Omenkeukwu_Sochima_hw6AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    
    //Initializing border and getting bounds for the main rectangle
    auto border = 5;
    auto area = getLocalBounds().reduced(border*4);
    auto areaWidth = area.getWidth();
    auto areaHeight = area.getHeight();
    auto widthRatio = 1.0/3.0;
    
    DBG("Area Width: " << areaWidth);
    
    auto pluginLabelArea =  area.removeFromTop(areaHeight*(1.0/8.0));
    
    //creating the rectangles for the midband and low band area
    auto lowBandArea = area.removeFromLeft(areaWidth*widthRatio);
    auto midBandArea = area.removeFromLeft(areaWidth*widthRatio);
    
    //Defining custom colours for the 3 bands
    auto lowBandColour = 0x33bb5411;
    auto midBandColour = 0x33f56b1a;
    auto highBandColour = 0x33fcba39;
    
    //Drawing background image and filling band rectangles with colour
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
    
    g.setColour(juce::Colour(highBandColour));
    g.fillRect(area);
    
    g.setColour(juce::Colour(lowBandColour));
    g.fillRect(lowBandArea);
    
    g.setColour(juce::Colour(midBandColour));
    g.fillRect(midBandArea);
    
   
}

void Omenkeukwu_Sochima_hw6AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto border = 5;
    
    auto area = getLocalBounds().reduced(border*4);
    auto areaWidth = area.getWidth();
    auto widthRatio = 1.0/3.0;
    auto areaHeight = area.getHeight();
    
    //Creating the rectangles for each of the UI Components
    auto pluginLabelArea =  area.removeFromTop(areaHeight*(1.0/8.0));
    
    //Creating the reactangles for all the UI compnents for the low band
    auto lowBandArea = area.removeFromLeft(areaWidth*widthRatio);
    auto lowBandAreaWidth = lowBandArea.getWidth();
    auto lowBandAreaHeight = lowBandArea.getHeight();
    DBG("Low-Band Area Width: " << lowBandAreaWidth);
    DBG("Low-Band Area Height: " << lowBandAreaHeight);
    auto bandWidthRatio = 0.5;
    auto bandHeightRatio = 0.5;
    auto lowBandUpperArea = lowBandArea.removeFromTop(lowBandAreaHeight*0.35);
    auto lowBandUpperAreaHeight = lowBandUpperArea.getHeight();
    auto lowBandUpperAreaWidth = lowBandUpperArea.getWidth();
    auto lowBandLabelArea = lowBandUpperArea.removeFromTop(lowBandUpperAreaHeight*0.5);
    auto lowBandToggleSpace = lowBandUpperArea.removeFromLeft(lowBandUpperAreaWidth*0.35);
    auto lowBandToggleArea = lowBandUpperArea;
    auto lowBandGainArea = lowBandArea.removeFromLeft(lowBandAreaWidth*bandWidthRatio);
    auto lowBandGainAreaHeight = lowBandGainArea.getHeight();
    auto lowBandGainLabelArea = lowBandGainArea.removeFromTop(lowBandGainAreaHeight*0.25);
    auto lowBandFreqArea = lowBandArea;
    auto lowBandFreqAreaHeight = lowBandFreqArea.getHeight();
    auto lowBandFreqLabelArea = lowBandFreqArea.removeFromTop(lowBandFreqAreaHeight * 0.25);
    
    //Creating the reactangles for all the UI compnents for the mid band
    auto midBandArea = area.removeFromLeft(areaWidth*widthRatio);
    auto midBandAreaWidth = midBandArea.getWidth();
    auto midBandAreaHeight = midBandArea.getHeight();
    auto midBandUpperArea = midBandArea.removeFromTop(midBandAreaHeight*0.35);
    auto midBandUpperAreaHeight = midBandUpperArea.getHeight();
    auto midBandLabelArea = midBandUpperArea.removeFromTop(midBandUpperAreaHeight*0.5);
    auto midBandToggleArea = midBandUpperArea;
    auto midBandGainArea = midBandArea.removeFromLeft(midBandAreaWidth*bandWidthRatio);
    auto midBandGainAreaHeight = midBandGainArea.getHeight();
    auto midBandGainLabelArea = midBandGainArea.removeFromTop(midBandGainAreaHeight*0.25);
    auto midBandFreqArea = midBandArea;
    auto midBandFreqAreaHeight = midBandFreqArea.getHeight();
    auto midBandFreqLabelArea = midBandFreqArea.removeFromTop(midBandFreqAreaHeight * 0.25);
    
    //Creating the reactangles for all the UI compnents for the high band
    auto highBandArea = area;
    auto highBandAreaWidth = highBandArea.getWidth();
    auto highBandAreaHeight = highBandArea.getHeight();
    auto highBandUpperArea = highBandArea.removeFromTop(highBandAreaHeight*0.35);
    auto highBandUpperAreaHeight = highBandUpperArea.getHeight();
    auto highBandUpperAreaWidth = highBandUpperArea.getWidth();
    auto highBandLabelArea = highBandUpperArea.removeFromTop(highBandUpperAreaHeight*0.5);
    auto highBandToggleSpace = highBandUpperArea.removeFromLeft(lowBandUpperAreaWidth*0.35);
    auto highBandToggleArea = highBandUpperArea;
    auto highBandGainArea = highBandArea.removeFromLeft(highBandAreaWidth*bandWidthRatio);
    auto highBandGainAreaHeight = highBandGainArea.getHeight();
    auto highBandGainLabelArea = highBandGainArea.removeFromTop(highBandGainAreaHeight*0.25);
    auto highBandFreqArea = highBandArea;
    auto highBandFreqAreaHeight = highBandFreqArea.getHeight();
    auto highBandFreqLabelArea = highBandFreqArea.removeFromTop(highBandFreqAreaHeight * 0.25);
    
    
    //Setting the bounds for all the UI Components
    pluginLabel.setBounds(pluginLabelArea);
    
    lowBandLabel.setBounds(lowBandLabelArea);
    lowShelfButton.setBounds(lowBandToggleArea);
    lowGainLabel.setBounds(lowBandGainLabelArea);
    lowGainSlider.setBounds(lowBandGainArea);
    lowFreqLabel.setBounds(lowBandFreqLabelArea);
    lowFreqSlider.setBounds(lowBandFreqArea);
    
    midBandLabel.setBounds(midBandLabelArea);
    midGainLabel.setBounds(midBandGainLabelArea);
    midGainSlider.setBounds(midBandGainArea);
    midFreqLabel.setBounds(midBandFreqLabelArea);
    midFreqSlider.setBounds(midBandFreqArea);

    highBandLabel.setBounds(highBandLabelArea);
    highShelfButton.setBounds(highBandToggleArea);
    highGainLabel.setBounds(highBandGainLabelArea);
    highGainSlider.setBounds(highBandGainArea);
    highFreqLabel.setBounds(highBandFreqLabelArea);
    highFreqSlider.setBounds(highBandFreqArea);
   
    backgroundImage.rescaled(getWidth(), getHeight(),juce::Graphics::highResamplingQuality);
    
    
    
}
