#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <chrono>

#include "generate_points_in_square.hpp"
#include "get_circle_area.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2 || argc > 3) {
    std::cerr << "Invalid command line parameters number\n";

    return 1;
  }
  if (std::strtol(argv[1], nullptr, 10) == 0 || argv[1][0] == '-') {
    std::cerr << "Invalid tries value\n";

    return 1;
  }
  if (argc == 3 && (std::strtol(argv[2], nullptr, 10) == 0 || argv[2][0] == '-')) {
    std::cerr << "Invalid seeed value\n";

    return 1;
  }

  int tries = std::strtol(argv[1], nullptr, 10);
  int seed = argc == 3 ? std::strtol(argv[2], nullptr, 10) : 0;
  int radius = 0;

  while ((std::cin >> radius) && !std::cin.eof()) {
    if (radius <= 0) {
      std::cerr << "Radius is not a positive number\n";

      return 2;
    }

    std::vector< geom::Point > points;

    try {
      rndm::generatePointsInSquare(radius, tries, seed, points);
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';

      return 2;
    }

    int errCircleArea = 0;

    const auto start{std::chrono::high_resolution_clock::now()};
    double circleArea = circle::getCircleAreaMonteCarlo(errCircleArea, radius, points);
    const auto finish{std::chrono::high_resolution_clock::now()};

    if (errCircleArea != 0.0) {
      std::cerr << "Failed to calculate circle area\n";

      continue;
    }

    const std::chrono::duration< double, std::milli > duration_ms = finish - start;

    std::cout << std::fixed << std::setprecision(3);
    std::cout << duration_ms.count();
    std::cout << ' ' << circleArea << '\n';
  }

  if (!std::cin.eof()) {
    std::cerr << "Invalid input\n";

    return 2;
  }
}
