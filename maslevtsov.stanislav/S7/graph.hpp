#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <string>
#include <vector/definition.hpp>
#include <tree/definition.hpp>
#include "double_hash.hpp"

namespace maslevtsov {
  class Graph
  {
  public:
    void add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight);
    Tree< std::string, int > get_vertices() const;
    Tree< std::string, Vector< unsigned > > get_outbound(const std::string& vertice) const;
    Tree< std::string, Vector< unsigned > > get_inbound(const std::string& vertice) const;

  private:
    using vertices_pair_t = std::pair< std::string, std::string >;
    using edges_set_t = std::unordered_map< vertices_pair_t, Vector< unsigned >, maslevtsov::PairDoubleHash >;

    edges_set_t edges_set_;
  };
}

namespace detail {
  template< class T >
  void sort(maslevtsov::Vector< T >& vector)
  {
    if (vector.empty()) {
      return;
    }
    for (size_t i = 0; i < vector.size() - 1; ++i) {
      for (size_t j = 0; j < vector.size() - i - 1; ++j) {
        if (vector[j] > vector[j + 1]) {
          std::swap(vector[j], vector[j + 1]);
        }
      }
    }
  }
}

#endif
