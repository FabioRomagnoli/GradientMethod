#ifndef MINIMIZER_HPP_
#define MINIMIZER_HPP_

#include "minimizer_traits.hpp"
#include "minimizer_options.hpp"
#include "learnRate.hpp"
#include "gradientFiniteDifferences.hpp"

#include <numbers>
#include <cmath>
#include <iostream>
#include <Eigen/Eigen> 
#include <iostream>
#include <memory>

/*
 * Computes the minimum of a function, which is given in the Data struct.
 * Its behaviour can be changed through the parameters struct
 */
class Minimizer {
    public: 
        Minimizer() = default;
        Minimizer(MinimizerData& data, MinimizerParams& params);
        
        // actual method that handles computation, more can be added
        Vector minimizer_method();
        
    private: 
        MinimizerData data;
        MinimizerParams params;
        Vector x;
        Vector x1;

        /* learning rate computation is handled by a pointer to a function object
         * to allow for different options. 
         */ 
        std::unique_ptr<LearnRate> learnRate;
        // allows for choice of child class through polymorphism
        void setLearnRate(std::unique_ptr<LearnRate> learnRate);

        // allows for choice of child class representing different schemes
        void setGradMethod(std::unique_ptr<GradFD> gradMethod);
};



#endif /* MINIMIZER_HPP_ */