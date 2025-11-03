#ifndef M3_GEOMETRY_UTILS_HPP
#define M3_GEOMETRY_UTILS_HPP

namespace mas {
  struct Point
  {
    double x, y;
  };

  class Circle
  {
  public:
    Circle();
    Circle(const Circle& rhs);
    Circle(int radius, Point center);

    Circle& operator=(const Circle& rhs);

    int getRadius();
    Point getCenter();

  private:
    int radius_;
    Point center_;
  };
}

#endif
