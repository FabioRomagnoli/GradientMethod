#ifndef LEARNRATE_HPP_
#define LEARNRATE_HPP_

#include "minimizer_options.hpp"
#include "minimizer_traits.hpp"


class LearnRate{
    public:
        LearnRate() = default;
        virtual double rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& param) = 0;
};

class Armajo: public LearnRate {
    public:
        double rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& param) override;
};

class ExpDecay: public LearnRate{
    public: 
        double rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& param) override;
};


class InvDecay: public LearnRate{
    public: 
        double rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& param) override;
};


#endif /* LEARNRATE_HPP_ */