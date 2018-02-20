/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PhysicalModelsDemoAudioProcessorEditor::PhysicalModelsDemoAudioProcessorEditor(PhysicalModelsDemoAudioProcessor& p, Parameters& params)
	: AudioProcessorEditor(&p), processor(p), valueTreeState(params.valueTree)
{

	pluckLengthAttachment = new SliderAttachment(valueTreeState, "pluckLength", pluckLengthSlider);
	pluckPointAttachment = new SliderAttachment(valueTreeState, "pluckPoint", pluckPointSlider);
	lowPassCoefAttachment = new SliderAttachment(valueTreeState, "lowPassCoef", lowPassCoefSlider);
	reedClosureAttachment = new SliderAttachment(valueTreeState, "reedClosure", reedClosureSlider);
	mouthPressureAttachment = new SliderAttachment(valueTreeState, "mouthPressure", mouthPressureSlider);
	mAttachment = new SliderAttachment(valueTreeState, "m", mSlider);
	blowLengthAttachment = new SliderAttachment(valueTreeState, "blowLength", blowLengthSlider);
	embochureDelayAttachment = new SliderAttachment(valueTreeState, "embochureDelay", embochureDelaySlider);
	noiseAmountAttachment = new SliderAttachment(valueTreeState, "noiseAmount", noiseAmountSlider);
	menuAttachment = new ComboBoxAttachment(valueTreeState, "instType", menu);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(800, 600);

	pluckLengthSlider.setSliderStyle(Slider::Rotary);
	pluckLengthSlider.setTextValueSuffix(" ms");
	pluckLengthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, pluckLengthSlider.getTextBoxHeight());
	pluckLengthLabel.setText("Pluck Duration", dontSendNotification);
	pluckLengthLabel.setJustificationType(Justification::centred);
	pluckLengthLabel.attachToComponent(&pluckLengthSlider, false);

	pluckPointSlider.setSliderStyle(Slider::Rotary);
	pluckPointSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, pluckPointSlider.getTextBoxHeight());
	pluckPointLabel.setText("Pluck Point (bridge -> fret)", dontSendNotification);
	pluckPointLabel.setJustificationType(Justification::centred);
	pluckPointLabel.attachToComponent(&pluckPointSlider, false);

	lowPassCoefSlider.setSliderStyle(Slider::Rotary);
	lowPassCoefSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, lowPassCoefSlider.getTextBoxHeight());
	lowPassCoefLabel.setText("Lowpass coefficient", dontSendNotification);
	lowPassCoefLabel.setJustificationType(Justification::centred);
	lowPassCoefLabel.attachToComponent(&lowPassCoefSlider, false);

	reedClosureSlider.setSliderStyle(Slider::Rotary);
	reedClosureSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, reedClosureSlider.getTextBoxHeight());
	reedClosureLabel.setText("Reed Closure DeltaPressure", dontSendNotification);
	reedClosureLabel.setJustificationType(Justification::centred);
	reedClosureLabel.attachToComponent(&reedClosureSlider, false);

	mouthPressureSlider.setSliderStyle(Slider::Rotary);
	mouthPressureSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, mouthPressureSlider.getTextBoxHeight());
	mouthPressureLabel.setText("Mouth Pressure", dontSendNotification);
	mouthPressureLabel.setJustificationType(Justification::centred);
	mouthPressureLabel.attachToComponent(&mouthPressureSlider, false);

	mSlider.setSliderStyle(Slider::Rotary);
	mSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, mSlider.getTextBoxHeight());
	mLabel.setText("Stiffness + Embochure", dontSendNotification);
	mLabel.setJustificationType(Justification::centred);
	mLabel.attachToComponent(&mSlider, false);

	blowLengthSlider.setSliderStyle(Slider::Rotary);
	blowLengthSlider.setTextValueSuffix(" ms");
	blowLengthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, blowLengthSlider.getTextBoxHeight());
	blowLengthLabel.setText("Blow Duration", dontSendNotification);
	blowLengthLabel.setJustificationType(Justification::centred);
	blowLengthLabel.attachToComponent(&blowLengthSlider, false);

	embochureDelaySlider.setSliderStyle(Slider::Rotary);
	embochureDelaySlider.setTextValueSuffix(" ms");
	embochureDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, embochureDelaySlider.getTextBoxHeight());
	embochureDelayLabel.setText("Embochure Delay", dontSendNotification);
	embochureDelayLabel.setJustificationType(Justification::centred);
	embochureDelayLabel.attachToComponent(&embochureDelaySlider, false);

	noiseAmountSlider.setSliderStyle(Slider::Rotary);
	noiseAmountSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, noiseAmountSlider.getTextBoxHeight());
	noiseAmountLabel.setText("Noise Amount", dontSendNotification);
	noiseAmountLabel.setJustificationType(Justification::centred);
	noiseAmountLabel.attachToComponent(&noiseAmountSlider, false);

	menu.setJustificationType(Justification::centred);
	menu.addItem("K-S Extended", 1);
	menu.addItem("Clarinet", 2);
	menu.addItem("Flute", 3);
	menu.setSelectedId(1, false);

	addAndMakeVisible(&pluckLengthSlider);
	addAndMakeVisible(&pluckLengthLabel);
	addAndMakeVisible(&pluckPointSlider);
	addAndMakeVisible(&pluckPointLabel);
	addAndMakeVisible(&lowPassCoefSlider);
	addAndMakeVisible(&lowPassCoefLabel);
	addAndMakeVisible(&menu);
}

PhysicalModelsDemoAudioProcessorEditor::~PhysicalModelsDemoAudioProcessorEditor()
{
}

//==============================================================================
void PhysicalModelsDemoAudioProcessorEditor::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
	g.setFont(15.0f);

	if (processor.menuChoice != processor.prevMenuChoice)
	{
		switch (processor.menuChoice)
		{
		case 0:
			addAndMakeVisible(&pluckLengthSlider);
			addAndMakeVisible(&pluckLengthLabel);
			addAndMakeVisible(&pluckPointSlider);
			addAndMakeVisible(&pluckPointLabel);
			removeChildComponent(&reedClosureSlider);
			removeChildComponent(&reedClosureLabel);
			removeChildComponent(&blowLengthSlider);
			removeChildComponent(&blowLengthLabel);
			removeChildComponent(&mouthPressureSlider);
			removeChildComponent(&mouthPressureLabel);
			removeChildComponent(&mSlider);
			removeChildComponent(&mLabel);
			removeChildComponent(&blowLengthSlider);
			removeChildComponent(&blowLengthLabel);
			removeChildComponent(&embochureDelaySlider);
			removeChildComponent(&embochureDelayLabel);
			removeChildComponent(&noiseAmountSlider);
			removeChildComponent(&noiseAmountLabel);
			break;
		case 1:
			removeChildComponent(&pluckLengthSlider);
			removeChildComponent(&pluckLengthLabel);
			removeChildComponent(&pluckPointSlider);
			removeChildComponent(&pluckPointLabel);
			addAndMakeVisible(&reedClosureSlider);
			addAndMakeVisible(&reedClosureLabel);
			addAndMakeVisible(&blowLengthSlider);
			addAndMakeVisible(&blowLengthLabel);
			addAndMakeVisible(&mouthPressureSlider);
			addAndMakeVisible(&mouthPressureLabel);
			addAndMakeVisible(&mSlider);
			addAndMakeVisible(&mLabel);
			removeChildComponent(&blowLengthSlider);
			removeChildComponent(&blowLengthLabel);
			removeChildComponent(&embochureDelaySlider);
			removeChildComponent(&embochureDelayLabel);
			removeChildComponent(&noiseAmountSlider);
			removeChildComponent(&noiseAmountLabel);
			break;
		case 2:
			removeChildComponent(&pluckLengthSlider);
			removeChildComponent(&pluckLengthLabel);
			removeChildComponent(&pluckPointSlider);
			removeChildComponent(&pluckPointLabel);
			removeChildComponent(&reedClosureSlider);
			removeChildComponent(&reedClosureLabel);
			removeChildComponent(&blowLengthSlider);
			removeChildComponent(&blowLengthLabel);
			removeChildComponent(&mouthPressureSlider);
			removeChildComponent(&mouthPressureLabel);
			removeChildComponent(&mSlider);
			removeChildComponent(&mLabel);
			addAndMakeVisible(&blowLengthSlider);
			addAndMakeVisible(&blowLengthLabel);
			addAndMakeVisible(&embochureDelaySlider);
			addAndMakeVisible(&embochureDelayLabel);
			addAndMakeVisible(&noiseAmountSlider);
			addAndMakeVisible(&noiseAmountLabel);
			break;
		default:
			break;
		}

		pluckLengthSlider.repaint();
		pluckPointSlider.repaint();
		reedClosureSlider.repaint();
		mouthPressureSlider.repaint();
		mSlider.repaint();
		blowLengthSlider.repaint();
		embochureDelaySlider.repaint();
		noiseAmountSlider.repaint();
		pluckLengthLabel.repaint();
		pluckPointLabel.repaint();
		reedClosureLabel.repaint();
		mouthPressureLabel.repaint();
		mLabel.repaint();
		blowLengthLabel.repaint();
		embochureDelayLabel.repaint();
		noiseAmountLabel.repaint();
	}
		

}

void PhysicalModelsDemoAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
		
	int marginX = 20;
	int marginY = 30;
	int x = marginX;
	int y = marginY;
	int size = 150;

	menu.setBounds(2 * x, y, 3 * size, size / 2);
	y += menu.getHeight() + marginY;
	pluckLengthSlider.setBounds(x, y, size, size);
	reedClosureSlider.setBounds(x, y, size, size);
	blowLengthSlider.setBounds(x, y, size, size);
	x += pluckLengthSlider.getWidth() + marginX;
	pluckPointSlider.setBounds(x, y, size, size);
	mouthPressureSlider.setBounds(x, y, size, size);
	embochureDelaySlider.setBounds(x, y, size, size);
	x += pluckPointSlider.getWidth() + marginX;
	lowPassCoefSlider.setBounds(x, y, size, size);
	y += lowPassCoefSlider.getHeight() + marginY;
	x = marginX;
	mSlider.setBounds(x, y, size, size);
	noiseAmountSlider.setBounds(x, y, size, size);

	int numX = 3;
	int numY = 3;
	setSize(size * numX + marginX * (numX + 1), size * numY + marginY * (numY + 1));
}
