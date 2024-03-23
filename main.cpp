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