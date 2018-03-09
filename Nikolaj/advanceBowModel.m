% stefanias bow model
clear; clc; close all; 

freq = 440;
fs = 44100;

N = fs; 

stringLength = floor(fs/freq);
l = stringLength/2;
nutDelay = zeros(1,l);
brigdeDelay = zeros(1,l);

%Interaction
Pb = 0.15;
Fb = 0.3;
Vb = 0.7;

Z = 0.1;
StaticFrictionCoeff = 0.02;
DynamicFrictionCoeff = 0.01;

Von = 0; 
Vob = 0;
Vin = 0; 
Vib = 0;
Vh = 0;

dVon = 0;
dVob = 0;

output = zeros(N,1);

for i = 1:N
    Vin = nutDelay(l);
    Vib = brigdeDelay(l);
    Vh = Vin + Vib;
    
    v = 0;
    f = Fb *(0.3 * (0.1/(0.2 + abs(v - Vb))));
    
    Von = Vib + f/(2*Z); 
    Vob = Vin + f/(2*Z);
    
    inputToNutDelay = 0.5*(Von + dVon);
    inputToBrigdeDelay = 0.5*(Vob + dVob);
    
    nutDelay = [inputToNutDelay, nutDelay(1:l-1)];
    brigdeDelay = [inputToBrigdeDelay, brigdeDelay(1:l-1)];
    
    output(i) = Vh;
    
    dVon = Von; 
    dVoB = Vob;
end

plot(output)


