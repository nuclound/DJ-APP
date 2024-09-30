/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Jan 2023 3:02:29pm
    Author:  nuclo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
public:
    DJAudioPlayer(juce::AudioFormatManager& formatManager);
    ~DJAudioPlayer();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    /** Load the audio file */
    void loadURL(juce::URL audioURL);
    /** Set the volume of the audio */
    void setGain(double gain);
    /** Set the speed of the audio */
    void setSpeed(double ratio);
    /** Set the position of the audio in terms of seconds */
    void setPosition(double posInSecs);
    /** Set the relation position of the audio */
    void setPositionRelative(double pos);
    /** Set the room size of the audio */
    void setRoomSize(float size);
    /** Set the damping of the audio */
    void setDamping(float damp);
    /** Set the wet level of the audio */
    void setWetLevel(float wet);
    /** Set the dry level of the audio */
    void setDryLevel(float dry);
    /** Get the relative position of the playhead */
    double getPositionRelative();
    /** Get the length of transport source in terms of seconds */
    double getLengthInSeconds();

    //==============================================================================
    void play();
    void stop();

private:
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false ,2 };
    juce::ReverbAudioSource reverbSource{ &resampleSource, false };
    juce::Reverb::Parameters reverbParameter;
};
