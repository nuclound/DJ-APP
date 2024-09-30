/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 13 Jan 2023 3:02:29pm
    Author:  nuclo

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
                             : formatManager(_formatManager)
{
    // Initialise the reverb parameters
    reverbParameter.roomSize = 0;
    reverbParameter.damping = 0;
    reverbParameter.wetLevel = 0;
    reverbParameter.dryLevel = 1.0;
    reverbSource.setParameters(reverbParameter);
}

DJAudioPlayer::~DJAudioPlayer()
{

}

//==============================================================================
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    reverbSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    reverbSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
    reverbSource.releaseResources();
}

//==============================================================================
/** Load the audio file */
void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

/** Set the volume of the audio */
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0.0 || gain > 1.0)
    {
        DBG("DJAudioPlayer::setGain gain should be between 0 and 1");
    }
    else
    {
        transportSource.setGain(gain);
    }
}

/** Set the speed of the audio */
void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0.25 || ratio > 5.0)
    {
        DBG("DJAudioPlayer::setSpeed ratio should be between 0.25 and 5");
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}

/** Set the position of the audio in terms of seconds */
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

/** Set the relation position of the audio */
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0.0 || pos > 1.0)
    {
        DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1");
    }
    else 
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

/** Set the room size of the audio */
void DJAudioPlayer::setRoomSize(float size)
{
    if (size < 0.0 || size > 1.0)
    {
        DBG("DJAudioPlayer::setRoomSize size should be between 0 and 1");
    }
    else
    {
        reverbParameter.roomSize = size;
        reverbSource.setParameters(reverbParameter);
    }
}

/** Set the damping of the audio */
void DJAudioPlayer::setDamping(float damp)
{
    if (damp < 0.0 || damp > 1.0)
    {
        DBG("DJAudioPlayer::setDamping damp should be between 0 and 1");
    }
    else
    {
        reverbParameter.damping = damp;
        reverbSource.setParameters(reverbParameter);
    }
}

/** Set the wet level of the audio */
void DJAudioPlayer::setWetLevel(float wet)
{
    if (wet < 0.0 || wet > 1.0)
    {
        DBG("DJAudioPlayer::setWetLevel wet should be between 0 and 1");
    }
    else
    {
        reverbParameter.wetLevel = wet;
        reverbSource.setParameters(reverbParameter);
    }
}

/** Set the dry level of the audio */
void DJAudioPlayer::setDryLevel(float dry)
{
    if (dry < 0.0 || dry > 1.0)
    {
        DBG("DJAudioPlayer::setDryLevel dry should be between 0 and 1");
    }
    else
    {
        reverbParameter.dryLevel = dry;
        reverbSource.setParameters(reverbParameter);
    }
}

/** Get the relative position of the playhead */
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

/** Get the length of transport source in terms of seconds */
double DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}

//==============================================================================
void DJAudioPlayer::play()
{
    transportSource.start();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
}
