/*
  ==============================================================================

    FluteCook.h
    Created: 18 Feb 2018 9:42:04pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FractionalDelay.h"

/** Slide flute model by Perry Cook */

class FluteCook
{
public:
	void reset(double newSampleRate);
	void setF0(double newF0);
	void setLowPassCoef(float newLowPassCoef);
	void setBlowLength(double newBlowLength);
	void setEmbochureDelay(double newEmbochureDelay);
	void setNoiseAmount(double newNoiseAmount);
	void renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples);

private:
	double sampleRate;
	double f0;

	float noiseAmount;
	float reflectionCoef;
	float boreVelocityReflected;
	float breathVelocity[44100];
	float excitationLength;
	int excitationLengthSamples;
	int breathCounter;
	bool isBlowing;
	float lowPassBore[2];
	float delayLengthBore;
	float delayLengthEmbochure;
	float lowPassCoef;

	FractionalDelay delayEmbochure;
	FractionalDelay delayBore;

	void calculateDelayLength();
	float jetModel(float currentMouthPressure);
	void calculateExcitation();
};