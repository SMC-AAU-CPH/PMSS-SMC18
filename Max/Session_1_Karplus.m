%% Simple Karplus-Strong Algorithm (Plucked String)
clear;clc;

freq = 443;
fs = 44100;

%Exciter
l = round(fs/freq);
noise = rand(1, 50); 
noise = noise-mean(noise);
%applying a triangular envelope to the excitation signal
att=linspace(0,1,15); % defining a vector for an attak that goes from = to full amplitude within 15 samples
rel=linspace(1, 0, 35);
env = [att, rel]; % concatenate my two vectors

noise = noise.*env; % apply my envelope to the excitation signal (element-wise multiplication)
plot(noise);

% Circular Buffer
dl = zeros(1, l);
a = 0.5; %damping-coefficient of the string
%Lowpass-Filter
% y[n| = 0.5x[n]+0.5x[n-1]

for i=1:4*fs %index of 1 sec length
     if i < length(noise) %since my excitation signal is smaller than my output signal, this statement is needed in order to ensure 
        x = noise(i);
    else 
        x = 0;
    end
    out(i) = a*dl(l) + (1-a)*dl(l-1); %lowpass filter in descrete form
    dl = [( x + out(i)), dl(1:l-1)];
end
plot(out)
soundsc(out, fs);

%pos = 1;

% C++ way to do it:
% for    i=1:2*fs
%     if i < length(noise)
%         x = noise(i);
%     else 
%         x = 0;
%     end
%     
%     
%     nextpos = mod(pos+1, max(l)+1);
%     if nextpos == 0;
%         nextpos = 1;
%     end
%         
%     pos = nextpos;
%    
% end

%% Clarinet

%% Bowed String