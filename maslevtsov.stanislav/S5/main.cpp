#include <fstream>
#include <iostream>
#include <map>
#include <tree/definition.hpp>

int main(int argc, char** argv)
{
  if (argc != 3) {
    std::cerr << "<INVALID PARAMETERS NUMBER>\n";
    return 1;
  }

  std::ifstream fin(argv[2]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }
  std::map< int, std::string > data;
  int key = 0;
  std::string value = "";
  while (fin >> key >> value) {
    data[key] = value;
  }
  if (!fin.eof()) {
    std::cerr << "<INPUT ERROR>\n";
    return 1;
  }
}
