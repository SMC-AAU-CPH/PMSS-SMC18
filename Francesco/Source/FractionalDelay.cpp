/*
  ==============================================================================

    FractionalDelay.cpp
    Created: 14 Feb 2018 2:48:02pm
    Author:  franc

  ==============================================================================
*/

#include "FractionalDelay.h"

FractionalDelay::FractionalDelay()
{
	writeIdx = 22051;

	for (int i = 0; i < 44100; i++)
		delayBuffer[i] = 0.0;

	sampleRate = 44.1e3;
}

void FractionalDelay::reset(double audioSampleRate)
{
	sampleRate = audioSampleRate;
	writeIdx = 22051;

	for (int i = 0; i < 44100; i++)
		delayBuffer[i] = 0.0;

}

float FractionalDelay::readFromBuffer(float delaySamples)
{
	int delaySamplesInt = (int)std::floor(delaySamples);
	float delaySamplesFrac = delaySamples - delaySamplesInt;
	int readIdx = writeIdx - delaySamplesInt;
	if (readIdx < 0)
		readIdx += 44100;
	float output;
	if (readIdx == 0)
		output = (1 - delaySamplesFrac) * delayBuffer[readIdx]
		+ delaySamplesFrac * delayBuffer[44099];
	else
		output = (1 - delaySamplesFrac) * delayBuffer[readIdx]
		+ delaySamplesFrac * delayBuffer[readIdx - 1];
	return output;
}

void FractionalDelay::writeToBuffer(float sampleIn)
{
	delayBuffer[writeIdx++] = sampleIn;
	if (writeIdx > 44099)
		writeIdx = 0;
}