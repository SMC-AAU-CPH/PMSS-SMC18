/*
  ==============================================================================

    SynthSound.h
    Created: 14 Feb 2018 2:48:35pm
    Author:  franc

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{

public:
	bool appliesToNote(int midiNoteNumber) override;
	bool appliesToChannel(int midiNoteNumber) override;
};