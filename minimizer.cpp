#include "./minimizer.hpp"


Minimizer::Minimizer(MinimizerData& data_, MinimizerParams& params_): data(data_), params(params_){
    // maps the initial coordinates to an Eigen vector
    x1 = Eigen::VectorXd::Map(&params.init[0], params.init.size());

    // depending on the choice a different unique pointer is made
    switch(params.rateMethod){
        case EXP_DECAY: setLearnRate(std::make_unique<ExpDecay>()); break; 
        case INV_DECAY: setLearnRate(std::make_unique<InvDecay>()); break; 
        case ARMAJO:    setLearnRate(std::make_unique<Armajo>());   break;  
    }


    switch(params.gradMethod){ 
        // if analyitic is picked but function is not given, falls trough to centered scheme
        case ANALYTIC: 
            if(data.gf)
                break; 
        case CENTERED: setGradMethod(std::make_unique<Centered>(data.f)); break;
        case FORWARD:  setGradMethod(std::make_unique<Forward>(data.f));  break; 
        case BACKWARD: setGradMethod(std::make_unique<Backward>(data.f)); break;  
    }

}


    /* actual computation of minimizer, the three condition (step size, residual, and max iter)
     * are checked as conditions for the loop to continue/
     */
Vector Minimizer::minimizer_method(){
    unsigned int k = 0;
    do{
        x = x1;

        // the overrided method of the parent class is called which falls trough to child clas
        double ak = learnRate->rate(k, data, x,params);
        
        // calls the function object stored in the data struct
        x1 = x - ak * data.gf(x);
        
        ++k;
    } while(k < params.kMax and (x1 - x).norm() >= params.stpTol and std::abs(data.f(x1) - data.f(x)) >= params.resTol);
    return x1;
}

// moves ownership of the unique pointer to the class member parent object
void Minimizer::setLearnRate(std::unique_ptr<LearnRate> learnRate_) {
    this->learnRate = std::move(learnRate_);
}

// uses a shared pointer to allow for the lambda function to bind it to 
// the gradient function in the data struct 
void Minimizer::setGradMethod(std::unique_ptr<GradFD> gradMethod) {
    std::shared_ptr gradShared = std::move(gradMethod);
    data.gf = [gradShared](const Vector& x) -> Vector {
        return (*gradShared)(x);
    };
}




