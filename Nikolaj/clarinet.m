clear;clc;

fs = 44100;
f = 220;
N = fs/f;
N = floor(N);


%envelope time in seconds
at = 0.1;
dt = 0.9;
st = 0.5;
rt = 0.01; % must equal to l + 1/fs

% levels of attack, decay and sustain
attlvl = 1;
decaylvl = 0;
suslvl = 0.5;
%generate env
attack = linspace(0,attlvl, fs*at);
decay = linspace(attlvl,decaylvl, fs*dt);
sustain = linspace(decaylvl,suslvl, fs*st); 
release = linspace(suslvl,0, fs*rt);
env = [attack decay];
x = 2*rand(1,length(env));
x = x - mean(x);

x = x.*env;
plot(x)

% clarinet parameters 
pm = 0.1; 

y1 = zeros(1, N/2+1); %  = [zeros(1,fs + delay)];
y2 = zeros(1,N/2);
t = 44100;
out = 0;
dout1 = 0; 
dout2 = 0;
signal = 0;
lengthYOffset = N/2-1;
a = 0.5;
a2 = 0.3;


pos = 1;
HPz1 = 0;
HPz2 = 0;

for i = 1:t
    pbplus = y2(N/2) - pm  ;
    
    if pbplus < -0.1
        alpha = 1;
    else 
        alpha = -0.5 * pbplus + 0.2;
    end
        
    if i < length(env) + 1
        noise = pm + 0.1*x(i);
    else
        noise = 0;
    end
    
    pbminus = alpha * pbplus + (1-alpha)* pm + 0.02*noise;
    
    
    y1 = [pbminus, y1(1:lengthYOffset)];
    y2 = [-(a*y1(N/2-1) + (1-a)*y1(N/2)), y2(1:lengthYOffset)];
    
    out = -(0.1*dout1 - 0.9*dout2);
    dout2 = dout1; 
    dout1 = y1(N/2);
    signal = [signal out];

    
%     
%     nextPos = mod((pos + 1), N + 2);
%     pbplus = y(pos) - pm/2;
%     pbplus = pbplus/2; 
%     
%     alpha = 0.1;
%     pbminus = alpha*pbplus - (1-alpha)*noise;
%     pbminus = pbminus+noise;
%     
%     if nextPos == 0
%         nextPos = 1;
%     end
%     
%     out = (a1*y(pos) + (1-a1)*y(nextPos));
%     y(pos) = pbminus - out;
%     
%     
%     
%     signal(i) = out + (a2*HPz1 - (1-a2)*HPz2);
%     
%     
%     HPz2 = HPz1;
%     HPz1 = signal(i);
%     
%     
%     pos = nextPos;
end

plot(signal)
soundsc(signal, fs)




