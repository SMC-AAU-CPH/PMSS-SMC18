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

	aAttachment = new SliderAttachment(valueTreeState, "pluckLength", aSlider);
	bAttachment = new SliderAttachment(valueTreeState, "pluckPoint", bSlider);
	cAttachment = new SliderAttachment(valueTreeState, "lowPassCoef", cSlider);
	dAttachment = new SliderAttachment(valueTreeState, "m", dSlider);
	menuAttachment = new ComboBoxAttachment(valueTreeState, "instType", menu);

	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(800, 600);

	aSlider.setSliderStyle(Slider::Rotary);
	aSlider.setTextValueSuffix(" ms");
	aSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, aSlider.getTextBoxHeight());
	aLabel.setText("Pluck Length", dontSendNotification);
	aLabel.setJustificationType(Justification::centred);
	aLabel.attachToComponent(&aSlider, false);

	bSlider.setSliderStyle(Slider::Rotary);
	bSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, bSlider.getTextBoxHeight());
	bLabel.setText("Pluck Point (bridge -> fret)", dontSendNotification);
	bLabel.setJustificationType(Justification::centred);
	bLabel.attachToComponent(&bSlider, false);

	cSlider.setSliderStyle(Slider::Rotary);
	cSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, cSlider.getTextBoxHeight());
	cLabel.setText("Lowpass coefficient", dontSendNotification);
	cLabel.setJustificationType(Justification::centred);
	cLabel.attachToComponent(&cSlider, false);

	dSlider.setSliderStyle(Slider::Rotary);
	dSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 150, dSlider.getTextBoxHeight());
	dSlider.setAlpha(0.0);
	dLabel.setText("", dontSendNotification);
	dLabel.setJustificationType(Justification::centred);
	dLabel.attachToComponent(&dSlider, false);

	menu.setJustificationType(Justification::centred);
	menu.addItem("K-S Extended", 1);
	menu.addItem("Clarinet", 2);
	menu.addItem("Flute", 3);
	menu.setSelectedId(1, false);

	addAndMakeVisible(&aSlider);
	addAndMakeVisible(&aLabel);
	addAndMakeVisible(&bSlider);
	addAndMakeVisible(&bLabel);
	addAndMakeVisible(&cSlider);
	addAndMakeVisible(&cLabel);
	addAndMakeVisible(&dSlider);
	addAndMakeVisible(&dLabel);
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
		switch (processor.menuChoice)
		{
		case 0:
			aAttachment.release();
			aAttachment = new SliderAttachment(valueTreeState, "pluckLength", aSlider);
			aSlider.setTextValueSuffix(" ms");
			aLabel.setText("Pluck Length", dontSendNotification);
			aSlider.repaint();
			aLabel.repaint();
			bAttachment.release();
			bAttachment = new SliderAttachment(valueTreeState, "pluckPoint", bSlider);
			bSlider.setTextValueSuffix("");
			bLabel.setText("Pluck Point (bridge -> fret)", dontSendNotification);
			bSlider.repaint();
			bLabel.repaint();
			dAttachment.release();
			dSlider.setAlpha(0.0);
			dSlider.repaint();
			dLabel.setText("", dontSendNotification);
			dLabel.repaint();
			break;
		case 1:
			aAttachment.release();
			aAttachment = new SliderAttachment(valueTreeState, "mouthPressure", aSlider);
			aSlider.setTextValueSuffix("");
			aLabel.setText("Mouth Pressure", dontSendNotification);
			aSlider.repaint();
			aLabel.repaint();
			bAttachment.release();
			bAttachment = new SliderAttachment(valueTreeState, "reedClosure", bSlider);
			bSlider.setTextValueSuffix("");
			bLabel.setText("Reed Closure deltaPressure", dontSendNotification);
			bSlider.repaint();
			bLabel.repaint();
			dAttachment.release();
			dAttachment = new SliderAttachment(valueTreeState, "m", dSlider);
			dSlider.setAlpha(1.0);
			dSlider.setTextValueSuffix("");
			dLabel.setText("Stiffness + Embochure", dontSendNotification);
			dSlider.repaint();
			dLabel.repaint();
			break;
		case 2:
			aAttachment.release();
			aAttachment = new SliderAttachment(valueTreeState, "blowLength", aSlider);
			aSlider.setTextValueSuffix(" ms");
			aLabel.setText("Blow Length", dontSendNotification);
			aSlider.repaint();
			aLabel.repaint();
			bAttachment.release();
			bAttachment = new SliderAttachment(valueTreeState, "embochureDelay", bSlider);
			bSlider.setTextValueSuffix(" ms");
			bLabel.setText("Embochure Delay", dontSendNotification);
			bSlider.repaint();
			bLabel.repaint();
			dAttachment.release();
			dAttachment = new SliderAttachment(valueTreeState, "noiseAmount", dSlider);
			dSlider.setAlpha(1.0);
			dSlider.setTextValueSuffix("");
			dLabel.setText("Noise Amount", dontSendNotification);
			dSlider.repaint();
			dLabel.repaint();
			break;
		default:
			break;
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
	aSlider.setBounds(x, y, size, size);
	x += aSlider.getWidth() + marginX;
	bSlider.setBounds(x, y, size, size);
	x += bSlider.getWidth() + marginX;
	cSlider.setBounds(x, y, size, size);
	y += cSlider.getHeight() + marginY;
	x = marginX;
	dSlider.setBounds(x, y, size, size);

	int numX = 3;
	int numY = 3;
	setSize(size * numX + marginX * (numX + 1), size * numY + marginY * (numY + 1));
}
