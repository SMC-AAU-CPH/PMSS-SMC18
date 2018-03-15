%% Mass spring
m = 30; fs = 44100; T = 1/fs; N = 10000;
k = 50000000; x = zeros(1,N); xm1 = 0.5; xm2 = xm1; 
for i = 1:N
    x(i) = (2*m)/(m+k*T*T)*xm1 - xm2 * (m)/(m+k*T*T);
    xm2 = xm1;
    xm1 = x(i);
end
figure
plot(x) 
%% mass spring with damping
m = 0.1; fs = 100*44100; T = 1/fs; N = 1000000;

k = 500000; x = zeros(1,N); xm1 = 0.5; xm2 = xm1; 
f = 1/(2*pi) * sqrt(k/m)
R = 0.00000001;
c1 = m + R*T + k *(T*T); c2 = 2*m+R*T;
for i = 1:N
    x(i) = c2/c1*xm1 - xm2 * (m)/c1;
    xm2 = xm1;
    xm1 = x(i);
end
figure
plot(x)
%% Bottle
%   mode
m = 1; fs = 44100; T = 1/fs; N = 44100*2;
k = 5000000; 
m2 = 0.5; fs = 44100; N = 44100*2;
k2 = 5000000;

x = zeros(1,N); 

f = 1/(2*pi) * sqrt(k/m) % resonant frequency

input = 50000;

noise = 2*rand(1,input);
noise = noise - mean(noise); % remove DC off

offset = length(x)-length(noise);
if length(x) > length(noise)
    noise = [noise, zeros(1,offset)];
end

R = -100;
R2 = -100;
c1 = m + R*T + k *(T*T); c2 = 2*m+R*T;
c3 = m2 + R2*T + k2 *(T*T); c4 = 2*m2+R2*T;
xm1 = noise(N); 
xm2 = xm1; 

for i = 1:N
    x(i) = c2/c1*xm1 - xm2 * (m)/c1;
    xm2 = xm1;
    xm1 = x(i) + noise(i);
end

figure
plot((x/max(x))) 
s = (x/max(x));
sound(s,fs)

%% 2 modes
%   mode
m = 2; fs = 44100; T = 1/fs; N = 44100*4;
k = 50000000; 
m2 = 10; 
k2 = 50000000;

x = zeros(1,N); 
x2 = zeros(1,N); 

f = 1/(2*pi) * sqrt(k/m)% resonant frequency
f2 = 1/(2*pi) * sqrt(k2/m2)% resonant frequency

input = 100000;

noise = 2*rand(1,input);
noise = noise - mean(noise); % remove DC off

offset = length(x)-length(noise);
if length(x) > length(noise)
    noise =[noise, zeros(1,offset)];
end

R = 100;
R2 = -10000;

c1 = m + R*T + k *(T*T); c2 = 2*m+R*T;
c3 = m2 + R2*T + k2 *(T*T); c4 = 2*m2+R2*T;

xm1 = noise(N); 
xm2 = xm1; 

xm11 = noise(N-1); 
xm21 = xm11; 

for i = 1:N
    x(i) = c2/c1*xm1 - xm2 * (m)/c1;
    x2(i) = c4/c3*xm11 - xm21 * (m2)/c3;
    
    xm2 = xm1;
    xm1 = x(i) + noise(i);
    
    xm21 = xm11;
    xm11 = x2(i) + noise(i);
end

figure
s = (x/max(x));
s2 = (x2/max(x2));
mix = (s+s2)*0.5;
plot(mix)
sound(mix,fs)

