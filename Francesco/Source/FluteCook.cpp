/*
  ==============================================================================

    FluteCook.cpp
    Created: 18 Feb 2018 9:42:04pm
    Author:  franc

  ==============================================================================
*/

#include "FluteCook.h"

void FluteCook::reset(double newSampleRate)
{
	sampleRate = newSampleRate;
	f0 = 440;
	excitationLength = 400.0e-3;
	reflectionCoef = 0.0;
	boreVelocityReflected = 0.0;
	breathCounter = 0;
	lowPassCoef = 0.3;
	noiseAmount = 0.1;
	isBlowing = false;

	delayEmbochure.reset(sampleRate);
	delayBore.reset(sampleRate);

	delayLengthEmbochure = 10.0e-3;
	delayLengthBore = 100;

	for (int i = 0; i < 2; i++)
		lowPassBore[i] = 0.0;

	calculateExcitation();
}

void FluteCook::setF0(double newF0)
{
	f0 = newF0;
	calculateDelayLength();

	if (!isBlowing)
	{
		isBlowing = true;
		breathCounter = 0;
	}
}

void FluteCook::setBlowLength(double newBlowLength)
{
	excitationLength = newBlowLength;
	calculateExcitation();
}

void FluteCook::setEmbochureDelay(double newEmbochureDelay)
{
	delayLengthEmbochure = newEmbochureDelay;
}

void FluteCook::setNoiseAmount(double newNoiseAmount)
{
	noiseAmount = newNoiseAmount;
}

void FluteCook::calculateDelayLength()
{
	delayLengthBore = sampleRate / f0 / 2;
}

void FluteCook::setLowPassCoef(float newLowPassCoef)
{
	lowPassCoef = newLowPassCoef;
}

float FluteCook::jetModel(float currentBreathVelocity)
{
	float deltaVelocityDelayed;
	float delayLengthEmbochureSamples = std::round(sampleRate * delayLengthEmbochure);
	float deltaVelocity = currentBreathVelocity + 0.1 * boreVelocityReflected;

	delayEmbochure.writeToBuffer(deltaVelocity);
	deltaVelocityDelayed = delayEmbochure.readFromBuffer(delayLengthEmbochureSamples);

	return deltaVelocityDelayed - deltaVelocityDelayed * deltaVelocityDelayed * deltaVelocityDelayed;
}

void FluteCook::calculateExcitation()
{
	Random randomNumber;
	excitationLengthSamples = std::round(sampleRate * excitationLength);
	float noise;
	float breathNoise;

	float attackLengthSamples = std::round(sampleRate * 0.075 * excitationLength);
	float decayLengthSamples = std::round(sampleRate * 0.125 * excitationLength);
	float sustainLengthSamples = std::round(sampleRate * 0.6 * excitationLength);
	float releaseLengthSamples = std::round(sampleRate * 0.2 * excitationLength);

	float attackIncrement = (1 - 0) / (attackLengthSamples - 1);
	float decayIncrement = (0.9 - 1) / (decayLengthSamples - 1);
	float sustainIncrement = 0;
	float releaseIncrement = (0 - 0.9) / (releaseLengthSamples - 1);

	float temp = 0;

	for (int i = 0; i < excitationLengthSamples; i++)
	{
		if (i < attackLengthSamples)
		{
			temp += attackIncrement;
			breathVelocity[i] = temp;
		}
		
		else if (i < attackLengthSamples + decayLengthSamples)
		{
			temp += decayIncrement;
			breathVelocity[i] = temp;
		}

		else if (i < attackLengthSamples + decayLengthSamples + sustainLengthSamples)
		{
			temp += sustainIncrement;
			breathVelocity[i] = temp;
		}

		else
		{
			temp += releaseIncrement;
			breathVelocity[i] = temp;
		}
	}

	for (int i = 0; i < excitationLengthSamples; i++)
	{
		noise = 2.0 * randomNumber.nextFloat() - 1.0;
		breathNoise = breathVelocity[i] * noiseAmount * noise;
		breathVelocity[i] += breathNoise;
	}
}

void FluteCook::renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	float input;
	float outputSample;
	float boreVelocityTransmitted;

	for (int sample = 0; sample < numSamples; sample++)
	{
		if (isBlowing)
		{
			input = breathVelocity[breathCounter++];

			if (breathCounter >= excitationLengthSamples)
				isBlowing = false;
		}

		else
			input = 0.0;

		boreVelocityTransmitted = jetModel(input) + 0.9 * boreVelocityReflected;

		lowPassBore[0] = (1 - lowPassCoef) * boreVelocityTransmitted
			+ lowPassCoef * lowPassBore[1];
		lowPassBore[1] = lowPassBore[0];

		delayBore.writeToBuffer(lowPassBore[0]);

		outputSample = lowPassBore[0];
		boreVelocityReflected = delayBore.readFromBuffer(delayLengthBore);

		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			outputBuffer.addSample(channel, startSample, outputSample);

		startSample++;
	}
}