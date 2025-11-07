#include <functional>
#include <iostream>
#include <limits>

#include "commands.hpp"

int main()
{
  using namespace mas;

  std::map< std::string, mas::Circle > shapes;

  std::map< std::string, std::function< void() > > commands;
  try {
    commands["circle"] = std::bind(createCircle, std::ref(std::cin), std::ref(shapes));
    // commands["set"] = std::bind();
    commands["show"] = std::bind(showCircle, std::ref(std::cin), std::ref(std::cout), std::cref(shapes));
    // commands["showset"] = std::bind();
    commands["frame"] = std::bind(showFrame, std::ref(std::cin), std::ref(std::cout), std::cref(shapes));
    // commands["frameset"] = std::bind();
    // commands["spawn"] = std::bind();
    // commands["area-on"] = std::bind();
    // commands["status"] = std::bind();
    // commands["wait"] = std::bind();
  } catch (const std::bad_alloc& e) {
    std::cerr << e.what() << '\n';

    return 1;
  }

  std::string command;
  while ((std::cin >> command) && !std::cin.eof()) {
    try {
      commands.at(command)();
    } catch (const std::out_of_range&) {
      if (std::cin.fail()) {
        std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
      }
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cerr << "<UNKNOWN COMMAND>\n";
    } catch (...) {
      if (std::cin.fail()) {
        std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
      }
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cerr << "<INVALID COMMAND>\n";
    }
  }
}
