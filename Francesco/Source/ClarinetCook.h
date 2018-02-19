/*
  ==============================================================================

    ClarinetCook.h
    Created: 18 Feb 2018 4:58:26pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FractionalDelay.h"

/** Clarinet model by Perry Cook: 1 waveguide */

class ClarinetCook
{
public:
	void reset(double newSampleRate);
	void setF0(double newF0);
	void setMouthPressure(float newMouthPressure);
	void setReedClosure(float newReedClosure);
	void setM(float newM);
	void setLowPassCoef(float newLowPassCoef);
	void stopBlowing();
	void renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples);

private:
	double sampleRate;
	double f0;

	float mouthPressure;
	float reedClosureDeltaPressure;
	float m;
	float reflectionCoef;
	float borePressureReflected;
	bool isBlowing;
	float lowPassBore[2];
	float delayLengthBore;
	float lowPassCoef;

	FractionalDelay delayBore;

	void calculateDelayLength();
	float reedModel(float currentMouthPressure);
};