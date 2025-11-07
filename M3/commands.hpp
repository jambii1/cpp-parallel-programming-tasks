#ifndef M3_COMMANDS_HPP
#define M3_COMMANDS_HPP

#include <map>
#include <string>

#include "geometry_utils.hpp"

namespace mas {
  void createCircle(std::istream& in, std::map< std::string, Circle >& shapes);
  void showCircle(std::istream& in, std::ostream& out, const std::map< std::string, Circle >& shapes);
  void showFrame(std::istream& in, std::ostream& out, const std::map< std::string, Circle >& shapes);
  void spawnProcess(std::istream& in);
}

#endif
