function phi = ComputeElectrostaticPotential(r, epsilon, q, zk, sk)
    % computeElectrostaticPotential calculates the electrostatic potential over a radial domain
    % Inputs:
    %   r       - Vector of radial coordinates
    %   epsilon - Permittivity of the medium
    %   q       - Elementary charge
    %   zk      - Vector of valence numbers for each species
    %   sk      - Matrix of species concentrations, columns correspond to species
    % Output:
    %   phi     - Vector of electrostatic potential at the values of r

    A = ax_laplacian(r, epsilon);  % Get the Laplacian matrix weighted by permittivity


    % Calculate the right-hand side of the Poisson equation
    f = q .* (zk .* sk);  % Row vector of total charge density at each point

    % Solve the linear system
    phi = A \ f;
end
