#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbnailCache{100};

    // Initialise the first player and deck
    DJAudioPlayer player1{ formatManager };
    DeckGUI deck1{ 1, &player1, formatManager, thumbnailCache };

    // Initialise the second player and deck
    DJAudioPlayer player2{ formatManager };
    DeckGUI deck2{ 2, &player2, formatManager, thumbnailCache };

    // Initialise the playlist library
    DJAudioPlayer metaDataParser{ formatManager };
    PlaylistComponent playlistComponent{ &deck1, &deck2, &metaDataParser };

    juce::MixerAudioSource mixerSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
