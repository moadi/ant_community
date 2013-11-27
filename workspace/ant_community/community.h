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

		Community(Graph&); //constructor

		WeightedGraph partition_one_level(Graph&, std::vector<Edge>&); //partition the graph with the initial sorted edges given

		void displayPartition(); //displays the partition of the level
};

#endif /* COMMUNITY_H_ */
