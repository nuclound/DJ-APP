/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Jan 2023 4:53:41pm
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "OtherLookAndFeel.h"

//==============================================================================
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(int _id,
            DJAudioPlayer* player,
            juce::AudioFormatManager& formatManagerToUse,
            juce::AudioThumbnailCache& cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** Implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

    /** Implement Slider::Listener */
    void sliderValueChanged(juce::Slider* slider) override;

    /** Check whether a file is being dragged over the deck */
    bool isInterestedInFileDrag(const juce::StringArray& files) override;

    /** Check whether a file is dropped into the deck */
    void filesDropped(const juce::StringArray& files, int x, int y) override;

    /** Check for changes in the waveform */
    void timerCallback() override;

    /** Load a file from the playlist */
    void loadFile(juce::URL audioURL);

private:
    int id;
    WaveformDisplay waveformDisplay;

    juce::TextButton playStopButton;
    juce::TextButton loadButton{ "LOAD" };
    juce::TextButton loopButton;

    OtherLookAndFeelV1 otherLookAndFeelV1;
    OtherLookAndFeelV2 otherLookAndFeelV2;
    juce::Slider volSlider;
    juce::Label volSliderLabel;
    juce::Slider speedSlider;
    juce::Label speedSliderLabel;
    juce::Slider roomSizeSlider;
    juce::Label roomSizeSliderLabel;
    juce::Slider dampingSlider;
    juce::Label dampingSliderLabel;
    juce::Slider wetLevelSlider;
    juce::Label wetLevelSliderLabel;
    juce::Slider dryLevelSlider;
    juce::Label dryLevelSliderLabel;
    juce::Slider posSlider;

    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
