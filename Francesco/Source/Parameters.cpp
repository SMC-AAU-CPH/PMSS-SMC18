/*
  ==============================================================================

    Parameters.cpp
    Created: 14 Feb 2018 2:48:23pm
    Author:  franc

  ==============================================================================
*/

#include "Parameters.h"

Parameters::Parameters(AudioProcessor &processor) : valueTree(processor, nullptr)
{
	valueTree.createAndAddParameter("pluckLength",
		"Pluck Length",
		"ms",
		NormalisableRange<float>(0.0, 100.0),
		20.0,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("pluckPoint",
		"Pluck Point",
		"",
		NormalisableRange<float>(0.0, 1.0),
		0.3,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("lowPassCoef",
		"Amplitude",
		"",
		NormalisableRange<float>(0.0, 1.0),
		0.3,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("instType",
		"Instrument Type",
		"",
		NormalisableRange<float>(0.0, 2.0),
		0.0,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("reedClosure",
		"Reed Closure deltaPressure",
		"",
		NormalisableRange<float>(-1.0, 1.0),
		-0.1,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("mouthPressure",
		"Mouth Pressure",
		"",
		NormalisableRange<float>(0.0, 0.5),
		0.09,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("m",
		"M (stiffness + embochure)",
		"",
		NormalisableRange<float>(0.0, 5.0),
		1.0,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("blowLength",
		"Blow Length",
		"ms",
		NormalisableRange<float>(0.0, 800.0),
		400.0,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("noiseAmount",
		"Noise Amount",
		"",
		NormalisableRange<float>(0.0, 0.5),
		0.1,
		nullptr,
		nullptr);

	valueTree.createAndAddParameter("embochureDelay",
		"Embochure Delay",
		"",
		NormalisableRange<float>(0.0, 50.0),
		10.0,
		nullptr,
		nullptr);
}

bool Parameters::update()
{
	auto prevPluckLength = pluckLength;
	auto prevPluckPoint = pluckPoint;
	auto prevLowPassCoef = lowPassCoef;
	auto prevInstType = instType;
	auto prevReedClosure = reedClosure;
	auto prevMouthPressure = mouthPressure;
	auto prevM = m;
	auto prevBlowLength = blowLength;
	auto prevEmbochureDelay = embochureDelay;
	auto prevNoiseAmount = noiseAmount;

	instType = *valueTree.getRawParameterValue("instType");
	pluckLength = *valueTree.getRawParameterValue("pluckLength");
	pluckPoint = *valueTree.getRawParameterValue("pluckPoint");
	lowPassCoef = *valueTree.getRawParameterValue("lowPassCoef");
	reedClosure = *valueTree.getRawParameterValue("reedClosure");
	mouthPressure = *valueTree.getRawParameterValue("mouthPressure");
	m = *valueTree.getRawParameterValue("m");
	blowLength = *valueTree.getRawParameterValue("blowLength");
	embochureDelay = *valueTree.getRawParameterValue("embochureDelay");
	noiseAmount = *valueTree.getRawParameterValue("noiseAmount");

	if (prevPluckLength != pluckLength || prevPluckPoint != pluckPoint
		|| prevLowPassCoef != lowPassCoef || prevInstType != instType
		|| prevReedClosure != reedClosure || prevMouthPressure != mouthPressure
		|| prevM != m || prevBlowLength != blowLength || prevEmbochureDelay != embochureDelay 
		|| prevNoiseAmount != noiseAmount)
		return true;

	else
		return false;
}