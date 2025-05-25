#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
#include <tree/definition.hpp>
#include "graph.hpp"
#include "bind_functor.hpp"
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS NUMBER>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }

  using namespace maslevtsov;
  using graphs_map_t = std::unordered_map< std::string, Graph, StringDoubleHash >;

  graphs_map_t graphs;
  std::string graph_name;
  while ((fin >> graph_name) && !fin.eof()) {
    size_t edges_count = 0;
    fin >> edges_count;
    Graph graph;
    for (size_t i = 0; i < edges_count; ++i) {
      std::string vertice1, vertice2;
      unsigned weight = 0;
      fin >> vertice1 >> vertice2 >> weight;
      graph.add_edge(vertice1, vertice2, weight);
    }
    graphs[graph_name] = graph;
  }

  std::unordered_map< std::string, IOFuncBinder< graphs_map_t >, StringDoubleHash > commands;
  commands["graphs"] = IOFuncBinder< graphs_map_t >(print_graphs, graphs, std::cout);
  commands["vertexes"] = IOFuncBinder< graphs_map_t >(print_vertices, graphs, std::cin, std::cout);
  commands["outbound"] = IOFuncBinder< graphs_map_t >(print_outbound, graphs, std::cin, std::cout);
  commands["inbound"] = IOFuncBinder< graphs_map_t >(print_inbound, graphs, std::cin, std::cout);

  std::string command;
  while ((std::cin >> command) && !std::cin.eof()) {
    try {
      commands.at(command)();
      std::cout << '\n';
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
