#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

#include "graph.h"

using namespace std;

#ifndef WEIGHTED_GRAPH_H_
#define WEIGHTED_GRAPH_H_

class WeightedVertex
{
	public:
		int in_links; //number of internal links in this new vertex (can be used to calculate modularity)
		int id; //id of the vertex
		double weight; //weight (or total pheromone) of all the edges within this new vertex
		int degree; //degree of this community
		double total; //total pheromone (in + out) at this vertex
		std::vector<int> origNodes; //nodes from the original graph in this community
		std::vector<int> neighbors; //vertices this one is connected to

		WeightedVertex()
		{
			total = 0;
			in_links = 0;
			weight = 0;
			degree = 0;
		}
};

class WeightedEdges
{
	public:
		std::unordered_map<pair<int, int>, int > cross_edges;
		std::unordered_map<pair<int, int>, double > cross_phm;
};

class WeightedGraph
{
	public:
		int num_vertices;
		std::vector<WeightedVertex> vertex;
		WeightedEdges edges;
		std::unordered_map<pair<int, int>, double > edgeTotal;

		//WeightedGraph(int, std::unordered_map<pair<int, int>, double >*, std::unordered_map<pair<int, int>, int >*);

		//WeightedGraph(Graph&);

		WeightedGraph() { }

		void displayGraph();

		double modularity(Graph&);

		void calc_edge_total();

		void mergeClusters(std::vector<pair<pair<int, int>, double > >&);

		void mergeNodes(int, int);

		void displayFrac();
};

#endif /* WEIGHTED_GRAPH_H_ */
