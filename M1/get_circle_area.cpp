#include "get_circle_area.hpp"

#include <algorithm>
#include <functional>

#include "point.hpp"

namespace {
  bool isPointInCircle(geom::Point pnt, unsigned radius) noexcept
  {
    double dx = pnt.x - radius;
    double dy = pnt.y - radius;

    return dx * dx + dy * dy <= radius * radius;
  }
}

double circle::getCircleAreaMonteCarlo(int& error, unsigned radius,
  const std::vector< geom::Point >& points) noexcept
{
  if (radius == 0 || points.empty()) {
    error = 1;

    return 0.0;
  }

  auto pntsInPred = std::bind(isPointInCircle, std::placeholders::_1, radius);
  double pntsInCircle = std::count_if(points.cbegin(), points.cend(), pntsInPred);
  error = 0;

  return (4.0 * radius * radius) * (pntsInCircle / points.size());
}
