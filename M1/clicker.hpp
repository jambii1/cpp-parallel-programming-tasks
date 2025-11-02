#ifndef M1_CLICKER_HPP
#define M1_CLICKER_HPP

#include <chrono>

namespace mas {
  class Clicker
  {
  public:
    Clicker();

    double millisec() const;

  private:
    std::chrono::time_point< std::chrono::high_resolution_clock > start_;
  };
}

#endif
