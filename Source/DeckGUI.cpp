/*
  ==============================================================================

    DeckGUI.cpp
    Created: 13 Jan 2023 4:53:41pm
    Author:  nuclo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _id,
                 DJAudioPlayer* _player, 
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse) 
                 : player{ _player },
                   id(_id),
                   waveformDisplay{ id,formatManagerToUse , cacheToUse }
{
    addAndMakeVisible(waveformDisplay);

    // Create a button and then set its initial text to "PLAY" 
    addAndMakeVisible(playStopButton);
    playStopButton.addListener(this);
    playStopButton.setButtonText("PLAY");
    playStopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playStopButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::red);
    playStopButton.setTriggeredOnMouseDown(true);

    // Create a load button
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);

    // Create a button and then set its initial text to "LOOP" 
    addAndMakeVisible(loopButton);
    loopButton.addListener(this);
    loopButton.setButtonText("LOOP");
    loopButton.setTriggeredOnMouseDown(true);

    // Create a rotary volume slider and then customises the slider using the image
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volSlider.setLookAndFeel(&otherLookAndFeelV2);
    volSlider.setValue(0.5);
    volSlider.setRange(0.0, 1.0);

    // Create a volume label below the slider
    addAndMakeVisible(volSliderLabel);
    volSliderLabel.setText("VOLUME", juce::NotificationType::dontSendNotification);
    volSliderLabel.setJustificationType(juce::Justification::centred);
    volSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create a rotary speed slider and then customises the slider using the image
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    speedSlider.setLookAndFeel(&otherLookAndFeelV2);
    speedSlider.setValue(1.0);
    speedSlider.setRange(0.25, 5.0);

    // Create a speed label below the slider
    addAndMakeVisible(speedSliderLabel);
    speedSliderLabel.setText("SPEED", juce::NotificationType::dontSendNotification);
    speedSliderLabel.setJustificationType(juce::Justification::centred);
    speedSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create a rotary room size slider and then customises the slider using the image
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.addListener(this);
    roomSizeSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    roomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    roomSizeSlider.setLookAndFeel(&otherLookAndFeelV1);
    roomSizeSlider.setValue(0.0);
    roomSizeSlider.setRange(0.0, 1.0);

    // Create a room size label below the slider
    addAndMakeVisible(roomSizeSliderLabel);
    roomSizeSliderLabel.setText("SIZE", juce::NotificationType::dontSendNotification);
    roomSizeSliderLabel.setJustificationType(juce::Justification::centred);
    roomSizeSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create a rotary damping slider and then customises the slider using the image
    addAndMakeVisible(dampingSlider);
    dampingSlider.addListener(this);
    dampingSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dampingSlider.setLookAndFeel(&otherLookAndFeelV1);
    dampingSlider.setValue(0.0);
    dampingSlider.setRange(0.0, 1.0);

    // Create a damping label below the slider
    addAndMakeVisible(dampingSliderLabel);
    dampingSliderLabel.setText("DAMPING", juce::NotificationType::dontSendNotification);
    dampingSliderLabel.setJustificationType(juce::Justification::centred);
    dampingSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create a rotary wet level slider and then customises the slider using the image
    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.addListener(this);
    wetLevelSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetLevelSlider.setLookAndFeel(&otherLookAndFeelV1);
    wetLevelSlider.setValue(0.0);
    wetLevelSlider.setRange(0.0, 1.0);

    // Create a wet level label below the slider
    addAndMakeVisible(wetLevelSliderLabel);
    wetLevelSliderLabel.setText("WET", juce::NotificationType::dontSendNotification);
    wetLevelSliderLabel.setJustificationType(juce::Justification::centred);
    wetLevelSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create a rotary dry level slider and then customises the slider using the image
    addAndMakeVisible(dryLevelSlider);
    dryLevelSlider.addListener(this);
    dryLevelSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    dryLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    dryLevelSlider.setLookAndFeel(&otherLookAndFeelV1);
    dryLevelSlider.setValue(1.0);
    dryLevelSlider.setRange(0.0, 1.0);

    // Create a dry level label below the slider
    addAndMakeVisible(dryLevelSliderLabel);
    dryLevelSliderLabel.setText("DRY", juce::NotificationType::dontSendNotification);
    dryLevelSliderLabel.setJustificationType(juce::Justification::centred);
    dryLevelSliderLabel.setFont(juce::Font("Open Sans", 20.f, juce::Font::bold));

    // Create an invisible position slider and then overlays it above the waveform
    addAndMakeVisible(posSlider);
    posSlider.addListener(this);
    posSlider.setSliderStyle(juce::Slider::LinearBar);
    posSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    posSlider.setColour(juce::Slider::trackColourId, juce::Colours::transparentWhite);
    posSlider.setRange(0.0, 1.0);

    startTimer(200);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId).darker());   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    double rowW = getWidth() / 6;

    waveformDisplay.setBounds(0, 0, getWidth(), rowH * 3);
    posSlider.setBounds(0, getHeight() * 0.05625, getWidth(), getHeight() * 0.2625);

    playStopButton.setBounds(0, rowH * 3, getWidth() / 3, rowH);
    loadButton.setBounds(getWidth() / 3, rowH * 3, getWidth() / 3, rowH);
    loopButton.setBounds(getWidth() / 3 * 2, rowH * 3, getWidth() / 3, rowH);

    volSlider.setBounds(0, rowH * 4, rowW, rowH * 3.5);
    speedSlider.setBounds(rowW, rowH * 4, rowW, rowH * 3.5);
    roomSizeSlider.setBounds(rowW * 2, rowH * 4, rowW, rowH * 3.5);
    dampingSlider.setBounds(rowW * 3, rowH * 4, rowW, rowH * 3.5);
    wetLevelSlider.setBounds(rowW * 4, rowH * 4, rowW, rowH * 3.5);
    dryLevelSlider.setBounds(rowW * 5, rowH * 4, rowW, rowH * 3.5);

    volSliderLabel.setBounds(0, rowH * 7.5, rowW, rowH * 0.5);
    speedSliderLabel.setBounds(rowW, rowH * 7.5, rowW, rowH * 0.5);
    roomSizeSliderLabel.setBounds(rowW * 2, rowH * 7.5, rowW, rowH * 0.5);
    dampingSliderLabel.setBounds(rowW * 3, rowH * 7.5, rowW, rowH * 0.5);
    wetLevelSliderLabel.setBounds(rowW * 4, rowH * 7.5, rowW, rowH * 0.5);
    dryLevelSliderLabel.setBounds(rowW * 5, rowH * 7.5, rowW, rowH * 0.5);
}

/** Implement Button::Listener */
void DeckGUI::buttonClicked(juce::Button* button)
{
    // Toggle the state of the playStopButton and handle the funcionality accordingly
    if (button == &playStopButton)
    {
        if (playStopButton.getButtonText() == "PLAY")
        {
            DBG("Play button was clicked ");
            player->play();
            playStopButton.setButtonText("STOP");
            playStopButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        }
        else
        {
            DBG("Stop button was clicked");
            player->stop();
            playStopButton.setButtonText("PLAY");
            playStopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser("Select a file to play...");
        if (chooser.browseForFileToOpen())
        {
            DBG("Audio file was chosen");
            juce::URL audioURL = juce::URL{ chooser.getResult() };
            player->loadURL(audioURL);
            waveformDisplay.loadURL(audioURL);
            playStopButton.setButtonText("PLAY");
            playStopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }
    // Toggle the state of the loopButton and change the text accordingly
    if (button == &loopButton)
    {
        if (loopButton.getButtonText() == "LOOP")
        {
            loopButton.setButtonText("NO LOOP");
            loopButton.setToggleState(true, juce::NotificationType::dontSendNotification);
        }
        else
        {
            loopButton.setButtonText("LOOP");
            loopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }
}

/** Implement Slider::Listener */
void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        DBG("volSlider: " << slider->getValue());
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        DBG("speedSlider: " << slider->getValue());
        player->setSpeed(slider->getValue());
    }
    if (slider == &roomSizeSlider)
    {
        DBG("roomSizeSlider: " << slider->getValue());
        player->setRoomSize(slider->getValue());
    }
    if (slider == &dampingSlider)
    {
        DBG("dampingSlider: " << slider->getValue());
        player->setDamping(slider->getValue());
    }
    if (slider == &wetLevelSlider)
    {
        DBG("wetLevelSlider: " << slider->getValue());
        player->setWetLevel(slider->getValue());
        dryLevelSlider.setValue(1 - slider->getValue());
    }
    if (slider == &dryLevelSlider)
    {
        DBG("dryLevelSlider: " << slider->getValue());
        player->setDryLevel(slider->getValue());
        wetLevelSlider.setValue(1 - slider->getValue());
    }
    if (slider == &posSlider)
    {
        DBG("posSlider: " << slider->getValue());
        player->setPositionRelative(slider->getValue());
    }
}

/** Check whether a file is being dragged over the deck */
bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files) 
{
    DBG("File is dragged in");
    return true;
}

/** Check whether a file is dropped into the deck */
void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    DBG("File is dropped into deck");
    if (files.size() == 1) {
        player->loadURL(juce::URL{ juce::File{files[0]} });
        waveformDisplay.loadURL(juce::URL{ juce::File{files[0]} });
        playStopButton.setButtonText("PLAY");
        playStopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    }
}

/** Check for changes in the waveform */
void DeckGUI::timerCallback()
{
    // If loop button is toggled on, the music track will be reset back to the start once it ends and the track will be played again
    if (std::to_string(loopButton.getToggleState()) == "1") { 
        if (player->getPositionRelative() >= 1) {
            player->setPositionRelative(0);
            player->play();
        }
    }

    // If loop button is toggled off, the music track will still be reset back to the start once it ends but there will be no loop
    if (std::to_string(loopButton.getToggleState()) == "0") { 
        if (player->getPositionRelative() >= 1) { 
            player->setPositionRelative(0); 
            player->stop();
            playStopButton.setButtonText("PLAY");
            playStopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

/** Load a file from the playlist */
void DeckGUI::loadFile(juce::URL audioURL)
{
    DBG("File is loaded from the playlist");
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
    playStopButton.setButtonText("PLAY");
    playStopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
}