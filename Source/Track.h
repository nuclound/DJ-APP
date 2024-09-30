/*
  ==============================================================================

    Track.h
    Created: 19 Feb 2023 3:01:46pm
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Track
{
public:
    juce::File file;
    juce::URL URL;
    juce::String title;
    juce::String length;

    /** Create a constructor for Track by taking in file */
    Track(juce::File _file);
   
    /** Compare the files by their titles */
    bool operator==(const juce::String& other) const;
};
