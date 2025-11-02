#include <numeric>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <thread>

#include "clicker.hpp"
#include "geometry_utils.hpp"

namespace {
  using seg_it_t = std::vector< double >::iterator;

  void getPointsNumInCircleSegment(unsigned radius, mas::points_c_it_t begin, mas::points_c_it_t end, seg_it_t result)
  {
    *result = mas::getPointsNumInCircle(radius, begin, end);
  }
}

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

  using namespace mas;

  int tries = std::strtol(argv[1], nullptr, 10);
  int seed = argc == 3 ? std::strtol(argv[2], nullptr, 10) : 0;
  int radius = 0;
  int threadNum = 0;

  while ((std::cin >> radius >> threadNum) && !std::cin.eof()) {
    if (radius <= 0 || threadNum <= 0) {
      std::cerr << "Radius or thread number is not a positive number\n";

      return 2;
    }

    std::vector< mas::Point > points;
    try {
      mas::generatePointsInSquare(radius, tries, seed, points);
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';

      return 2;
    }

    double duration_ms = 0.0;
    int pointsNumInCircle = 0;
    {
      try {
        std::vector< std::thread > threads;
        threads.reserve(threadNum);
        std::vector< double > results(threadNum, 0);
        mas::Clicker cl;

        size_t per_th = points.size() / threadNum;
        int i = 0;
        auto it = points.cbegin();
        for (; i < threadNum - 1; ++i) {
          auto end = it + per_th;
          threads.emplace_back(getPointsNumInCircleSegment, radius, it, end, results.begin() + i);
          it = end;
        }
        getPointsNumInCircleSegment(radius, it, it + per_th + points.size() % threadNum, results.begin() + i);
        for (auto&& thread: threads) {
          thread.join();
        }

        pointsNumInCircle = std::accumulate(results.cbegin(), results.cend(), 0);
        duration_ms = cl.millisec();
      } catch (std::bad_alloc& e) {
        std::cerr << e.what() << '\n';

        return 2;
      }
    }

    std::cout << std::fixed << std::setprecision(3);
    std::cout << duration_ms << ' ';

    double circleArea =
      (4.0 * radius * radius) * (static_cast< double >(pointsNumInCircle) / static_cast< double >(points.size()));
    std::cout << circleArea << '\n';
  }

  if (!std::cin.eof()) {
    std::cerr << "Invalid input\n";

    return 2;
  }
}
