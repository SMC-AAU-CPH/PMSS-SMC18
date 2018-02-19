/*
  ==============================================================================

    FractionalDelay.h
    Created: 14 Feb 2018 2:48:02pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class FractionalDelay
{
public:
	FractionalDelay();

	void reset(double audioSampleRate);
	float readFromBuffer(float delaySamples);
	void writeToBuffer(float sampleIn);

private:
	float delayBuffer[44100];
	int writeIdx;
	double sampleRate;
};