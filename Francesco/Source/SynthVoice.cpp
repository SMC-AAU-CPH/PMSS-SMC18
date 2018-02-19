/*
  ==============================================================================

    SynthVoice.cpp
    Created: 14 Feb 2018 2:48:28pm
    Author:  franc

  ==============================================================================
*/

#include "SynthVoice.h"

void SynthVoice::reset()
{
	f0 = 0.0;
	instType = 0;
	ksModel.reset(getSampleRate());
	clarinetCookModel.reset(getSampleRate());
	fluteCookModel.reset(getSampleRate());
}

bool SynthVoice::canPlaySound(SynthesiserSound* sound)
{
	return dynamic_cast <SynthSound*>(sound) != nullptr;
}

void SynthVoice::setInstType(int newInstType)
{
	instType = newInstType;
}

void SynthVoice::startNote(int midiNoteNumber, float /*velocity*/, SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
{
	f0 = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	
	ksModel.setF0(f0);
	clarinetCookModel.setF0(f0);
	fluteCookModel.setF0(f0);
}

void SynthVoice::stopNote(float /*velocity*/, bool /*allowTailOff*/)
{
	clarinetCookModel.stopBlowing();
	clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::renderNextBlock(AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
	switch (instType)
	{
	case 0:
		clarinetCookModel.reset(getSampleRate());
		fluteCookModel.reset(getSampleRate());
		ksModel.renderNextBlock(outputBuffer, startSample, numSamples);
		break;
	case 1:
		ksModel.reset(getSampleRate());
		fluteCookModel.reset(getSampleRate());
		clarinetCookModel.renderNextBlock(outputBuffer, startSample, numSamples);
		break;
	case 2:
		ksModel.reset(getSampleRate());
		clarinetCookModel.reset(getSampleRate());
		fluteCookModel.renderNextBlock(outputBuffer, startSample, numSamples);
	default:
		ksModel.renderNextBlock(outputBuffer, startSample, numSamples);
		break;
	}
}

void SynthVoice::setParameters(int newInstType, float pluckLength, float pluckPoint, float lowPassCoef, float mouthPressure,
	float reedClosure, float m, float blowLength, float embochureDelay, float noiseAmount)
{
	instType = newInstType;
	ksModel.setPluckLength(pluckLength);
	ksModel.setPluckPoint(pluckPoint);
	ksModel.setLowPassCoef(lowPassCoef);
	clarinetCookModel.setMouthPressure(mouthPressure);
	clarinetCookModel.setReedClosure(reedClosure);
	clarinetCookModel.setM(m);
	clarinetCookModel.setLowPassCoef(lowPassCoef);
	fluteCookModel.setBlowLength(blowLength);
	fluteCookModel.setEmbochureDelay(embochureDelay);
	fluteCookModel.setNoiseAmount(noiseAmount);
	fluteCookModel.setLowPassCoef(lowPassCoef);
}