/*
  ==============================================================================

    SynthSound.cpp
    Created: 14 Feb 2018 2:48:35pm
    Author:  franc

  ==============================================================================
*/

#include "SynthSound.h"

bool SynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool SynthSound::appliesToChannel(int midiNoteNumber)
{
	return true;
}
