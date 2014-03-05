#ifndef COMMUNITY_H_
#define COMMUNITY_H_

#include "graph.h"
#include "weighted_graph.h"
#include "helper.h"
#include "cluster_tabu_list.h"

#include <vector>
#include <set>

using namespace std;

class Community
{
	public:
		unsigned int comm; //number of communities formed at the end of the first partition level
		std::vector<int> n2c; //community to which each node belongs
		std::vector<int> in_degree; //no. of links the node has to vertices in its own cluster
		std::vector<int> tot_out; //total out degree of each vertex
		std::vector<std::unordered_map<int, int> > out_degree; //no. of links each node has to different clusters
		std::vector<pair<int, int> > out_degrees; //stores the sorted out_degrees in decreasing order of out degree
		int nodes_replaced;
		std::vector<int> delta; //store delta (indegree - outdegree) for each vertex

		Community(Graph&); //constructor

		WeightedGraph partition_one_level(Graph&, std::vector<Edge>&); //partition the graph with the initial sorted edges given

		void displayPartition(); //displays the partition of the level

		void displayOutdegree(Graph&); //displays out_degree and in_degree of each vertex in the graph

		void sort_out_degrees(); //sort the outdegrees

		void reassign_communities(); //reassign the communities of the nodes based on the out degrees

		void reassign_communities(Graph&); //reassign the communities of the nodes based on the out degrees

		void reassign_communities(ClusterTabuList*);

		void reassign_communities_sigmoid(Helper&);

		void reassign_communities_sigmoid(Helper&, ClusterTabuList*);

		WeightedGraph rebuild_graph(std::vector<Edge>&); //rebuild the new graph after communities have been reassigned

		void recalc_degrees(std::vector<Edge>&); // recalculate the in-degree and out-degree for each node

		void reset_degrees(); //resets the degrees of all vertices

		void recalc_degrees(std::vector<int>&, Graph&); // recalculate the degrees for a specific set of nodes
};

#endif /* COMMUNITY_H_ */
