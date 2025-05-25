#include "commands.hpp"
#include <vector/definition.hpp>

namespace {
  void print_vector(const maslevtsov::Vector< unsigned >& vector, std::ostream& out)
  {
    if (vector.empty()) {
      return;
    }
    out << *vector.cbegin();
    for (auto i = ++vector.cbegin(); i != vector.cend(); ++i) {
      out << ' ' << *i;
    }
  }
}

void maslevtsov::print_graphs(const graphs_map_t& graphs, std::ostream& out)
{
  Tree< std::string, int > names;
  for (auto i = graphs.cbegin(); i != graphs.cend(); ++i) {
    names[i->first];
  }
  out << names.cbegin()->first;
  for (auto i = ++names.cbegin(); i != names.cend(); ++i) {
    out << ' ' << i->first;
  }
}

void maslevtsov::print_vertices(const graphs_map_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  in >> graph_name;
  Graph graph = graphs.at(graph_name);
  Tree< std::string, int > names = graph.get_vertices();
  out << names.cbegin()->first;
  for (auto i = ++names.cbegin(); i != names.cend(); ++i) {
    out << '\n' << i->first;
  }
}

void maslevtsov::print_outbound(const graphs_map_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name, vertice_name;
  in >> graph_name >> vertice_name;
  Graph graph = graphs.at(graph_name);
  Tree< std::string, int > names = graph.get_vertices();
  if (names.find(vertice_name) == names.end()) {
    throw std::invalid_argument("non-existing vertice given");
  }
  Tree< std::string, Vector< unsigned > > outbound = graph.get_outbound(vertice_name);
  out << outbound.cbegin()->first << ' ';
  print_vector(outbound.cbegin()->second, out);
  for (auto i = ++outbound.cbegin(); i != outbound.cend(); ++i) {
    out << '\n' << i->first << ' ';
    print_vector(i->second, out);
  }
}

void maslevtsov::print_inbound(const graphs_map_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name, vertice_name;
  in >> graph_name >> vertice_name;
  Graph graph = graphs.at(graph_name);
  Tree< std::string, int > names = graph.get_vertices();
  if (names.find(vertice_name) == names.end()) {
    throw std::invalid_argument("non-existing vertice given");
  }
  Tree< std::string, Vector< unsigned > > inbound = graph.get_inbound(vertice_name);
  out << inbound.cbegin()->first << ' ';
  print_vector(inbound.cbegin()->second, out);
  for (auto i = ++inbound.cbegin(); i != inbound.cend(); ++i) {
    out << '\n' << i->first << ' ';
    print_vector(i->second, out);
  }
}
