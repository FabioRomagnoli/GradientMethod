// #include <muParser.h>
#include <functional>
#include <numbers>
#include <cmath>
#include <iostream>
#include <Eigen/Eigen> 


typedef Eigen::VectorXd Vector;

enum class L_rate {
	exp_decay, 
	inv_decay, 
	armijo
};


double f(Vector x){
	return x(0)*x(1) + 4*std::pow(x(0),4) + std::pow(x(1),2) + 3 * x(0);
}

Vector gf(Vector x){
	Vector y(2);
	y << x(1) + 16*std::pow(x(0),3) + 3 , x(0) + 2*x(1);
	return y;
}


struct ps{
	double e_r;		
	double e_s;

	std::vector<double> init;

	unsigned int k_max;
	double a0;
	double sig;
	double mu;  
};

template<L_rate a>
double learning_rate(ps p, std::function<double(Vector)> f, std::function<Vector(Vector)> gf, Vector x, double k){

	if constexpr (a == L_rate::armijo){
		double ak = p.a0;
		while(f(x) - f(x - ak * gf(x)) < p.sig * ak * gf(x).squaredNorm()) 
			ak = ak / 2;
			return ak;

    } else if constexpr (a == L_rate::exp_decay){
        std::cerr << "val2\n";

    } else if constexpr (a == L_rate::inv_decay) {
        std::cerr << "val2\n";

	} else {
		return NULL;
	}
	
}

template<L_rate a>
Vector gradient_method(std::function<double(Vector)> f, std::function<Vector(Vector)> gf, ps p){

	Vector x_1 = Eigen::VectorXd::Map(p.init.data(), p.init.size());
	Vector x;

	unsigned int k = 0;

	do{
		x = x_1;

		double la0 = learning_rate<a>(p, f, gf, x, k);

		x_1 = x - la0 * gf(x);
		++k;

	} while(k < p.k_max and (x_1 - x).norm() >= p.e_s and std::abs(f(x_1) - f(x)) >= p.e_r);

	return x_1;
}


int main(int argc, char **argv){

	struct ps p = {1e-6,1e-6, {0.0,0.0}, 1000, 2.0, 0.1, 2.0};


	Vector x = gradient_method<L_rate::armijo>(f, gf, p);

	std::cout << x.transpose() << std::endl;
	std::cout << f(x) << std::endl;

	return 0;
}