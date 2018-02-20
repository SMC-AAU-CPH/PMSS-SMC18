/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/
//#include "DelayLine.cpp"
#include "Violin.cpp"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);

        // specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
        // This function will be called when the audio device is started, or when
        // its settings (i.e. sample rate, block size, etc) are changed.

        // You can use this function to initialise any resources you might need,
        // but be careful - it will be called on the audio thread, not the GUI thread.
        fs = sampleRate;
        
        violin.init(fs);
 
    }

    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();
        
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float* const channelData = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
            
            if (channel == 0)
            {
                for (int i = 0; i < bufferToFill.buffer->getNumSamples(); i++)
                {
                    float vio = violin.play(v);
                    float out = vio*0.5;//0.277691*vio + 0.5*dout;
                    dout = vio;
                    
                    channelData[i] = out;
                    
                    if(pluckNow)
                    {
                    
                    } else {
                        v *= 0.80;
                    }
                    
                }
            }
            else
            {
                memcpy (channelData,
                        bufferToFill.buffer->getReadPointer (0),
                        bufferToFill.numSamples * sizeof (float));
            }
        }
    }

    void releaseResources() override
    {
        // This will be called when the audio device stops, or when it is being
        // restarted due to a setting change.

        // For more details, see the help for AudioProcessor::releaseResources()
    }


    //==============================================================================
    void paint (Graphics& g) override
    {
        // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        // You can add your drawing code here!
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }
    void pluck()
    {
       pluckNow = true;
    }


private:
    //==============================================================================
    void mouseDown (const MouseEvent& e) override
    {
        pluckNow = true;
        freq = e.getScreenX();
        
       
        if (freq < 50) freq = 50;
        v = e.getScreenY()/100000.f;
        violin.setFrequency(freq);
        //std::cout << newFreq << "\n";
       
    }
    void mouseDrag (const MouseEvent& e) override
    {
        int freq = e.getScreenX();
        v = e.getScreenY()/10000.f;
        vibratoGain = e.getScreenY()/100000.f;
        if (freq < 50) freq = 50;
        violin.setFrequency(freq);
        violin.setVibratoGain(vibratoGain);

    }
    void mouseUp (const MouseEvent& e) override
    {
        pluckNow = false;
    }
    
    // Your private member variables go here...
    bool pluckNow = false;
    double fs = 44100;
    float freq = 220;
    float v = 0;
    float dout = 0;
    float vibratoGain = 0.008;
    Violin violin;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent);

};
// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
