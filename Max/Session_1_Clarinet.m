%% Clarinet (partly taken from Cook, Perry R-Real Sound Synthesis for Interactive Applications-CRC Press (2015).pdf, p.123)
clear;clc;

freq = 443;
fs = 44100;
l = round(fs/freq); 
%Exciter: I need an excitation signal that also gets fed with the output
%of my following delay line, in order to simulate 

Pm = 0.1; %incoming mouth-pressure
alpha = 0 % dummy value for calculating the actual mouth-pressure by

% Circular Buffer
delayline = zeros(1, l);
a = 0.3; %damping-coefficient 

for i=1:4*fs %index of 1 sec length
 deltaP = -(a*delayline(l) + (1-a)*delayline(l-1)) - Pm ; %the first term corresponds to my output signal and is actually "Pb"
    if deltaP < -0.1
        alpha = 1;
    else
        alpha = -0.5*deltaP + 0.2;
    end
    out(i) = a*delayline(l) + (1-a)*delayline(l-1); %lowpass filter in descrete form
    inputToDelay = alpha * deltaP +(1-alpha)*Pm;
    delayline = [inputToDelay, delayline(1:l-1)];
   
end
plot(out)
soundsc(out, fs);
