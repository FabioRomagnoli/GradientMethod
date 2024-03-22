// #include <muParser.h>
#include <functional>
#include <numbers>
#include <cmath>
#include <iostream>
#include <Eigen/Eigen> 
#include <iostream>
#include <vector>
#include <memory>

typedef Eigen::VectorXd Vector;
typedef std::function<double(Vector)> RnR;
typedef std::function<Vector(Vector)> RnRn;

struct Param{
	double e_r;		
	double e_s;

	std::vector<double> init;

	unsigned int k_max;
	double a0;
	double sig;
	double mu;  
    int rateMethod = 0; 
};


enum L_rate {
	EXP_DECAY = 0, 
	INV_DECAY = 1, 
	ARMAJO = 2
};

class LearnRate{
    public:
        LearnRate() = default;
        virtual double rate(double k, RnR f, RnRn gf, Vector x, Param p) = 0;
};

class Grad {
    public: 
        Grad() = default;
        Grad(RnR& _f, RnRn& _gf, Param _p);

        Vector gradient_method();
        
    private: 
        RnR f;
        RnRn gf;
	    Vector x;
        Vector x_1;
        Param p;

        std::unique_ptr<LearnRate> learnRate;
        void setLearnRate(std::unique_ptr<LearnRate> learnRate);
        double evalRate(double k);
};



class Armajo: public LearnRate {
    public:
        double rate(double k, RnR f, RnRn gf, Vector x, Param p) override;
};

class ExpDecay: public LearnRate{
    public: 
        double rate(double k, RnR f, RnRn gf, Vector x, Param p) override;
};


class InvDecay: public LearnRate{
    public: 
        double rate(double k, RnR f, RnRn gf, Vector x, Param p) override;
};
