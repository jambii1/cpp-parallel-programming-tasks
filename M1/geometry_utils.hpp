#ifndef M1_GEOMETRY_UTILS_HPP
#define M1_GEOMETRY_UTILS_HPP

#include <vector>

namespace mas {
  struct Point
  {
    double x, y;
  };

  using points_c_it_t = std::vector< Point >::const_iterator;

  int getPointsNumInCircle(unsigned radius, points_c_it_t begin, points_c_it_t end) noexcept;
  void generatePointsInSquare(unsigned radius, unsigned tries, unsigned seed, std::vector< Point >& points);

}

#endif
