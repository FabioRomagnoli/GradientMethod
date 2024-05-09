function [omega] = ComputeOmegaTownsend(s, kr)
% COMPUTEOMEGATOWNSEND:
% Summary: 
%       Calculates the net reaciton rates  for electrons, protons, and
%       neutrons. The reactions considered include ionization, attachment, 
%       and two types of recombination (electron-proton and neutron-proton)
%
% Args: 
%       s: concentrations
%       kr: reaction rate coefficients
%
% Return: 
%       Omega: A matrix that stores the net reaction rates, reflecting the 
%       change in concentraction due to the reactions.


omega = zeros(size(s)); %size ns x ns


%n is the concentration, here it is stored as a column vector
n_e   = s(:,1); 
n_p  = s(:,2);  
n_n  = s(:,3);  

% k reaction coefficients
r1  = kr(:,1) .* n_e;        % Ionization
r2  = kr(:,2) .* n_e;        % Attachment
r3  = kr(:,3) .* n_e .* n_p; % Recombination e - p 
r4  = kr(:,3) .* n_n .* n_p; % Recombination n - p

omega(:,1) = r1 - r2 - r3;
omega(:,2) = r1 - r3 - r4;
omega(:,3) = r2 - r4 + 1e8;

end
