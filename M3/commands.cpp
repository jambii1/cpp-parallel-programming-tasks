#include "commands.hpp"

#include <iostream>

void mas::createCircle(std::istream& in, std::map< std::string, Circle >& shapes)
{
  std::string name;
  int radius = 0;
  Point center{0.0, 0.0};

  in >> name >> radius >> center.x >> center.y;
  if (!in.good() || radius <= 0 || shapes.find(name) != shapes.end()) {
    throw std::invalid_argument("createCircle: invalid input");
  }

  shapes[name] = Circle{radius, center};
}

void mas::showCircle(std::istream& in, std::ostream& out, const std::map< std::string, Circle >& shapes)
{
  std::string name;

  in >> name;
  Circle circle = shapes.at(name);

  out << circle.getRadius() << " (" << circle.getCenter().x << ' ' << circle.getCenter().y << ")\n";
}
