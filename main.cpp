#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "minimizer.hpp"
#include "muParserXInterface.hpp"

#include "GetPot"
#include <functional>
#include <numbers>
#include <cmath>


int main(int argc, char **argv){

	GetPot command_line(argc, argv);
  	const std::string filename = command_line.follow("param","-f");
  	GetPot datafile(filename.c_str());
	
	const int varNum = datafile("varNum", 2);
	const std::string parsedFun = datafile("func", "x[0]*x[1] + 4*x[0]^(4) + x[1]^(2) + 3*x[0]");
	const std::string parsedGradFun = datafile("gradFunc", "");

	const Scalar stpTol = datafile("stpTol", 1e-6);
	const Scalar resTol = datafile("resTol", 1e-6);	

    std::vector<Scalar> init;

	const int initSize = datafile.vector_variable_size("init");
    if(initSize > 0 and initSize == varNum) {
        for(int i = 0; i < initSize; ++i) {
            double value = datafile("init", i, 0.0); // Default value can be adjusted as needed
            init.push_back(value);
        }
	}

	const unsigned int kMax = datafile("kMax", 100);
	const Scalar a0 = datafile("a0", 0.1);
	const Scalar sig = datafile("sig", 0.1);
	const Scalar mu = datafile("mu", 0.1);

    const int rateMethod = datafile("rateMethod", 0);
	const int gradMethod = datafile("gradMethod", 1);

	MinimizerData data;

	muParserXInterface<2, Vector> fun;
	std::function<Vector(Vector)> func = fun;
    fun.set_expression(parsedFun);
	data.cFun = [fun](const Vector &x) { 		
		return fun(x)};

	if(!parsedGradFun.empty()){
		muParserXInterface<2, Vector> gradFun;
    	gradFun.set_expression(parsedGradFun);
		data.cGFun = [gradFun](const Vector &x) { return gradFun(x);};

	}

	MinimizerParams params = {stpTol,resTol, init, kMax, a0, sig, mu, rateMethod, gradMethod};

	Minimizer mod(data, params);

	Vector x = mod.minimizer_method();
	std::cout << x.transpose() << std::endl;
	std::cout << data.cFun(x) << std::endl;

	return 0;
}