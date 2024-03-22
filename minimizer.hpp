#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "learnRate.hpp"

#include <numbers>
#include <cmath>
#include <iostream>
#include <Eigen/Eigen> 
#include <iostream>
#include <memory>


class Minimizer {
    public: 
        Minimizer() = default;
        Minimizer(MinimizerData& data, MinimizerParams& params);

        Vector gradient_method();
        
    private: 
        MinimizerData data;
        MinimizerParams params;
        Vector x;
        Vector x1;

        std::unique_ptr<LearnRate> learnRate;
        void setLearnRate(std::unique_ptr<LearnRate> learnRate);
        double evalRate(unsigned int k);
};



#endif /* MINIMIZER_HPP_ */