
#ifndef MINIMIZER_TRAITS_HPP_
#define MINIMIZER_TRAITS_HPP_
#include "Eigen/Core"
#include <functional>

using Scalar = double;
using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
using D0 = std::function<Scalar(const Vector&)>;
using D1 = std::function<Vector(const Vector&)>;


#endif /* MINIMIZER_TRAITS_HPP_ */