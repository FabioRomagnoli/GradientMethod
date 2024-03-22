#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "minimizer.hpp"
#include "muparser_fun.hpp"
#include "GetPot"

#include <functional>
#include <numbers>
#include <cmath>


Vector gf(Vector x){
	Vector y(2);
	y << x(1) + 16*std::pow(x(0),3) + 3 , x(0) + 2*x(1);
	return y;
}


int main(int argc, char **argv){



GetPot command_line(argc, argv);
  const std::string filename = command_line.follow("param","-f");
  GetPot datafile(filename.c_str());

	// initialization of parameters from file 
	// for now the forcing term is just a string

	const double y0 = datafile("y0", 0.0);
	const double T = datafile("FinalTime", 1.0);
	const unsigned int N = datafile("Nsteps", 100);
	const std::string force_term = datafile("force_term", "-t*+_e^(-y)");

	//string is parsed and a MuparserFun object is constructed from it
  	MuparserFun fun(force_term);

	//allows for control of which scheme is used from param
	const int forEul = datafile("forEul", 0);
	const int crankN = datafile("crankN", 1);
	const int backEul = datafile("backEul", 0);


	if(forEul){
	//theta = 0 for the Forward Euler scheme
	Cauchy forwardEuler(fun, y0, T, N, 0.0);

	//solved, but output ignored.
	//data sent to .dat file for later plotting
	forwardEuler.solve();
	forwardEuler.output_dat("forwardEuler");
	}




























	MinimizerParams params = {1e-6,1e-6, {1.0,2.5}, 1000, 0.1, 0.1, 0.1, 2, 1};
	MinimizerData data;


	data.cFun = [](const Vector &x) { return x[0]*x[1] + 4*std::pow(x[0],4) + std::pow(x[1],2) + 3 * x[0]; };
	data.cGFun = [](const Vector &x) {
		Vector y(2);
		y << x(1) + 16*std::pow(x(0),3) + 3 , x(0) + 2*x(1);
		return y;
	};

	Minimizer mod(data, params);

	Vector x = mod.minimizer_method();
	std::cout << x.transpose() << std::endl;
	std::cout << data.cFun(x) << std::endl;

	return 0;
}