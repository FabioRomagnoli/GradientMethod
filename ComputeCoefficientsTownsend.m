% COMPUTECOEFFICIENTSTOWNSEND:
% Summary: 
%       calculates reaction coefficients (kr), mobilities (mu)
%       and diffusivities (D) for a Townsend-type discharge model,
%
% Args: 
%       nr = Number of reactions
%       N =  Number density of the gas
%       Ec = Critical electric field
%       E =  Electric field
%       T =  Temperature of the Gas
%       mu = mobility coefficient (can be given just initalized)
%       D =  Diffusivity coefficient (can be given just initialized)
%       LUT = Look up table (Values of mu, D, alpha, eta for different
%               electric field)
%
% Extra definitions:
%       alpha = Ionization coefficient at the critical electric field.
%       eta =   Attachment coefficient at the critical electric field.
% Return: 
%       kr = Reaction coefficients for each species
%       mu = mobility coefficient for each species
%       D =  Diffusivity coefficient for each species

function [kr, mu, D] = ComputeCoefficientsTownsend(nr,N,Ec,E,T,mu,D,LUT)

% Reaction coefficients (kr)
kr = zeros(size(Ec,1), nr);

% mu_ec: Mobility at the critical electric field.
% alpha: Ionization coefficient at the critical electric field.
% eta:   Attachment coefficient at the critical electric field.
[mu_ec,~,alpha,eta] = GetSwarmParameters(Ec/N*1e21, LUT);

% mu_e: Mobility at the typical electric field.
% D_e: Diffusivity at the typical electric field.
[mu_e,D_e,~,~] = GetSwarmParameters(E/N*1e21, LUT);

kr(:,1) = alpha .* mu_ec .* Ec;
kr(:,2) = eta .* mu_ec .* Ec;
kr(:,3) = 2e-7 * 1e-6;

% mu is mobility, dependent on k
mu(1,:) = mu_e / N;
mu(2,:) = (0.5/N) * (min(0.75e23 * (T).^(-0.5), 2.03e12 * (E/N).^(-0.5)) +...
                     min(1.18e23 * (T).^(-0.5), 3.61e12 * (E/N).^(-0.5)));
mu(3,:) = (1/N) * min(0.97e23 * (T).^(-0.5), 3.56e19 * (E/N).^(-0.1));

%D is diffusivity, dependent on k
D(1,:) = D_e / N;
D([2,3],:) = mu([2,3],:) .* T / 11600;

end
