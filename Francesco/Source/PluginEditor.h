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

	ScopedPointer<SliderAttachment> aAttachment;
	ScopedPointer<SliderAttachment> bAttachment;
	ScopedPointer<SliderAttachment> cAttachment;
	ScopedPointer<SliderAttachment> dAttachment;
	ScopedPointer<SliderAttachment> eAttachment;
	ScopedPointer<ComboBoxAttachment> menuAttachment;

	// Create sliders and labels for parameters
	Slider aSlider;
	Slider bSlider;
	Slider cSlider;
	Slider dSlider;
	Label aLabel;
	Label bLabel;
	Label cLabel;
	Label dLabel;

	ComboBox menu;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PhysicalModelsDemoAudioProcessorEditor)
};
