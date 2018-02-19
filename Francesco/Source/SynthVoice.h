/*
  ==============================================================================

    SynthVoice.h
    Created: 14 Feb 2018 2:48:28pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "FractionalDelay.h"
#include "KSExtended.h"
#include "ClarinetCook.h"
#include "FluteCook.h"

class SynthVoice : public SynthesiserVoice
{
public:
	void reset();
	bool canPlaySound(SynthesiserSound* sound) override;
	void setInstType(int newInstType);
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;
	void setParameters(int newInstType, float pluckLength, float pluckPoint, float lowPassCoef, float mouthPressure, 
		float reedClosure, float blowLength, float m, float embochureDelay, float noiseAmount);

	//=======================================================
private:
	int instType;
	double f0;

	FractionalDelay delayBridge;
	FractionalDelay delayFretboard;

	KSExtended ksModel;
	ClarinetCook clarinetCookModel;
	FluteCook fluteCookModel;
};