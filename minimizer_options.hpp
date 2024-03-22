
#ifndef MINIMIZER_OPTIONS_HPP_
#define MINIMIZER_OPTIONS_HPP_

#include <vector>
#include "minimizer_traits.hpp"

struct MinimizerParams
{
	Scalar stpTol = 1e-6;
	Scalar resTol = 1e-6;		
	std::vector<Scalar> init ={0.0,0.0};
	unsigned int kMax = 100;
	Scalar a0 = 0.1;
	Scalar sig = 0.1;
	Scalar mu = 0.1;  

    int rateMethod = 0; 
	int gradMethod = 0; 

};

struct MinimizerData 
{
    ConstD0 cFun;
    ConstD1 cGFun;
};

enum Lrate {
	EXP_DECAY = 0, 
	INV_DECAY = 1, 
	ARMAJO = 2
};

enum FDType
{
	ANALYTIC = 0,
  	CENTERED = 1,
 	FORWARD = 2,
  	BACKWARD = 3
};



#endif /* MINIMIZER_TRAITS_HPP_ */