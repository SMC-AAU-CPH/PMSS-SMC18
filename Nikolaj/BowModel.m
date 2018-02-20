clear;clc;

fs = 44100;
f = 220;
N = fs/f;
N = floor(N);

%envelope time in seconds
at = 0.02;
dt = 0.005;
st = 0.8;
rt = 0.01; % must equal to l + 1/fs

% levels of attack, decay and sustain
attlvl = 1;
decaylvl = 0.9;
suslvl = 0.9;
%generate env
attack = linspace(0,attlvl, fs*at);
decay = linspace(attlvl,decaylvl, fs*dt);
sustain = linspace(decaylvl,suslvl, fs*st);
release = linspace(suslvl,0, fs*rt);
env = [attack decay sustain release];

yr = zeros(1, N/2);
yl = zeros(1, N/2);

out = 0;

signal = 0;

lengthYOffset = N/2-1;
l = N/2

a = 0.5;

maxVelocity = .25;
t = 44100;

offset = 0.001;
slope = 5.0;

% still needs vibrato, modulate neck delay length: (baseDelay_ * (1.0 - betaRatio_) ) +  (baseDelay_ * vibratoGain_ * vibrato_.tick())
% betaRatio =  0.127236
for i = 1:t  
    if i < length(env)
        ADSR = env(i);
    else
        ADSR = 0;
    end
    
    bowVelocity = maxVelocity*ADSR;
    
    bridgeReflection = -(a*yr(l) + (1-a)*yr(l-1));
    nutReflection = -yl(l);
    stringVelocity = bridgeReflection + nutReflection;
    vdelta = bowVelocity - stringVelocity;
     
    % bow table
    bow = (vdelta + offset) * slope;
    bow = abs(bow) + 0.75;
    bow = bow^-4;
    
    if bow < 0.01
        bow = 0.01;
    elseif bow > 0.98
        bow = 0.98;
    end
    
    newVelocity = vdelta * bow;
   
    % yr goes from bow to brigde
    yr = [nutReflection + newVelocity, yr(1:lengthYOffset)];
   
    % yl goes from bow to brigde
    yl = [bridgeReflection + newVelocity, yl(1:lengthYOffset)];
    
    signal(i) = yr(l);
end

plot(signal)
sound(signal, fs)




