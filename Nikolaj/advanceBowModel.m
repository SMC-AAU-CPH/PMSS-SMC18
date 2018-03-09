% stefanias bow model
clear; clc; close all; 

freq = 440;
fs = 44100;

N = fs; 

stringLength = floor(fs/freq);
l = stringLength/2;
Pb = 0.15;
Fb = 0.3;
Vb = 0.7;

nutLength = floor(stringLength*(1-Pb))
brigdeLength = floor(stringLength*Pb)
nutDelay = zeros(1,nutLength);
brigdeDelay = zeros(1,brigdeLength);


Z = 0.1;

Von = 0; 
Vob = 0;
Vin = 0; 
Vib = 0;
Vh = 0;

dVon = 0;
dVob = 0;

output = zeros(N,1);

for i = 1:N
    Vin = nutDelay(nutLength);
    Vib = brigdeDelay(brigdeLength);
    Vh = Vin + Vib;
    
    v = sqrt((Vh*0.2)/(0.2 - Vb - Vh) - (Vb*Vh)/(0.2 - Vb - Vh) + (0.4*Fb)/(2*Z*(0.2 + 1 - Vb - Vh)));
    if v - Vb > 0
        vVb = 0;
    else
        vVb = v - Vb;
    end
    
    f = Fb * (0.3 * (0.1/(0.2 + abs(vVb))));
    
    Von = Vib + f/(2*Z); 
    Vob = Vin + f/(2*Z);
    
    inputToNutDelay = 0.5*(Von + dVon);
    inputToBrigdeDelay = 0.5*(Vob + dVob);
    
    nutDelay = [inputToNutDelay, nutDelay(1:nutLength-1)];
    brigdeDelay = [inputToBrigdeDelay, brigdeDelay(1:brigdeLength-1)];
    
    output(i) = Vh;
    
    dVon = inputToNutDelay; 
    dVoB = inputToBrigdeDelay;
end

plot(output)
soundsc(output,fs)

