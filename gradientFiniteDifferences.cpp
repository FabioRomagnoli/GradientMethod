#include "gradientFiniteDifferences.hpp"

void GradFD::gradInit(Vector const &x){
    n = x.size();
    h = std::max(smallNumber, x.norm() * smallNumber);
    e = Vector::Zero(n);
}

Vector Centered::operator()(Vector const &x){
    gradInit(x);
    Vector res(n);
    auto h2 = 1. / (2.0 * h);
    for(decltype(n) i = 0u; i < n; ++i){
        e(i) = h;
        res(i) = h2 * (f(x + e) - f(x - e));
        e(i) = 0.;
    }
    return res;
}

Vector Forward::operator()(Vector const &x){
    gradInit(x);
    Vector res(n);
    auto f0 = f(x);
    auto h2 = 1. / h;
    for(std::size_t i = 0u; i < n; ++i){
        e(i) = h;
        res(i) = (f(x + e) - f0) * h2;
        e(i) = 0;
    }
    return res; 
}

Vector Backward::operator()(Vector const &x){
    gradInit(x);
    Vector res(n);
    auto f0 = f(x);
    auto h2 = 1. / h;
    for(std::size_t i = 0u; i < n; ++i){
          e(i) = h;
          res(i) = (f0 - f(x - e)) * h2;
          e(i) = 0.;
    }
    return res;
}
