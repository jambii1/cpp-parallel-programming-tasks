#include "geometry_utils.hpp"

#include <algorithm>
#include <functional>
#include <random>
#include <stdexcept>

namespace {
  bool isPointInCircle(mas::Point pnt, unsigned radius) noexcept
  {
    double dx = pnt.x - radius;
    double dy = pnt.y - radius;

    return dx * dx + dy * dy <= radius * radius;
  }
}

int mas::getPointsNumInCircle(unsigned radius, points_c_it_t begin, points_c_it_t end) noexcept
{
  auto pntsInPred = std::bind(isPointInCircle, std::placeholders::_1, radius);
  int pntsInCircle = std::count_if(begin, end, pntsInPred);

  return pntsInCircle;
}

void mas::generatePointsInSquare(unsigned radius, unsigned tries, unsigned seed, std::vector< Point >& points)
{
  if (radius == 0 || tries == 0 || !points.empty()) {
    throw std::invalid_argument("generatePointsInSquare: invalid arguments");

    return;
  }

  double minX = 0.0, maxX = 2.0 * radius;
  double minY = 0.0, maxY = 2.0 * radius;

  std::mt19937 gen(seed);
  std::uniform_real_distribution< double > distX(minX, maxX);
  std::uniform_real_distribution< double > distY(minY, maxY);

  for (unsigned long i = 0ul; i != tries; ++i) {
    double x = distX(gen);
    double y = distY(gen);

    points.push_back({x, y});
  }
}
