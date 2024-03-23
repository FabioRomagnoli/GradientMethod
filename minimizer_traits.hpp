
#ifndef MINIMIZER_TRAITS_HPP_
#define MINIMIZER_TRAITS_HPP_
#include "Eigen/Core"
#include <functional>

// struct Minimize_traits
// {
  using Scalar = double;
  using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
  // using Vector = Eigen::VectorXd;
  using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
  using fD0 = std::function<Scalar(const Vector&)>;
  using fD1 = std::function<Vector(const Vector&)>;
// };

#endif /* MINIMIZER_TRAITS_HPP_ */