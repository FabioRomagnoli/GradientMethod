// #include <muParser.h>
#include <functional>
#include <numbers>
#include <cmath>
#include <iostream>
#include <Eigen/Eigen> 


typedef Eigen::VectorXd Vector;

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
};

Vector gradient_method(std::function<double(Vector)> f, std::function<Vector(Vector)> gf, ps p){

	Vector x_1 = Eigen::VectorXd::Map(p.init.data(), p.init.size());
	Vector x;


	unsigned int k = 0;

	do{
		x = x_1;

		double la0 = p.a0;
		while(f(x) - f(x - la0 * gf(x)) < p.sig * la0 * gf(x).squaredNorm()) 
			la0 = la0 / 2;
		std::cout << la0 << std::endl;

		x_1 = x - la0 * gf(x);
		++k;

	} while(k < p.k_max and (x_1 - x).norm() >= p.e_s and std::abs(f(x_1) - f(x)) >= p.e_r);

	return x_1;
}


int main(int argc, char **argv){

	struct ps p = {1e-6,1e-6, {0.0,0.0}, 1000, 2.0, 0.1};

	Vector x = gradient_method(f, gf, p);

	std::cout << x.transpose() << std::endl;
	std::cout << f(x) << std::endl;

	return 0;
}