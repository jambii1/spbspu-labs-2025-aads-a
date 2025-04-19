#ifndef MAP_OPERATIONS_HPP
#define MAP_OPERATIONS_HPP

#include <map>
#include <string>

namespace maslevtsov {
  using set_t = std::map< int, std::string >;
  using setmap_t = std::map< std::string, set_t >;

  void input_setmap(std::istream& in, setmap_t& map);
  void print_set(std::ostream& out, const setmap_t& map, const std::string& setname);
  void complement_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
    const std::string& setname2);
  void intersect_sets(setmap_t& map, const std::string& newname, const std::string& setname1,
    const std::string& setname2);
  void union_sets(setmap_t& map, const std::string& newname, const std::string& setname1, const std::string& setname2);
}

#endif
