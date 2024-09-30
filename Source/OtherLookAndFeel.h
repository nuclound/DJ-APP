/*
  ==============================================================================

    OtherLookAndFeel.h
    Created: 20 Feb 2023 10:10:21am
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class OtherLookAndFeelV1 : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeelV1();
    
    /** Customise the appearance of the rotary slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image dialImg1;
};

class OtherLookAndFeelV2 : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeelV2();

    /** Customise the appearance of the rotary slider */
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image dialImg2;
};