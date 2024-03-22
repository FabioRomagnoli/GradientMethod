#include "./grad.hpp"


double f(Vector x){
	return x(0)*x(1) + 4*std::pow(x(0),4) + std::pow(x(1),2) + 3 * x(0);
}


Vector gf(Vector x){
	Vector y(2);
	y << x(1) + 16*std::pow(x(0),3) + 3 , x(0) + 2*x(1);
	return y;
}


int main(int argc, char **argv){
	Param p = {1e-6,1e-6, {1.0,2.5}, 1000, 0.1, 0.1, 0.1, 0};

	RnR f_ = f;
	RnRn gf_ = gf; 
	Grad mod(f_, gf_, p);

	Vector x = mod.gradient_method();
	std::cout << x.transpose() << std::endl;
	std::cout << f(x) << std::endl;

	return 0;
}