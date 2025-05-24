#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <string>
#include <vector/definition.hpp>
#include "double_hash.hpp"

namespace maslevtsov {
  class Graph
  {
  public:
    void add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight);

  private:
    using vertices_pair_t = std::pair< std::string, std::string >;
    using edges_set_t = std::unordered_map< vertices_pair_t, Vector< unsigned >, maslevtsov::PairDoubleHash >;

    edges_set_t edges_set;
  };
}

#endif
