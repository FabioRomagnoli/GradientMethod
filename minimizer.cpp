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
            if(data.gf)
                break; 
        case CENTERED: setGradMethod(std::make_unique<Centered>(data.f)); break;
        case FORWARD:  setGradMethod(std::make_unique<Forward>(data.f));  break; 
        case BACKWARD: setGradMethod(std::make_unique<Backward>(data.f)); break;  
    }

}


Vector Minimizer::minimizer_method(){
    unsigned int k = 0;
    do{
        x = x1;
        double ak = evalRate(k);
        x1 = x - ak * data.gf(x);
        ++k;
    } while(k < params.kMax and (x1 - x).norm() >= params.stpTol and std::abs(data.f(x1) - data.f(x)) >= params.resTol);
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
    data.gf = [gradShared](const Vector& x) -> Vector {
        return (*gradShared)(x);
    };
}




