#include "learnRate.hpp"

double Armajo::rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& params){
    double ak = params.a0;
    while(data.cFun(x) - data.cFun(x - ak * data.cGFun(x)) < params.sig * ak * data.cGFun(x).squaredNorm()) 
        ak = ak / 2;
    return ak;
}

double ExpDecay::rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& params){
        return params.a0 * exp(-params.mu*k);
}


double InvDecay::rate(unsigned int k, MinimizerData& data, Vector x, MinimizerParams& params) {
    return params.a0/(1+params.mu*k);
}
