#include "graph.hpp"

void maslevtsov::Graph::add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight)
{
  edges_set[std::make_pair(vertice1, vertice2)].push_back(weight);
}
