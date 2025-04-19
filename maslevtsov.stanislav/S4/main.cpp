#include <iostream>
#include <fstream>
#include <limits>
#include "map_operations.hpp"
#include "tree/definition.hpp"

int main(int argc, char** argv)
{
  using namespace maslevtsov;

  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }
  setmap_t data_map;
  input_setmap(fin, data_map);

  std::string command;
  while (std::cin) {
    std::cin >> command;
    if (std::cin.eof()) {
      break;
    }
    std::string setname;
    try {
      if (command == "print") {
        std::cin >> setname;
        print_set(std::cout, data_map, setname);
        std::cout << '\n';
      } else if (command == "complement") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        complement_sets(data_map, newname, setname, setname2);
      } else if (command == "intersect") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        intersect_sets(data_map, newname, setname, setname2);
      } else if (command == "union") {
        std::string newname, setname2;
        std::cin >> newname >> setname >> setname2;
        union_sets(data_map, newname, setname, setname2);
      } else {
        throw std::invalid_argument("invalid command");
      }
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
