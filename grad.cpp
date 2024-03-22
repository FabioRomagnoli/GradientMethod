#include "./grad.hpp"


Grad::Grad(RnR& _f, RnRn& _gf, Param _p): f(_f), gf(_gf), p(_p){
    x_1 = Eigen::VectorXd::Map(&p.init[0], p.init.size());

    switch(p.rateMethod){
        case EXP_DECAY: setLearnRate(std::make_unique<ExpDecay>()); break; 
        case INV_DECAY: setLearnRate(std::make_unique<InvDecay>()); break; 
        case ARMAJO:    setLearnRate(std::make_unique<Armajo>()); break;  
    }
}


Vector Grad::gradient_method(){
    unsigned int k = 0;
    do{
        x = x_1;
        double ak = evalRate(k);
        x_1 = x - ak * gf(x);
        ++k;
    } while(k < p.k_max and (x_1 - x).norm() >= p.e_s and std::abs(f(x_1) - f(x)) >= p.e_r);
    return x_1;
}


void Grad::setLearnRate(std::unique_ptr<LearnRate> learnRate_) {
    this->learnRate = std::move(learnRate_);
}

double Grad::evalRate(double k) {
    if (learnRate) {
        return learnRate->rate(k,f,gf,x,p);
    }
    return 0;
}


double Armajo::rate(double k, RnR f, RnRn gf, Vector x, Param p){
    double ak = p.a0;
    while(f(x) - f(x - ak * gf(x)) < p.sig * ak * gf(x).squaredNorm()) 
        ak = ak / 2;
    return ak;
}

double ExpDecay::rate(double k, RnR f, RnRn gf, Vector x, Param p){
        return p.a0 * exp(-p.mu*k);
}


double InvDecay::rate(double k, RnR f, RnRn gf, Vector x, Param p) {
    return p.a0/(1+p.mu*k);
}


