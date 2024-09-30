/*
  ==============================================================================

    PlaylistComponent.h
    Created: 29 Jan 2023 2:29:12pm
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Track.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener,
                           public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deck1,
                      DeckGUI* _deck2,
                      DJAudioPlayer* _metaDataParser);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    /** Draw the background behind the rows in the playlist table */
    void paintRowBackground(juce::Graphics&,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;

    /** Draw the playlist table cells */
    void paintCell(juce::Graphics&,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;

    /** Create a custom component to go in a cell */
    Component* refreshComponentForCell(int rowNumber,
                                       int columnId,
                                       bool isRowSelected,
                                       Component* existingComponentToUpdate) override;

    /** Implement Button::Listener */
    void buttonClicked(juce::Button* button) override;
private:
    std::vector<Track> trackTitles;

    juce::TableListBox playlist;
    juce::TextButton addToPlaylistButton{ "ADD TO PLAYLIST" };
    juce::TextEditor searchBox;
    juce::TextButton addToDeck1Button{ "ADD TO DECK 1" };
    juce::TextButton addToDeck2Button{ "ADD TO DECK 2" };

    DeckGUI* deck1;
    DeckGUI* deck2;
    DJAudioPlayer* metaDataParser;

    /** Get the length of the audio file */
    juce::String getLength(juce::URL audioURL);
    /** Convert seconds to minutes */
    juce::String secondsToMinutes(double seconds);

    /** Check whether the file is among the tracks */
    bool isInTracks(juce::String fileNameWithoutExtension);
    /** Check where the file is among the tracks */
    int whereInTracks(juce::String searchText);
    /** Add a file to the playlist library */
    void addToPlaylist();
    /** Search a file within the playlist library */
    void searchPlaylist(juce::String searchText);
    /** Save the playlist library */
    void savePlaylist();
    /** Load the playlist library */
    void loadPlaylist();
    /** Load a track to one of the decks */
    void loadToDeck(DeckGUI* deckGUI);
    /** Delete a track from the saved playlist library */
    void deletedFromPlaylist(int id);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
