/*
  ==============================================================================

    Parameters.h
    Created: 14 Feb 2018 2:48:23pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct Parameters
{
	Parameters(AudioProcessor &processor);
	bool update();

	int instType;
	float pluckLength;
	float pluckPoint;
	float lowPassCoef;
	float reedClosure;
	float mouthPressure;
	float m;
	float blowLength;
	float embochureDelay;
	float noiseAmount;

	AudioProcessorValueTreeState valueTree;
};