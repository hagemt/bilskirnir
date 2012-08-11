/* Boost includes */
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/tokenizer.hpp>
#include <boost/tuple/tuple.hpp>

/* Standard includes */
#include <iostream>
#include <fstream>
#include <string>
#include <map>

/* Constants */
#define GRAPH_FILE "./graph.dat"
#define SOURCE_LABEL "Kevin Bacon"

/* Namespace and typedefs */
using namespace boost;
typedef adjacency_list<vecS, vecS, undirectedS,
                       property<vertex_name_t, std::string>,
                       property<edge_name_t,   std::string> > Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::map<std::string, Vertex> LabelMap;

/* Visitor */
template <typename DistanceMap>
class number_recorder : public default_bfs_visitor
{
public:
  number_recorder(DistanceMap dist) : d(dist) { }
  template<typename Edge, typename Graph>
  void tree_edge(Edge e, const Graph& g) const {
    d[target(e, g)] = d[source(e, g)] + 1;
  }
private:
  DistanceMap d;
};

template <typename DistanceMap>
inline number_recorder<DistanceMap>
record_number(DistanceMap d) {
  return number_recorder<DistanceMap>(d);
}

int
main(int argc, char ** argv)
{
  /* Take only two arguments */
  if (argc != 3) {
    std::cerr << "USAGE: " << argv[0] << " graph_file root" << std::endl;
    return EXIT_FAILURE;
  }

  /* Setup the data file */
  std::ifstream graph_file(argv[1]);
  if (!graph_file) {
    std::cerr << "ERROR: '" << argv[1] << "' not found!" << std::endl; 
    return EXIT_FAILURE;
  }

  /* Initialize the data structures */
  Graph g;
  Vertex u, v;
  std::string u_name, v_name;
  property_map<Graph, vertex_name_t>::type v_names = get(vertex_name, g);
  property_map<Graph,   edge_name_t>::type e_names = get(  edge_name, g);
  LabelMap labels;
  LabelMap::iterator it;

  /* Read from the file, split on semicolons */
  bool initial_insertion;
  char_delimiters_separator<char> separator(false, "", ";");
  for (std::string line; std::getline(graph_file, line);) {
    tokenizer<>::iterator i = tokenizer<>(line, separator).begin();

    /* Add the first vertex */
    u_name = *i++;
    boost::tie(it, initial_insertion) =
     labels.insert(std::make_pair(u_name, Vertex()));
    if (initial_insertion) {
      u = add_vertex(g);
      v_names[u] = u_name;
      it->second = u;
    } else {
      u = it->second;
    }

    /* Add the second vertex */
    v_name = *i++;
    tie(it, initial_insertion) =
     labels.insert(std::make_pair(v_name, Vertex()));
    if (initial_insertion) {
      v = add_vertex(g);
      v_names[v] = v_name;
      it->second = v;
    } else {
      v = it->second;
    }

    /* Add an edge between them */
    graph_traits<Graph>::edge_descriptor e;
    tie(e, initial_insertion) = add_edge(u, v, g);
    if (initial_insertion) {
      e_names[e] = *i;
    }
  }

  /* Setup and do BFS to get labels */
  std::vector<int> numbers(num_vertices(g), 0);
  it = labels.find(std::string(argv[2]));
  if (it == labels.end()) {
    std::cerr << "ERROR: Unknown vertex '" << argv[2] << "'" << std::endl;
    return EXIT_FAILURE;
  }
  breadth_first_search(g, it->second, visitor(record_number(&numbers[0])));
  /* TODO better understand what this does                  ^ */

  /* Iterate over the graph, printing numbered vertices */
  graph_traits<Graph>::vertex_iterator i, end;
  for (tie(i, end) = vertices(g); i != end; ++i) {
    std::cout << v_names[*i] << ": " << numbers[*i] << std::endl;
  }
  return EXIT_SUCCESS;
}

