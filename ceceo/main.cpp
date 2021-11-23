#include "ceceo/interpreter.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string open_file(std::filesystem::path const &path) {
  auto stream = std::ifstream(path);
  auto strstream = std::ostringstream();

  strstream << stream.rdbuf();
  return strstream.str();
}

int main([[maybe_unused]] int argc, char *argv[]) {
  auto code =  open_file(argv[1]);
  auto i = ceceo::interpreter({data(code), size(code)});


  auto result = i.interpret();
  std::cout << "program returned: " << result << '\n';
}
