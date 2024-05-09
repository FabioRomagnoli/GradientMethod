function [mu, D, alpha, eta] = GetSwarmParameters(E_normalized, LokiPath)
    % Load the data from Loki_E_mu_D_alpha_eta.mat
    dataTable = load(fullfile(LokiPath, 'Loki_E_mu_D_alpha_eta.mat'));


    % Suppose the array is a 100x5 matrix and you've successfully accessed it
    % If you want to convert this array to a table with column names:
    columnNames = {'E', 'mu', 'D', 'alpha', 'eta'};
    data = array2table(dataTable.Loki_E_mu_D_alpha_eta, 'VariableNames', columnNames);

    E = data.E;
    mu = data.mu;
    D = data.D;
    alpha = data.alpha; 
    eta = data.eta;

    % Interpolate the swarm parameters based on the normalized electric field
    mu = interp1(E, mu, E_normalized, 'linear', 'extrap');
    D = interp1(E, D, E_normalized, 'linear', 'extrap');
    alpha = interp1(E, alpha, E_normalized, 'linear', 'extrap');
    eta = interp1(E, eta, E_normalized, 'linear', 'extrap');

end
    