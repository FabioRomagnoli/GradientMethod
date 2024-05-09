function A = constructLaplacianMatrix(r, epsilon)
    % constructLaplacianMatrix constructs a matrix representing the Laplacian
    % for the electrostatic potential phi in a radial domain with logarithmic terms.
    %
    % Inputs:
    %   r       - Vector of radial coordinates (must be strictly increasing)
    %   epsilon - Permittivity of the medium (scalar or vector matching length of r)
    %
    % Output:
    %   A       - Sparse matrix representing the Laplacian operator

    N = numel(r);  % Number of grid points

    if numel(epsilon) == 1
        epsilon = epsilon * ones(N, 1);
    end

    % Compute differences and mean permittivities
    log_ratio_pos = log(r(2:end) ./ r(1:end-1));
    log_ratio_neg = log(r(1:end-1) ./ r(2:end));


    eps_half = (epsilon(1:end-1) + epsilon(2:end)) / 2;



    % Compute coefficients
    off_diag_pos = [-eps_half' ./ log_ratio_pos , 0];  % Shift for upper diagonal, append zero
    off_diag_neg = [0 , -eps_half' ./ log_ratio_neg];  % Shift for lower diagonal, prepend zero
    diag_elems = -(off_diag_neg(1:end-1) + off_diag_pos(2:end));

    % Create sparse matrix
    A = spdiags([off_diag_neg(2:end); diag_elems; off_diag_pos(1:end-1)]', [-1, 0, 1], N - 1, N -1 );

    % Handle boundary conditions if necessary
    % For Dirichlet conditions at the boundaries (assuming phi(1) = phi(N) = 0)
    A(1, :) = 0;
    A(N, :) = 0;
    A(1, 1) = 1;
    A(N, N) = 1;

    % Handle boundary conditions (Dirichlet here, modify if necessary)
    A(1,1) = 1;
    A(N,N) = 1;
end
