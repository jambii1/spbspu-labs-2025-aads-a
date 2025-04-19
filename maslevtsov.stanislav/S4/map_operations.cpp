#include "map_operations.hpp"
#include <iostream>

void maslevtsov::input_setmap(std::istream& in, setmap_t& map)
{
  std::string setname, value;
  int key = 0;
  while (in) {
    set_t set;
    in >> setname;
    while (in && in.peek() != '\n') {
      in >> key >> value;
      set.insert(std::make_pair(key, value));
    }
    map.insert(std::make_pair(setname, set));
  }
}

void maslevtsov::print_set(std::ostream& out, const setmap_t& map, const std::string& setname)
{
  set_t set;
  set = map.at(setname);
  if (set.empty()) {
    out << "<EMPTY>";
    return;
  }
  out << setname;
  for (auto it = set.cbegin(); it != set.cend(); ++it) {
    out << ' ' << it->first << ' ' << it->second;
  }
}

void maslevtsov::complement_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    if (set2.find(it->first) == set2.end()) {
      newset.insert(std::make_pair(it->first, it->second));
    }
  }
  map[newname] = newset;
}

void maslevtsov::intersect_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    if (set2.find(it->first) != set2.end()) {
      newset.insert(std::make_pair(it->first, it->second));
    }
  }
  map[newname] = newset;
}

void maslevtsov::union_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
  const std::string& setname2)
{
  set_t set1 = map.at(setname1), set2 = map.at(setname2);
  set_t newset;
  for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
    newset.insert(std::make_pair(it->first, it->second));
  }
  for (auto it = set2.cbegin(); it != set2.cend(); ++it) {
    newset.insert(std::make_pair(it->first, it->second));
  }
  map[newname] = newset;
}
