/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 16 Jan 2023 9:05:47am
    Author:  nuclo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(int _id,
                                 juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse)
                                 : audioThumbnail{ 1000, formatManagerToUse, cacheToUse },
                                   fileLoaded(false),
                                   position(0),
                                   id(_id)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));// clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);// draw an outline around the component
    g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker());
    g.fillRect(juce::Rectangle<int>::Rectangle(0, 0, getWidth(), getHeight() * 0.15));
    g.fillRect(juce::Rectangle<int>::Rectangle(0, getHeight() * 0.85, getWidth(), getHeight() * 0.15));

    // Create deck text
    g.setColour(juce::Colours::orange);
    g.setFont(20.0f);
    g.drawText("Deck " + std::to_string(id), juce::Rectangle<int>::Rectangle(0, 0, getWidth(), getHeight() * 0.15)
               , juce::Justification::centred, true);

    // Create audio file title text
    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawText(fileName, juce::Rectangle<int>::Rectangle(0, getHeight() * 0.85, getWidth(), getHeight() * 0.15)
               , juce::Justification::centred, true);

    if (fileLoaded)
    {
        // Draw a waveform and a time position marker which will show the current time postion of the file playback
        g.setColour(juce::Colours::red);
        audioThumbnail.drawChannel(g, juce::Rectangle<int>::Rectangle(0, getHeight() * 0.15, getWidth(), getHeight() * 0.7)
                                   , 0, audioThumbnail.getTotalLength(), 0, 1.0f);
        g.setColour(juce::Colours::white);
        g.drawRect(position * getWidth(), getHeight() * 0.15, getWidth() / 30, getHeight() * 0.7);
        g.fillRect(position * getWidth(), getHeight() * 0.15, getWidth() / 30, getHeight() * 0.7);
    }
    else
    {
        g.setFont(20.0f);
        g.setColour(juce::Colours::orange);
        g.drawText("File not loaded...", getLocalBounds(),
                   juce::Justification::centred, true);  // draw some placeholder text
    }

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

/** Load the URL file */
void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumbnail.clear();
    fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));
    fileName = audioURL.getFileName();
}

/** Trigger a callback once a change is detected */
void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

/** set the relative postion of the playhead*/
void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}
