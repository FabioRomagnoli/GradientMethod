#ifndef GRADIENTFINITEDIFFERENCE_HPP_
#define GRADIENTFINITEDIFFERENCE_HPP_

#include "Eigen/Dense"
#include "minimizer_traits.hpp"
#include <cmath>
#include <limits>
#include <iostream>

/*
 * Computing the gradient via finite differences. 
 * base class has  virtual () operator, that is overriden to allow choice of
 * forward, backward and centered schemes for the computation of the gradient
 */

class GradFD
{
    public:
        GradFD() = default;

        // Here you pass the function to be derived.
        GradFD(fD0& f_): f(f_){};

        // Here you change the function to be derived.
        void setFunction(fD0& ff)
        {
            f = ff;
        }

        virtual Vector operator()(Vector const &x) = 0;

        void gradInit(Vector const &x);

        virtual ~GradFD() = default;

    protected:
    
        int n;
        Scalar  h;
        Vector e;


        fD0 f;
        // A small number used for differencing
        double const smallNumber = std::sqrt(std::numeric_limits<double>::epsilon());
};


class Centered: public GradFD
{
    public:
        Centered(fD0& func) : GradFD(func) {}
        Vector operator()(Vector const &x) override;
};

class Forward: public GradFD
{
    public:
        Forward(fD0& func) : GradFD(func) {}
        Vector operator()(Vector const &x) override;
};

class Backward: public GradFD
{
    public:
        Backward(fD0& func) : GradFD(func) {}
        Vector operator()(Vector const &x) override;
};


#endif /* GRADIENTFINITEDIFFERENCE_HPP_ */