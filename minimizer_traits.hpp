
#ifndef MINIMIZER_TRAITS_HPP_
#define MINIMIZER_TRAITS_HPP_
#include "Eigen/Core"
#include <functional>

// struct Minimize_traits
// {
  using Scalar = double;
  using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
  using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
  using ConstD0 = std::function<Scalar(Vector const &)>;
  using ConstD1 = std::function<Vector(Vector const &)>;
// };

#endif /* MINIMIZER_TRAITS_HPP_ */