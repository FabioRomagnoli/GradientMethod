#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "minimizer.hpp"

#include <functional>
#include <numbers>
#include <cmath>

int main(int argc, char **argv){

	//structs contatining the necessary parameters and function for the minimization
	MinimizerParams params = {1e-6,1e-6, {1.0,2.5}, 1000, 0.1, 0.1, 0.1, 2, 1};
	MinimizerData data;

	//lambda function as a function object stored in a struct
	data.cFun = [](const Vector &x) { return x[0]*x[1] + 4*std::pow(x[0],4) + std::pow(x[1],2) + 3 * x[0]; };
	data.cGFun = [](const Vector &x) {
		Vector y(2);
		y << x(1) + 16*std::pow(x(0),3) + 3 , x(0) + 2*x(1);
		return y;
	};

	//class that handles minimzation is istantiated
	Minimizer min(data, params);

	Vector x = min.minimizer_method();
	std::cout << x.transpose() << std::endl;
	std::cout << data.cFun(x) << std::endl;

	return 0;
}