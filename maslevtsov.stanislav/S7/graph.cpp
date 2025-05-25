#include "graph.hpp"

void maslevtsov::Graph::add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight)
{
  edges_set_[std::make_pair(vertice1, vertice2)].push_back(weight);
}

maslevtsov::Tree< std::string, int > maslevtsov::Graph::get_vertices() const
{
  Tree< std::string, int > vertices;
  for (auto i = edges_set_.cbegin(); i != edges_set_.cend(); ++i) {
    vertices[i->first.first];
    vertices[i->first.second];
  }
  return vertices;
}

maslevtsov::Tree< std::string, maslevtsov::Vector< unsigned > >
  maslevtsov::Graph::get_outbound(const std::string& vertice) const
{
  Tree< std::string, Vector< unsigned > > outbound;
  for (auto i = edges_set_.cbegin(); i != edges_set_.cend(); ++i) {
    if (i->first.first == vertice) {
      for (auto j = i->second.cbegin(); j != i->second.cend(); ++j) {
        outbound[i->first.second].push_back(*j);
      }
      detail::sort(outbound[i->first.second]);
    }
  }
  return outbound;
}

maslevtsov::Tree< std::string, maslevtsov::Vector< unsigned > >
  maslevtsov::Graph::get_inbound(const std::string& vertice) const
{
  Tree< std::string, Vector< unsigned > > outbound;
  for (auto i = edges_set_.cbegin(); i != edges_set_.cend(); ++i) {
    if (i->first.second == vertice) {
      for (auto j = i->second.cbegin(); j != i->second.cend(); ++j) {
        outbound[i->first.first].push_back(*j);
      }
      detail::sort(outbound[i->first.first]);
    }
  }
  return outbound;
}
