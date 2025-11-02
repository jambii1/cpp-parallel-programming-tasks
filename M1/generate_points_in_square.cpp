#include "generate_points_in_square.hpp"

#include <random>
#include <stdexcept>

void rndm::generatePointsInSquare(unsigned radius, unsigned tries, unsigned seed, std::vector< geom::Point >& points)
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
