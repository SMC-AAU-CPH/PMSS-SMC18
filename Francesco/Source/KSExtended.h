/*
  ==============================================================================

    KSExtended.h
    Created: 18 Feb 2018 4:58:19pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FractionalDelay.h"

/** Karplus-Strong model with triangular-wave pluck
and pluck point implementation */

class KSExtended
{
public:
	void reset(double newSampleRate);
	void setF0(double newF0);
	void setPluckPoint(float newPluckPoint);
	void setPluckLength(float newPluckLength);
	void setLowPassCoef(float newLowPassCoef);
	void renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples);

private:
	double sampleRate;
	double f0;
	float pluckPoint;
	float pluckLength;
	int pluckLengthSamples;
	int pluckCounter;
	bool isPlucked;
	float lowPassBridge[2];
	float lowPassFretboard[2];
	float excitation[4000];
	float delayLengthBridge;
	float delayLengthFretboard;
	float lowPassCoef;

	FractionalDelay delayBridge;
	FractionalDelay delayFretboard;

	void calculateDelayLength();
	void calculatePluck();
};