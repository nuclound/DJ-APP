/*
  ==============================================================================

    WaveformDisplay.h
    Created: 16 Jan 2023 9:05:47am
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(int _id,
                    juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    /** Load the URL file */
    void loadURL(juce::URL audioURL);

    /** Trigger a callback once a change is detected */
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    /** set the relative postion of the playhead*/
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumbnail;

    int id;
    bool fileLoaded;
    double position;
    juce::String fileName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
