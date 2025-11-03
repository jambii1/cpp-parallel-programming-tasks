#include "geometry_utils.hpp"

mas::Circle::Circle():
  radius_(0.0),
  center_({0.0, 0.0})
{}

mas::Circle::Circle(const Circle& rhs):
  radius_(rhs.radius_),
  center_({rhs.center_.x, rhs.center_.y})
{}

mas::Circle::Circle(int radius, Point center):
  radius_(radius),
  center_({center.x, center.y})
{}

mas::Circle& mas::Circle::operator=(const Circle& rhs)
{
  if (this != &rhs) {
    radius_ = rhs.radius_;
    center_ = rhs.center_;
  }

  return *this;
}

int mas::Circle::getRadius()
{
  return radius_;
}

mas::Point mas::Circle::getCenter()
{
  return center_;
}
