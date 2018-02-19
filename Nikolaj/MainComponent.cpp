/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

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
        frameSize = samplesPerBlockExpected;
        fs = sampleRate;
        /*
        
        size_t delayLineLength = (size_t) roundToInt (sampleRate / f);
        N = delayLineLength;
        delayLine.resize (delayLineLength);
        std::fill (delayLine.begin(), delayLine.end(), 0.0f);
        delayLine2.resize (delayLineLength);
        std::fill (delayLine2.begin(), delayLine2.end(), 0.0f);
        
        excitationSample.resize (delayLineLength);
        
        
        // as the excitation sample we use random noise between -1 and 1
        // (as a simple approximation to a plucking excitation)
        
        std::generate (excitationSample.begin(),
                       excitationSample.end(),
                       [] { return (Random::getSystemRandom().nextFloat() * 2.0f) - 1.0f; } );
        
        std::transform (excitationSample.begin(),
                        excitationSample.end(),
                        delayLine.begin(),
                        [this] (double sample) { return amplitude * sample; } );
        */
        // For more details, see the help for AudioProcessor::prepareToPlay()
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
                    int nextPos = (pos + 1) % l;
                    float out = 0.5*delayBuffer[pos] + 0.5*delayBuffer[nextPos];
                    channelData[i] = out;
                    delayBuffer[nextPos] = out;
                    pos = nextPos; 
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
        for (int i = 0; i < l; i++ )
        {
            delayBuffer[i] = 2*r.nextFloat()-1;
        }
        std::cout << "Hey" << "\n";
           //
    }
    

private:
    //==============================================================================
    void mouseDown (const MouseEvent& e) override
    {
        pluck ();
    }
    // Your private member variables go here...

    int frameSize = 0;
    double fs = 44100; 
    float freq = 220; 
    const int l = fs/freq; 
    int pos = 0; 
    float delayBuffer[200] = {};
    //std::vector<float> excitationSample, delayLine, delayLine2;

    
    Random r; 
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent);

};
// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }
