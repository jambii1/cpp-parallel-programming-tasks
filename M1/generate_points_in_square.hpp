#ifndef M1_GENERATE_POINTS_IN_SQUARE_HPP
#define M1_GENERATE_POINTS_IN_SQUARE_HPP

#include <vector>

#include "point.hpp"

namespace rndm {
  void generatePointsInSquare(unsigned radius, unsigned tries, unsigned seed, std::vector< geom::Point >& points);
}

#endif
