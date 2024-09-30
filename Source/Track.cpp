/*
  ==============================================================================

    Track.cpp
    Created: 19 Feb 2023 3:01:46pm
    Author:  nuclo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Track.h"
#include <filesystem>

//==============================================================================
/** Create a constructor for Track by taking in file */
Track::Track(juce::File _file) : file(_file),
                                 title(_file.getFileNameWithoutExtension()),
                                 URL(juce::URL{ _file })
{
    DBG("A new track is added: " << title);
}

/** Compare the files by their titles */
bool Track::operator==(const juce::String& other) const
{
    return title == other;
}