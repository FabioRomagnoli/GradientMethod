% Initialize reaction and species parameters
ns = 3;                         % Number of species
nr = 4;                         % Number of reactions

% Initialize Domain 
Nr = 20;                        % Number of grid points
r = linspace(1, 2, Nr);          % Radial positions
dt = 1e-3;                       % Time step
tF = 0.1;                          % Final time
t = 0:dt:tF;                     % Time array

% Initial conditions for speies concentrations
s_k = zeros(Nr, ns);             % Species concentraction
s_k(Nr/2,:) = [10,10,10];

% Define the thermal voltage function
ThermVoltage = @(T) (1.38e-23 * T) / 1.6e-19;  % Thermal voltage in volts

% Initialize physical quantities 
mu = zeros(ns,1);               % Mobility coefficients 
D = zeros(ns,1);                % Diffusivity coefficients
z = [-1,1,-1];                  % The valence number or charge number

N = 1e23;                       % Number density of the gas (m^-3)
Ec = 100;                       % Critical electric field (V/m)
E = 50;                         % Electric field (V/m)
T = 300;                        % Temperature of the gas (K)
Vth = ThermVoltage(T);  % Calculate the thermal voltage at 300 K

% Path to lookUpTable
LUT = './xx_data/'; 


epsilon = 8.85e-12;        % Permittivity of free space
q = 1.6e-19;               % Elementary charge


% kr = reaction coefficients 
[kr, mu, D] = ComputeCoefficientsTownsend(nr,N,Ec,E,T,mu,D,LUT);
t_idx = 1;
% Time-stepping loop
for time = t
    v = ComputeElectrostaticPotential(r, epsilon, q, z, s_k(:,:,t_idx));

    F = radialfluxmatrix (r, v, mu, Vth, z);

    I = speye(Nr);

    s_k_partial = (I - dt * F) * s_k(:,:,t_idx);

    s_k(:,:,t_idx + 1) = dt*ComputeOmegaTownsend(s_k_partial,kr) +   s_k_partial ;

    t_idx = t_idx + 1;

    disp(t_idx);

    xlabel('Radius');
    ylabel('Species Concentration');
    title('Concentration Profile over domain');
    plot(r, s_k(:,2,t_idx));
    drawnow 

end

% Post-processing or visualization
% hold on;
% plot(r, s_k(:,2,1));
% plot(r, s_k(:,2,end));
% hold off;
% xlabel('Radius');
% ylabel('Species Concentration');
% title('Concentration Profile over domain');



