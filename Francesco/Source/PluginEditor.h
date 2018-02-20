/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Parameters.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

//==============================================================================
/**
*/
class PhysicalModelsDemoAudioProcessorEditor : public AudioProcessorEditor
{
public:
	PhysicalModelsDemoAudioProcessorEditor(PhysicalModelsDemoAudioProcessor&, Parameters&);
	~PhysicalModelsDemoAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	PhysicalModelsDemoAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;

	ScopedPointer<SliderAttachment> pluckLengthAttachment;
	ScopedPointer<SliderAttachment> pluckPointAttachment;
	ScopedPointer<SliderAttachment> lowPassCoefAttachment;
	ScopedPointer<SliderAttachment> reedClosureAttachment;
	ScopedPointer<SliderAttachment> mouthPressureAttachment;
	ScopedPointer<SliderAttachment> mAttachment;
	ScopedPointer<SliderAttachment> blowLengthAttachment;
	ScopedPointer<SliderAttachment> embochureDelayAttachment;
	ScopedPointer<SliderAttachment> noiseAmountAttachment;
	ScopedPointer<ComboBoxAttachment> menuAttachment;

	// Create sliders and labels for parameters
	Slider pluckLengthSlider;
	Slider pluckPointSlider;
	Slider lowPassCoefSlider;
	Slider reedClosureSlider;
	Slider mouthPressureSlider;
	Slider mSlider;
	Slider blowLengthSlider;
	Slider embochureDelaySlider;
	Slider noiseAmountSlider;
	Label pluckLengthLabel;
	Label pluckPointLabel;
	Label lowPassCoefLabel;
	Label reedClosureLabel;
	Label mouthPressureLabel;
	Label mLabel;
	Label blowLengthLabel;
	Label embochureDelayLabel;
	Label noiseAmountLabel;

	ComboBox menu;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhysicalModelsDemoAudioProcessorEditor)
};
