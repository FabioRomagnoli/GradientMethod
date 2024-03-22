#include "./minimizer.hpp"


Minimizer::Minimizer(MinimizerData& data_, MinimizerParams& params_): data(data_), params(params_){
    x1 = Eigen::VectorXd::Map(&params.init[0], params.init.size());

    switch(params.rateMethod){
        case EXP_DECAY: setLearnRate(std::make_unique<ExpDecay>()); break; 
        case INV_DECAY: setLearnRate(std::make_unique<InvDecay>()); break; 
        case ARMAJO:    setLearnRate(std::make_unique<Armajo>()); break;  
    }
}


Vector Minimizer::gradient_method(){
    unsigned int k = 0;
    do{
        x = x1;
        double ak = evalRate(k);
        x1 = x - ak * data.cGFun(x);
        ++k;
    } while(k < params.kMax and (x1 - x).norm() >= params.stpTol and std::abs(data.cFun(x1) - data.cFun(x)) >= params.resTol);
    return x1;
}


void Minimizer::setLearnRate(std::unique_ptr<LearnRate> learnRate_) {
    this->learnRate = std::move(learnRate_);
}

double Minimizer::evalRate(unsigned int k) {
    if (learnRate) {
        return learnRate->rate(k, data, x,params);
    }
    return 0;
}



