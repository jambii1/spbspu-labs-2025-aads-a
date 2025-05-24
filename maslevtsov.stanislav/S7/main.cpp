#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
#include <tree/definition.hpp>
#include "graph.hpp"

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
  using graphs_map_t = std::unordered_map< std::string, maslevtsov::Graph, StringDoubleHash >;

  graphs_map_t graphs;
  std::string graph_name;
  while ((fin >> graph_name) && !fin.eof()) {
    size_t edges_count = 0;
    fin >> edges_count;
    maslevtsov::Graph graph;
    for (size_t i = 0; i < edges_count; ++i) {
      std::string vertice1, vertice2;
      unsigned weight = 0;
      fin >> vertice1 >> vertice2 >> weight;
      graph.add_edge(vertice1, vertice2, weight);
    }
    graphs[graph_name] = graph;
  }

  std::unordered_map< std::string, std::function< void() >, StringDoubleHash > commands;

  std::string command;
  while ((std::cin >> command) && !std::cin.eof()) {
    try {
      commands.at(command)();
    } catch (...) {
      std::cerr << "<INVALID COOMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
