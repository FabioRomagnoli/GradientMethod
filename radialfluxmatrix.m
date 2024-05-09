% RADIALFLUXMATRIX:
% Summary: 
%       approximates the discretization of the advection-diffusion flux in radial
%       coordinates
% Args: 
%       r:   A vector of radial coordinates.
%       v:   A vector representing the potential at r (phi)
%       mu:  The mobility coefficient, (diffusivity or electrical mobility)
%       Vth: Thermal voltage
%       z:   The valence number or charge number
%
% Return: 
%       F:   Discretized form of flux operator for continuity equation


function F = radialfluxmatrix (r, v, mu, Vth, z)

  % This establishes the size of the matrix F based on the number of radial positions.
  ndof = numel (r);
  % Computes a scaled difference of the potential v across adjacent radial points
  DV = z .* diff (v) ./ Vth;
  % Computes the Bernoulli functions Bp and Bm for the difference values DV.
  % These functions are typically used to handle sharp gradients or discontinuities
  [Bp, Bm] = bimu_bernoulli (DV);
   

  % f0l, f0r: Components of the flux moving to the left and right, 
  % scaled negatively with the Bernoulli function Bp. These terms might 
  % represent a diffusion-like flux adjusted for the non-uniform grid 
  % spacing in radial coordinates.
  % f1l, f1r: Similar to f0l and f0r, but scaled positively with the
  % Bernoulli function Bm, likely representing an advection-like 
  % component in the opposite direction.

  f0l  = mu ./ (r(1:end-1) .* log(r(1:end-1)./r(2:end))) .* (-Vth .* Bp');
  f0r  = mu ./ (r(2:end)   .* log(r(1:end-1)./r(2:end))) .* (-Vth .* Bp');
  f1l  = mu ./ (r(1:end-1) .* log(r(1:end-1)./r(2:end))) .* ( Vth .* Bm');
  f1r  = mu ./ (r(2:end)   .* log(r(1:end-1)./r(2:end))) .* ( Vth .* Bm');
  

  % Constructs the sparse matrix F using diagonal (main, lower, and upper)
  % elements representing the radial flux components. This matrix
  % formulation captures the discrete representation of the flux terms for 
  % a continuity equation on a radial mesh.
  % Multiplication by diag(r) adjusts each term by the radial position, 
  % essential in radial systems to account for the geometric factor of 
  % the volume or area element (e.g., 2πr2πr in cylindrical coordinates).

  dd = [f0l zeros(size(mu))] - [zeros(size(mu))  f1r];
  du = [zeros(size(mu)) f1l];
  dl = [-f0r zeros(size(mu))];
  
  F = spdiags ([dl; dd; du]', [-1, 0, 1], ndof, ndof);
  F = diag (r) * F;
end
