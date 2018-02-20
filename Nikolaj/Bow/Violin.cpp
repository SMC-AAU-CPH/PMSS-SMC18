/*
  ==============================================================================

    Violin.cpp
    Created: 20 Feb 2018 9:07:00am
    Author:  Nikolaj Schwab Andersson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "DelayLine.cpp"

class Violin{
public:

    Violin(){
    
    }
    
    void init(float sampleRate){
        fs = sampleRate;
        
        deltaPhase = M_PI * 2 * (vibratoFreq/fs);
        
        nutDelay.initDelay(0.01,fs);
        nutDelay.setFrequency(freq*(1-betaRatio));

        brigdeDelay.initDelay(0.01,fs);
        brigdeDelay.setFrequency(freq*betaRatio);    
    }
    
    void setVibratoGain(float g){
        vibratoGain = g;
    }
    
    void setFrequency(float f){
        freq = f;
        
        nutDelay.setFrequency(freq*(1-betaRatio));
        brigdeDelay.setFrequency(freq*betaRatio);
        
    }
    
    float play(float velocity){
        if (velocity > maxVelocity) velocity = maxVelocity;
        
        auto bowVelocity = velocity;
        auto brigdeReflection = -brigdeDelay.getLPOutput();
        auto nutReflection = -nutDelay.getOutput();
        auto stringVelocity = brigdeReflection + nutReflection;
        
        auto vdelta = bowVelocity - stringVelocity;
        
        // bow table
        auto bow = (vdelta + offset) * slope;
        bow = fabs(bow) + 0.75;
        bow = pow(bow,-4);
        
        if (bow < 0.01) bow = 0.01;
        else if (bow > 0.98) bow = 0.98;

        
        auto newVelocity = vdelta * bow;
        
        float out = -nutReflection;
        
        brigdeDelay.tick(newVelocity + nutReflection);
        nutDelay.tick(newVelocity + brigdeReflection);
        
        auto sine = sin(phase);
        
        phase += deltaPhase;
        if (phase > M_PI * 2) phase -= M_PI * 2;
        
        nutDelay.setFrequency(freq * (1.0 - betaRatio ) + (freq * vibratoGain * sine) );
        
        return out;  
    }
    
private:
    DelayLine nutDelay, brigdeDelay;

    double fs = 44100;
    float freq = 220; 

    float maxVelocity = 0.25;
    float offset = 0.001;
    float slope = 5;
    float betaRatio = 0.127236;
    float v = 0;
    
    float phase = 0;
    float vibratoFreq = 6.5;
    float deltaPhase = 0;
    float vibratoGain = 0.008;
};
