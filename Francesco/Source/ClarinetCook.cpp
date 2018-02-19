/*
  ==============================================================================

    ClarinetCook.cpp
    Created: 18 Feb 2018 4:58:26pm
    Author:  franc

  ==============================================================================
*/

#include "ClarinetCook.h"

void ClarinetCook::reset(double newSampleRate)
{
	sampleRate = newSampleRate;
	f0 = 440;
	mouthPressure = 0.09;
	reflectionCoef = 0.0;
	reedClosureDeltaPressure = -0.1;
	borePressureReflected = 0.0;
	m = 1;
	lowPassCoef = 0.3;
	isBlowing = false;

	delayBore.reset(sampleRate);

	delayLengthBore = 100;

	for (int i = 0; i < 2; i++)
		lowPassBore[i] = 0.0;
}

void ClarinetCook::setF0(double newF0)
{
	f0 = newF0;
	calculateDelayLength();

	if (!isBlowing)
		isBlowing = true;
}

void ClarinetCook::setMouthPressure(float newMouthPressure)
{
	mouthPressure = newMouthPressure;
}

void ClarinetCook::setReedClosure(float newReedClosure)
{
	reedClosureDeltaPressure = newReedClosure;
}

void ClarinetCook::setM(float newM)
{
	m = newM;
}

void ClarinetCook::stopBlowing()
{
	isBlowing = false;
}

void ClarinetCook::calculateDelayLength()
{
	delayLengthBore = sampleRate / f0 / 2;
}

void ClarinetCook::setLowPassCoef(float newLowPassCoef)
{
	lowPassCoef = newLowPassCoef;
}

float ClarinetCook::reedModel(float currentMouthPressure)
{
	float deltaPressure = borePressureReflected - currentMouthPressure;

	if (deltaPressure < reedClosureDeltaPressure)
		return 1;

	else
		return 1 - m * (deltaPressure - reedClosureDeltaPressure);
}

void ClarinetCook::renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	float outputSample;
	float currentMouthPressure;
	float borePressureTransmitted;

	for (int sample = 0; sample < numSamples; sample++)
	{
		if (isBlowing)
			currentMouthPressure = mouthPressure;

		else
			currentMouthPressure = 0.0;

		reflectionCoef = reedModel(currentMouthPressure);

		borePressureTransmitted = reflectionCoef * borePressureReflected + (1 - reflectionCoef) * currentMouthPressure;

		delayBore.writeToBuffer(borePressureTransmitted);

		lowPassBore[0] = (1 - lowPassCoef) * delayBore.readFromBuffer(delayLengthBore)
			+ lowPassCoef * lowPassBore[1];
		lowPassBore[1] = lowPassBore[0];

		outputSample = borePressureTransmitted;
		borePressureReflected = - lowPassBore[0];

		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			outputBuffer.addSample(channel, startSample, outputSample);

		startSample++;
	}
}