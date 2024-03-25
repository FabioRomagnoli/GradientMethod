#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "minimizer.hpp"
#include "functionParser.hpp"
#include "GetPot"

#include <functional>
#include <numbers>
#include <cmath>

MinimizerData initialize_data(const int& varNum, GetPot &datafile, int printFun = 0){
	MinimizerData data;

	//read the function to be minimized
	const std::string pf = datafile("f", "x[0]*x[1] + 4*x[0]^(4) + x[1]^(2) + 3*x[0]");
	if(printFun){
		std::cout << "Parsed function " << pf << std::endl;
	}
	//parse it by giving it the number of variables present.
	functionParser f(varNum,pf);
	//functionParser class is an function object since its () operator is overriden
	data.f = f;

	//vector of functionParser object, elements correspond to each partial derivative
	//in the param file gradient will be represented as space separated array of strings 
	//that represent functions
	std::vector<functionParser> gf;
	const int gradDim = datafile.vector_variable_size("gf");
    if(gradDim > 0 and gradDim == varNum){
        for(int i = 0; i < gradDim; ++i){
			const std::string pgf = datafile("gf", "", i);
			if(printFun){
				std::cout << "Parsed gradient function dx[" << i << "] " << pgf << std::endl;
			}
            gf.emplace_back(varNum, pgf);
		}
	}		
	//gf is passed by copy since it will go out of scope out in this initialization function
	//lambda is used to evaluate each partial derivative separatly and return Eigen vector
	data.gf = [gf](const Vector &x) -> Vector{
		std::vector<double> y;
		for(int i = 0; i < gf.size(); ++i)
            y.push_back(gf[i](x));
		return Eigen::VectorXd::Map(&y[0], y.size());
	};

	return data;
}

MinimizerParams initialize_params(const int& varNum,GetPot& datafile, int printParam = 0){
	const Scalar stpTol = datafile("stpTol", 1e-6);
	const Scalar resTol = datafile("resTol", 1e-6);	

	//vector with initial values is parsed 
    std::vector<Scalar> init;
	const int initSize = datafile.vector_variable_size("init");
    if(initSize > 0 and initSize == varNum) {
        for(int i = 0; i < initSize; ++i) {
            double value = datafile("init", 0.0, i); // i specifies position if space separated array
            init.push_back(value);
        }
	} else {
		std::cerr << "initial values vector not properly defined" << std::endl;
	}

	const unsigned int kMax = datafile("kMax", 100);
	const Scalar a0 = datafile("a0", 0.1);
	const Scalar sig = datafile("sig", 0.1);
	const Scalar mu = datafile("mu", 0.1);

    const int rateMethod = datafile("rateMethod", 0);
	const int gradMethod = datafile("gradMethod", 1);

	if(printParam){
		std::cout << "number of variables " << varNum  << std::endl
		 << "step lenght tollerance " << stpTol  << std::endl
		 << "residual tollerence " << resTol  << std::endl
		 << "max steps " << kMax  << std::endl
		 << "a0 " << a0  << std::endl
		 << "sigma " << sig  << std::endl
		 << "mu " << mu  << std::endl
		 << "learning rate method " << rateMethod  << std::endl
		 << "gradient method " << gradMethod  << std::endl;
	}

	return {stpTol,resTol, init, kMax, a0, sig, mu, rateMethod, gradMethod};
}

int main(int argc, char **argv){

	//GetPot initialization, input takes from file param in folder
	GetPot command_line(argc, argv);
  	const std::string filename = command_line.follow("param","-f");
  	GetPot datafile(filename.c_str());

	const int varNum = datafile("varNum", 2);
	const int printParam = datafile("printParam", 0);
	const int printFun = datafile("printFun", 0);

	//functions and params are initialized
	MinimizerData data = initialize_data(varNum, datafile,printFun);
	MinimizerParams params = initialize_params(varNum, datafile, printParam);

	//class that handles minimzation is istantiated
	Minimizer min(data, params);

	Vector x = mod.minimizer_method();

	std::cout << "minimum found at x = " << x.transpose() << std::endl;
	std::cout << "with function value = " <<  data.f(x) << std::endl;

	return 0;
}