%% 2D- Waveguide Mesh

%Exciter initial velocity profile (width = 20% of grid)
dim = floor(NJ/5);         % size of the excitation
start = floor((NJ-dim)/2); % position of the exciter (1-dimensional, since I am operating on a line))
vals = zeros(NJ-1,1);      % initializiing the array that holds the excitation
vals(start:start+dim-1) = 0.25*sin(pi*[0:dim-1]/(dim)); % creating a sinusidual excitation signal -> "pulls" the mesh up at that position
valm = vals*transpose(vals);    % makes our 1-dimensional excitation array 2-dimensional through transposition.

%I need:

%Matrix containing incoming velocities
%Matrix containing outgoing velocities
%Matrix 3-dimensional bed with zeros, containing the resulting velocities
%Matrix for low-pass filtering at the boundaries

%PROCESSING in a for-loop
