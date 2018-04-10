%% Simple Mass-Spring System:

% Discretized with the "backwards finite difference" equation:
% Equation x[n] = m*(2x[n-1] - x[n-2]) / k*T^2+m

clc; clear;

fs = 88200; %samplerate
T = 1/fs;   %sample-period
N = 100000;   %duration

m = 20; %mass
k = 50000000;  %spring coefficient
%f = 1/(2*pi) * sqrt(k/m)
x = zeros(1,N); %output buffer
xn1 = 1;    % x[n-1] = x[n]
xn2 = 0;
;    % x[n-2] = x[n-1]  

for n=1:N

    x(n) = m*(2*xn1 - xn2) / (k*T*T+m);
    xn2 = xn1;
    xn1 = x(n);
end
plot(x)
grid
xlabel('Time Steps (samples)'); ylabel('Mass Displacement (m)');
soundsc(x,fs);


%% Simple Mass-Spring System with Damping:

% Discretized with the "backwards finite difference" equation:
% Equation x[n] = (2*m + b*T / (T*T)*k + m + b*T)*x[n-1] + (m / (T*T)*k + m + b*T)*x[n-2]

clc; clear;

fs = 44200; %samplerate
T = 1/fs;   %sample-period
N = 100000;   %duration

m = 0.1; %mass
k = 500000000;  %spring coefficient
b = 0; % damping coefficient


x = zeros(1,N); %output buffer
xn1 = 1;    % x[n-1] = x[n]
xn2 = 0;

for n=1:N
    
    x(n) = ((2*m + b*T) / ((T*T)*k + m + b*T))*xn1 + (m / ((T*T)*k + m + b*T))*xn2;
    xn2 = xn1;
    xn1 = x(n);
end

plot(x)
grid
xlabel('Time Steps (samples)'); ylabel('Mass Displacement (m)');
soundsc(x,fs);
