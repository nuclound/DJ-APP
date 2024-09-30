/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 29 Jan 2023 2:29:12pm
    Author:  nuclo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deck1,
                                     DeckGUI* _deck2,
                                     DJAudioPlayer* _metaDataParser
                                    ) : deck1(_deck1),
                                        deck2(_deck2),
                                        metaDataParser(_metaDataParser)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playlist);
    addAndMakeVisible(addToPlaylistButton);
    addAndMakeVisible(searchBox);
    addAndMakeVisible(addToDeck1Button);
    addAndMakeVisible(addToDeck2Button);

    addToPlaylistButton.addListener(this);
    searchBox.addListener(this);
    addToDeck1Button.addListener(this);
    addToDeck2Button.addListener(this);

    addToPlaylistButton.setColour(juce::TextButton::buttonColourId, juce::Colours::maroon);
    addToDeck1Button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);
    addToDeck2Button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkgrey);

    playlist.getHeader().addColumn("Track Title", 1, 200);
    playlist.getHeader().addColumn("Length", 2, 60);
    playlist.getHeader().addColumn("Delete", 3, 60);
    playlist.setModel(this);
    loadPlaylist();

    searchBox.setTextToShowWhenEmpty("Search For Track...", juce::Colours::white);
    searchBox.setAlpha(0.7);
    searchBox.setJustification(juce::Justification::centred);
    searchBox.onReturnKey = [this] { searchPlaylist(searchBox.getText()); };
}

PlaylistComponent::~PlaylistComponent()
{
    savePlaylist();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    double rowH = getHeight() / 15;
    double rowW = getWidth() / 2;
    addToPlaylistButton.setBounds(0, 0, rowW, rowH);
    searchBox.setBounds(rowW, 0, rowW, rowH);
    playlist.setBounds(0, rowH, getWidth(), rowH * 12.5);
    addToDeck1Button.setBounds(0, rowH * 13.5, rowW, rowH * 1.5);
    addToDeck2Button.setBounds(rowW, rowH * 13.5, rowW, rowH * 1.5);
}

int PlaylistComponent::getNumRows()
{
    return trackTitles.size(); 
}

/** Draw the background behind the rows in the playlist table */
void PlaylistComponent::paintRowBackground(juce::Graphics& g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
                           .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    // For highlighting selected rows
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::darkorange);
    }
    else if (rowNumber % 2)
    {
        g.fillAll(alternateColour);
    }
}

/** Draw the playlist table cells */
void PlaylistComponent::paintCell(juce::Graphics& g,
                                   int rowNumber,
                                   int columnId,
                                   int width,
                                   int height,
                                   bool rowIsSelected)
{
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
        {
            g.drawText(trackTitles[rowNumber].title,
                2,
                0,
                width - 4,
                height,
                juce::Justification::centredLeft,
                true
            );
        }
        if (columnId == 2)
        {
            g.drawText(trackTitles[rowNumber].length,
                2,
                0,
                width - 4,
                height,
                juce::Justification::centred,
                true
            );
        }
    }
}

/** Create a custom component to go in a cell */
juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                            int columnId,
                                                            bool isRowSelected,
                                                            Component* existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton * btn = new juce::TextButton{ "X" };
            btn->setColour(juce::TextButton::buttonColourId, juce::Colours::darkred);
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

/** Implement Button::Listener */
void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &addToPlaylistButton)
    {
        DBG("Add to Library button is clicked");
        addToPlaylist();
        playlist.updateContent();
    }
    else if (button == &addToDeck1Button)
    {
        DBG("Add to Deck 1 button is clicked");
        loadToDeck(deck1);
    }
    else if (button == &addToDeck2Button)
    {
        DBG("Add to Deck 2 button is clicked");
        loadToDeck(deck2);
    }
    else
    {
        int id = std::stoi(button->getComponentID().toStdString());
        DBG(trackTitles[id].title + " is removed from playlist");
        deletedFromPlaylist(id);
        playlist.updateContent();
    }
}

/** Get the length of the audio file */
juce::String PlaylistComponent::getLength(juce::URL audioURL)
{
    metaDataParser->loadURL(audioURL);
    double seconds{ metaDataParser->getLengthInSeconds() };
    juce::String minutes{ secondsToMinutes(seconds) };
    return minutes;
}

/** Convert seconds to minutes */
juce::String PlaylistComponent::secondsToMinutes(double seconds)
{
    // Find minutes & seconds and then covert them into strings
    int secondsRounded{ int(std::round(seconds)) };
    juce::String min{ std::to_string(secondsRounded / 60) };
    juce::String sec{ std::to_string(secondsRounded % 60) };

    if (sec.length() < 2)
    {
        // Add '0' to seconds until the seconds has the length of 2
        sec = sec.paddedLeft('0', 2);
    }
    return juce::String{ min + ":" + sec };
}

/** Check whether the file is among the tracks */
bool PlaylistComponent::isInTracks(juce::String fileNameWithoutExtension)
{
    return (std::find(trackTitles.begin(), trackTitles.end(), fileNameWithoutExtension) != trackTitles.end());
}

/** Check where the file is among the tracks */
int PlaylistComponent::whereInTracks(juce::String searchText)
{
    // Finds index where the track title contains searchText
    auto it = find_if(trackTitles.begin(), trackTitles.end(), [&searchText](const Track& obj) {return obj.title.contains(searchText); });
    int i = -1;

    if (it != trackTitles.end())
    {
        i = std::distance(trackTitles.begin(), it);
    }

    return i;
}

/** Add a file to the playlist library */
void PlaylistComponent::addToPlaylist()
{
    // Initialise file chooser
    juce::FileChooser chooser{ "Select files" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : chooser.getResults())
        {
            juce::String fileNameWithoutExtension{ file.getFileNameWithoutExtension() };
            if (!isInTracks(fileNameWithoutExtension))// If the file does not exist in the playlist
            {
                Track newTrack{ file };
                juce::URL audioURL{ file };
                newTrack.length = getLength(audioURL);
                trackTitles.push_back(newTrack);
                DBG("loaded file: " << newTrack.title);
            }
            else// If the file already exist in the playlist, a message will appear to inform the user about it
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon, 
                                                   "Warning:",
                                                   fileNameWithoutExtension + " is already loaded to the playlist", 
                                                   "OK", 
                                                   nullptr
                );
            }
        }
    }
}

/** Search a file within the playlist library */
void PlaylistComponent::searchPlaylist(juce::String searchText)
{
    DBG("Searching playlist for: " << searchText);
    if (searchText != "")
    {
        int rowNumber = whereInTracks(searchText);
        playlist.selectRow(rowNumber);
    }
    else
    {
        playlist.deselectAllRows();
    }
}

/** Save the playlist library */
void PlaylistComponent::savePlaylist()
{
    // Create .csv file to save playlist
    std::ofstream myLibrary("my-library.csv");

    // Save the tracks in the playlist to file
    for (Track& t : trackTitles)
    {
        myLibrary << t.file.getFullPathName() << "," << t.length << "\n";
    }
}

/** Load the playlist library */
void PlaylistComponent::loadPlaylist()
{
    std::ifstream myLibrary("my-library.csv");
    std::string filePath;
    std::string length;

    // Read the csv data line by line
    if (myLibrary.is_open())
    {
        while (getline(myLibrary, filePath, ',')) 
            {
               juce::File file{ filePath };
               Track newTrack{ file };

               getline(myLibrary, length);
               newTrack.length = length;
               trackTitles.push_back(newTrack);
             }
    }
    myLibrary.close();
}

/** Load a track to one of the decks */
void PlaylistComponent::loadToDeck(DeckGUI* deck)
{
    int selectedRow{ playlist.getSelectedRow() };
    if (selectedRow != -1)// If a track is selected
    {
        DBG("Adding " << trackTitles[selectedRow].title << " to deck");
        deck->loadFile(trackTitles[selectedRow].URL);
    }
    else // If a track is not selected, a message will appear to inform the user about it
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::InfoIcon,
                                           "Warning:",
                                           "Please select a track to add to deck",
                                           "OK",
                                           nullptr
        );
    }
}

/** Delete a track from the saved playlist library */
void PlaylistComponent::deletedFromPlaylist(int id)
{
    trackTitles.erase(trackTitles.begin() + id);
}