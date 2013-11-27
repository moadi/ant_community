#include "graph.h"
#include "weighted_graph.h"

#include <vector>

using namespace std;

#ifndef COMMUNITY_H_
#define COMMUNITY_H_

class Community
{
	public:
		unsigned int comm; //number of communities formed at the end of the first partition level
		std::vector<int> n2c; //community to which each node belongs
		std::vector<int> in_links; //number of links inside a community
		std::vector<int> total_degree; //total degree of all vertices in a community
		std::vector<double> in_phm; //total internal pheromone in a community
		std::vector<int> community_degree; //degree of each community

		std::unordered_map<pair<int, int>, double > out_phm; //crossing pheromone between 2 clusters
		std::unordered_map<pair<int, int>, int > crossing_edges; //crossing edges between 2 clusters
		std::unordered_map<pair<int, int>, double >::iterator out_phm_it;
		std::unordered_map<pair<int, int>, int >::iterator crossing_edges_it;

		std::vector<vector<int> > community_neighbors; //neighbors of each community
		std::vector<vector<int> > communities; //stores the nodes of the original graph corresponding to each community

		Community(Graph&); //constructor

		WeightedGraph partition_one_level(Graph&, std::vector<Edge>&); //partition the graph with the initial sorted edges given

		void displayPartition(); //displays the partition of the level

		double modularity(Graph&, int); //returns the modularity of the partition
};

#endif /* COMMUNITY_H_ */
