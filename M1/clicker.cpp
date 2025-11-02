#include "clicker.hpp"

mas::Clicker::Clicker():
  start_(std::chrono::high_resolution_clock::now())
{}

double mas::Clicker::millisec() const
{
  auto t = std::chrono::high_resolution_clock::now();
  std::chrono::duration< double, std::milli > f = t - start_;

  return f.count();
}
