/*
  ==============================================================================

    DelayLine.cpp
    Created: 19 Feb 2018 4:40:29pm
    Author:  Nikolaj Schwab Andersson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

class DelayLine{
    public:
    
    void initDelay(float _delayInSeconds, float _fs){
        delayInSeconds = _delayInSeconds;
        fs = _fs;

        setDelayTime(_delayInSeconds);
    }
    
    
    void setDelayTime(float _delayInSeconds){
        delayInSamples = ceil(fs*delayInSeconds);
        
        if (delayInSamples > 88200) delayInSamples = 88200;
        
        frac = fs*delayInSeconds - floor(fs*delayInSeconds);
    }
    
    void setFeedback(float _feedback){
        feedback = _feedback;
    }
    
    void setFrequency(float freq){
        delayInSamples = ceil(fs/freq);
    
    }
    
    void tick(float input){
        
        int writePos = (pos + 1) % delayInSamples;
        
        int readPos = pos - delayInSamples;
        
        if (readPos < 0) readPos += delayInSamples;
        
        int nextReadPos = (readPos + 1) % delayInSamples;
        
        float out = frac * delay[readPos] + (1-frac)*delay[nextReadPos];
        
        
        delay[writePos] = input + feedback*out;

        pos = writePos;        
    }
    
    float getOutput(){
        int readPos = pos - delayInSamples;
        
        if (readPos < 0) readPos += delayInSamples;
        
        int nextReadPos = (readPos + 1) % delayInSamples;
        
        return frac * delay[readPos] + (1-frac)*delay[nextReadPos];
    }
    
    float getLPOutput(){          
        float out = getOutput();
        float currentOut = a*out + (1-a)*previousOutput;
        previousOutput = out;
        
        return currentOut;
    }
    private:
    
    float delayInSeconds;
    int delayInSamples;
    float frac; 
    int pos;
    float a = 0.5;
    float previousOutput = 0;
    
    float feedback = 0.0;
    float fs = 44100; 
    float delay[88200] = {};
    
};