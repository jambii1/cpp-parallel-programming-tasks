#ifndef M1_GET_CIRCLE_AREA_HPP
#define M1_GET_CIRCLE_ARE_HPP

#include <vector>

#include "point.hpp"

namespace circle {
  double getCircleAreaMonteCarlo(int& error, unsigned radius, const std::vector< geom::Point >& points) noexcept;
}

#endif
