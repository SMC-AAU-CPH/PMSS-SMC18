% This implements a simple mass-spring-damper model by using state-space
% modelling, discretized with the trapezoid rule.
%
% References:
%   Bilbao, Numerical Sound Synthsis, Chapter 2
%   Intro to Control - 6.1 State-Space Model Basics, https://www.youtube.com/watch?v=g9G8b7FxEHc
%
% - Pelle Juul, PMSS, SMC8 2018

% Basic parameters
fs = 4*44100;       % The sample rate, higher samplerate yields higher precision
T = 1 / fs;         % The sample period
N = fs * 3;         % The length of our output matrix
y = zeros(1, N);    % The output matrix

% Model parameters
k = 10000;      % The spring constant
m = 0.002;      % The mass of our mass
b = 0.006;      % The dampening coefficient

% State-space model states
x = [0.0; 0.0]; % The position and velocity states
u = [500000];   % The input force
u1 = [0.0];     % The previous input force

% State-space model matrices
A = [0 1; (-k/m) (-b/m)];               % Position/velocity contributions to derivatives
B = [0; 1/m];                           % Input forces contributions to derivatives
C = [1 0 ];                             % Output mapping
H = inv((2 / T) * eye(size(A)) - A);    % Matrix constant found using the trapezoid rule

% Main update loop
for i = 1:N
    % Apply the update rule
    x = H * ((2 / T) * eye(size(A)) + A) * x + H * B * (u + u1);
    % Do the output mapping
    y(i) = C * x;    
    % Store the current input force
    u1 = u;
    
    % Remove input force after first iteration
    if i == 1
        u = [0.0];
    end
end

plot(y);
soundsc(y, fs);