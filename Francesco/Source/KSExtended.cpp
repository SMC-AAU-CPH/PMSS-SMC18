/*
  ==============================================================================

    KSExtended.cpp
    Created: 18 Feb 2018 4:58:19pm
    Author:  franc

  ==============================================================================
*/

#include "KSExtended.h"

void KSExtended::reset(double newSampleRate)
{
	sampleRate = newSampleRate;
	f0 = 440;
	pluckCounter = 0;
	pluckLength = 20.0e-3;
	pluckPoint = 0.3;
	lowPassCoef = 0.5;
	isPlucked = false;

	delayBridge.reset(sampleRate);
	delayFretboard.reset(sampleRate);

	delayLengthBridge = 70;
	delayLengthFretboard = 30;

	for (int i = 0; i < 4000; i++)
		excitation[i] = 0.0;

	for (int i = 0; i < 2; i++)
	{
		lowPassBridge[i] = 0.0;
		lowPassFretboard[i] = 0.0;
	}

	calculatePluck();
}

void KSExtended::calculatePluck()
{
	double phase = 0.0;
	double pluckFrequency = 1 / pluckLength;
	double deltaPhase = 2 * double_Pi * pluckFrequency / sampleRate;
	pluckLengthSamples = (int)std::round(pluckLength * sampleRate);

	for (int i = 0; i < pluckLengthSamples; i++)
	{
		excitation[i] = phase <= double_Pi ? -1 + 2 / double_Pi * phase : 3 - 2 / double_Pi * phase;
		phase += deltaPhase;
	}
}

void KSExtended::setF0(double newF0)
{
	f0 = newF0;
	calculateDelayLength();

	if (!isPlucked)
	{
		isPlucked = true;
		pluckCounter = 0;
	}
}

void KSExtended::calculateDelayLength()
{
	delayLengthBridge = pluckPoint * sampleRate / f0;
	delayLengthFretboard = (1 - pluckPoint) * sampleRate / f0;
}

void KSExtended::setPluckPoint(float newPluckPoint)
{
	pluckPoint = newPluckPoint;
	calculateDelayLength();
}

void KSExtended::setPluckLength(float newPluckLength)
{
	pluckLength = newPluckLength;
	calculatePluck();
}

void KSExtended::setLowPassCoef(float newLowPassCoef)
{
	lowPassCoef = newLowPassCoef;
}

void KSExtended::renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	float outputSample;
	float input;

	for (int sample = 0; sample < numSamples; sample++)
	{
		if (isPlucked)
		{
			input = excitation[pluckCounter++];

			if (pluckCounter >= pluckLengthSamples)
				isPlucked = false;
		}

		else
			input = 0.0;

		delayBridge.writeToBuffer(input + lowPassFretboard[0]);
		delayFretboard.writeToBuffer(input + lowPassBridge[0]);

		lowPassBridge[0] = (1 - lowPassCoef) * delayBridge.readFromBuffer(delayLengthBridge)
			+ lowPassCoef * lowPassBridge[1];
		lowPassFretboard[0] = (1 - lowPassCoef) * delayFretboard.readFromBuffer(delayLengthFretboard)
			+ lowPassCoef * lowPassFretboard[1];
		lowPassBridge[1] = lowPassBridge[0];
		lowPassFretboard[1] = lowPassFretboard[0];

		outputSample = delayFretboard.readFromBuffer(delayLengthFretboard);


		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			outputBuffer.addSample(channel, startSample, outputSample);

		startSample++;
	}
}