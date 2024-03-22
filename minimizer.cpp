#include "./minimizer.hpp"


Minimizer::Minimizer(MinimizerData& data_, MinimizerParams& params_): data(data_), params(params_){
    x1 = Eigen::VectorXd::Map(&params.init[0], params.init.size());


    switch(params.rateMethod){
        case EXP_DECAY: setLearnRate(std::make_unique<ExpDecay>()); break; 
        case INV_DECAY: setLearnRate(std::make_unique<InvDecay>()); break; 
        case ARMAJO:    setLearnRate(std::make_unique<Armajo>());   break;  
    }

    switch(params.gradMethod){
        case ANALYTIC: 
            if(data.cGFun)
                break; 
        case CENTERED: setGradMethod(std::make_unique<Centered>(data.cFun)); break;
        case FORWARD:  setGradMethod(std::make_unique<Forward>(data.cFun));  break; 
        case BACKWARD: setGradMethod(std::make_unique<Backward>(data.cFun)); break;  
    }

}


Vector Minimizer::minimizer_method(){
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


void Minimizer::setGradMethod(std::unique_ptr<GradFD> gradMethod) {
    std::shared_ptr gradShared = std::move(gradMethod);
    data.cGFun = [gradShared](const Vector& x) -> Vector {
        return (*gradShared)(x);
    };
}




