#include <ceceo/interpreter.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

auto open_file(std::filesystem::path const &path) {
  auto stream = std::ifstream(path);
  auto strstream = std::ostringstream();

  strstream << stream.rdbuf();
  return strstream.str();
}

int main(int argc, char *argv[]) {
  if (argc <= 1)
    throw std::runtime_error("missing program to run");

  auto code = open_file(argv[1]);
  auto interpreter = ceceo::interpreter({data(code), size(code)});

  auto result = interpreter.interpret();
  std::cout << "program returned: " << result << '\n';
}
