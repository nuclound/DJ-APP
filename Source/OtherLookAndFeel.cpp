/*
  ==============================================================================

    OtherLookAndFeel.cpp
    Created: 20 Feb 2023 10:10:21am
    Author:  nuclo

  ==============================================================================
*/

#include "OtherLookAndFeel.h"

//==============================================================================
OtherLookAndFeelV1::OtherLookAndFeelV1() {
    // Load the png file from binary resources
    dialImg1 = juce::ImageFileFormat::loadFrom(BinaryData::AdvancedDial_png, BinaryData::AdvancedDial_pngSize);
}

/** Customise the appearance of the rotary slider */
void OtherLookAndFeelV1::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    const double rotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());

    const int frames = dialImg1.getHeight() / dialImg1.getWidth();
    const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
    const float radius = juce::jmin(width / 2.0f, height / 2.0f);
    const float centerX = x + width * 0.5f;
    const float centerY = y + height * 0.5f;
    const float rx = centerX - radius - 1.0f;
    const float ry = centerY - radius;

    g.drawImage(dialImg1, (int)rx, (int)ry, 2 * (int)radius, 2 * (int)radius, 0, frameId * dialImg1.getWidth(),
        dialImg1.getWidth(), dialImg1.getWidth());
}

OtherLookAndFeelV2::OtherLookAndFeelV2() {
    // Load the png file from binary resources
    dialImg2 = juce::ImageFileFormat::loadFrom(BinaryData::AdvancedDial2_png, BinaryData::AdvancedDial2_pngSize);
}

/** Customise the appearance of the rotary slider */
void OtherLookAndFeelV2::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    const double rotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());

    const int frames = dialImg2.getHeight() / dialImg2.getWidth();
    const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
    const float radius = juce::jmin(width / 2.0f, height / 2.0f);
    const float centerX = x + width * 0.5f;
    const float centerY = y + height * 0.5f;
    const float rx = centerX - radius - 1.0f;
    const float ry = centerY - radius;

    g.drawImage(dialImg2, (int)rx, (int)ry, 2 * (int)radius, 2 * (int)radius, 0, frameId * dialImg2.getWidth(),
        dialImg2.getWidth(), dialImg2.getWidth());
}