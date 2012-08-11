/*
 * random_graph.cpp
 *
 *  Created on: Mar 1, 2012
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */

#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include <boost/archive/binary_oarchive.hpp>

#include <boost/graph/adj_list_serialize.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

#include <boost/timer/timer.hpp>

#include <boost/tuple/tuple.hpp>

#define N 5
#define EDGE_WEIGHT_MIN 0.0
#define EDGE_WEIGHT_MAX 1.0
#define EDGE_SPARCITY   0.9

// Property types
typedef int VertexIndexType;
typedef double EdgeWeightType;
typedef boost::property<boost::vertex_index_t, VertexIndexType> VertexProperties;
typedef boost::property<boost::edge_weight_t, EdgeWeightType> EdgeProperties;

// Graph data structures
typedef boost::adjacency_list<boost::listS, boost::listS, boost::directedS, VertexProperties, EdgeProperties> Graph;
typedef boost::property_map<Graph, boost::vertex_index_t>::const_type VertexIndexMap;
typedef boost::property_map<Graph, boost::vertex_distance_t>::const_type VertexDistanceMap;
typedef boost::property_map<Graph, boost::edge_weight_t>::const_type EdgeWeightMap;

// Descriptors and iterators
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef std::map<Vertex, std::map<Vertex, EdgeWeightType> > VertexPairDistanceMap;

// For RNG and edge generation
typedef boost::minstd_rand RandomNumberGenerator;
typedef boost::uniform_real<EdgeWeightType> RandomEdgeDistribution;
typedef boost::variate_generator<RandomNumberGenerator&, RandomEdgeDistribution> RandomEdgeGenerator;
typedef boost::generator_iterator<RandomEdgeGenerator> RandomEdgeGeneratorIterator;

// TODO does boost::print_graph(const Graph&) work?
std::ostream&
operator<<(std::ostream&, const Graph&);

// Utility function
void
dist_map_to_matrix(const Graph&, VertexPairDistanceMap&, EdgeWeightType**);

// Checking the result of APSP
bool
check_distances(const Graph&, EdgeWeightType**);

int
main(int argc, char** argv)
{
	// Populate a graph with N vertices
	Graph g;
	for (int i = 0; i < N; ++i) {
		boost::add_vertex(i, g);
	}

	// Setup a mechanism for randomness
	RandomNumberGenerator RNG(static_cast<uint32_t>(time(NULL)));
	RandomEdgeDistribution range(EDGE_WEIGHT_MIN, EDGE_WEIGHT_MAX);
	RandomEdgeGenerator gen(RNG, range);
	RandomEdgeGeneratorIterator genit(&gen);

	// Add randomly-weighted edges
	VertexIterator v1it, v1itend, v2it, v2itend;
	for (boost::tie(v1it, v1itend) = boost::vertices(g); v1it != v1itend; ++v1it) {
		for (boost::tie(v2it, v2itend) = boost::vertices(g); v2it != v2itend; ++v2it) {
			if (*v1it != *v2it && !(*genit++ < EDGE_SPARCITY)) {
				boost::add_edge(*v1it, *v2it, *genit++, g);
			}
		}
	}

	// Write the graph to a binary file
	if (argc == 2) {
		std::ofstream output_file_stream(argv[1], std::ios::out | std::ios::binary);
		if(!output_file_stream) {
			std::cerr << "[ERROR] failure writing to '" << argv[1] << "'" << std::endl;
			return (EXIT_FAILURE);
		}
		boost::archive::binary_oarchive output_archive(output_file_stream);
		output_archive << g;
		output_file_stream.close();
	} else {
		// Create a timer
		boost::timer::cpu_timer timer;
		timer.stop();
		double load = static_cast<double>(N * N) / std::log(N);
		std::cout << "num_vertices(g) = " << boost::num_vertices(g) << std::endl;
		std::cout << "num_edges(g) = " << boost::num_edges(g) << std::endl;
		std::cout << "load(g) = " << load << std::endl;

		// Calculate all-pairs shortest path
		EdgeWeightType ** distance_matrix = new EdgeWeightType*[N];
		for (int i = 0; i < N; ++i) {
			distance_matrix[i] = new EdgeWeightType[N];
		}
		if (boost::num_edges(g) < load) {
			std::cout << "Running Johnson APSP Algorithm... " << std::endl;
			timer.start();
			boost::johnson_all_pairs_shortest_paths(g, distance_matrix);
			timer.stop();
		} else {
			std::cout << "Running Floyd-Warshall APSP Algorithm... " << std::endl;
			VertexPairDistanceMap dist;
			timer.start();
			boost::floyd_warshall_all_pairs_shortest_paths(g, dist);
			timer.stop();
			// TODO better way than dumping?
			dist_map_to_matrix(g, dist, distance_matrix);
		}
		std::cout << timer.format() << std::endl;
		assert(check_distances(g, distance_matrix));
		for (int i = 0; i < N; ++i) {
			delete[] distance_matrix[i];
		}
		delete[] distance_matrix;

		// Calculate MST
		std::vector<Edge> mst;
		if (boost::num_edges(g) < N) {
			std::cout << "Running Kruskal's Algorithm... " << std::endl;
			timer.start();
			boost::kruskal_minimum_spanning_tree(g, std::back_inserter(mst));
			timer.stop();
		} else {
			std::cout << "Running Prim's Algorithm... " << std::endl;
			//std::vector<Vertex> tst(boost::num_vertices(g));
			timer.start();
			// boost::prim_minimum_spanning_tree(g, &tst[0]);
			timer.stop();
		}
		std::cout << "MST has " << mst.size() << " edge(s)!" << std::endl;
		std::cout << timer.format() << std::endl;
	}

	#if N < 10
	// Print the graph
	std::cout << g << std::endl;
	#endif

	return (EXIT_SUCCESS);
}

void dist_map_to_matrix(const Graph& g, VertexPairDistanceMap& src, EdgeWeightType** dst) {
	VertexIndexMap vertex_indices = boost::get(boost::vertex_index, g);

	VertexIterator v1it, v1itend, v2it, v2itend;
	for (boost::tie(v1it, v1itend) = boost::vertices(g); v1it != v1itend; ++v1it) {
		for (boost::tie(v2it, v2itend) = boost::vertices(g); v2it != v2itend; ++v2it) {
			int v1index = boost::get(vertex_indices, *v1it);
			int v2index = boost::get(vertex_indices, *v2it);
			dst[v1index][v2index] = src[*v1it][*v2it];
		}
	}
}

bool
check_distances(const Graph& g, EdgeWeightType** d) {
	// Fetch a listing of the graph's properties
	VertexIndexMap vertex_indices = boost::get(boost::vertex_index, g);
	EdgeWeightMap edge_weights = boost::get(boost::edge_weight, g);

	VertexIndexType edge_source_index, edge_target_index;
	EdgeWeightType edge_weight;

	// Check that w(u,v) is an upper bound on dist[u][v]
	EdgeIterator eit, eitend;
	for (boost::tie(eit, eitend) = boost::edges(g); eit != eitend; ++eit) {
		edge_source_index = boost::get(vertex_indices, source(*eit, g));
		edge_target_index = boost::get(vertex_indices, target(*eit, g));
		edge_weight = boost::get(edge_weights, *eit);
		if (edge_weight < d[edge_source_index][edge_target_index]) {
			return false;
		}
	}

	return true;
}

std::ostream&
operator<<(std::ostream& ostr, const Graph& g)
{
	// Fetch a listing of the graph's properties
	VertexIndexMap vertex_indices = boost::get(boost::vertex_index, g);
	EdgeWeightMap edge_weights = boost::get(boost::edge_weight, g);

	VertexIndexType edge_source_index, edge_target_index;
	EdgeWeightType edge_weight;

	// Dump information about the edges to the output stream
	EdgeIterator eit, eitend;
	for (boost::tie(eit, eitend) = boost::edges(g); eit != eitend; ++eit) {
		edge_source_index = boost::get(vertex_indices, source(*eit, g));
		edge_target_index = boost::get(vertex_indices, target(*eit, g));
		edge_weight = boost::get(edge_weights, *eit);
		ostr << "w(" << edge_source_index << "," << edge_target_index << ") = "
				<< std::fixed << std::setprecision(2) << edge_weight << std::endl;
	}

	// Dump information about each vertex's neighbors
	VertexIterator vit, vitend;
	OutEdgeIterator oeit, oeitend;
	for (boost::tie(vit, vitend) = boost::vertices(g); vit != vitend; ++vit) {
		edge_source_index = boost::get(vertex_indices, *vit);
		ostr << "Vertex '" << edge_source_index << "' is adjacent to "
				<< out_degree(*vit, g) << " other(s):" << std::endl;
		for (boost::tie(oeit, oeitend) = boost::out_edges(*vit, g); oeit != oeitend; ++oeit) {
			edge_target_index = boost::get(vertex_indices, target(*oeit, g));
			edge_weight = boost::get(edge_weights, *oeit);
			std::cout << "\tVertex '" << edge_target_index << "' with weight: " << edge_weight << std::endl;
		}
	}
	return ostr;
}
