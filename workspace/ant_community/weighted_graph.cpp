#include "weighted_graph.h"

/*WeightedGraph::WeightedGraph(int num_vertices, std::unordered_map<pair<int, int>, double >* out_phm, std::unordered_map<pair<int, int>, int >* edges_cross)
{
	this->num_vertices = num_vertices;
	vertex.resize(num_vertices);
	edges.cross_edges = edges_cross;
	edges.cross_phm = out_phm;
}*/

/*WeightedGraph::WeightedGraph(Graph& graph)
{
	num_vertices = 0;
	vertex.resize(graph.num_vertices);
}*/

void WeightedGraph::displayGraph()
{
	std::unordered_map<pair<int, int>, int >::iterator cross_edges_it;
	std::unordered_map<pair<int, int>, double >::iterator cross_phm_it;
	ofstream fout("output.dat");
	for(unsigned int i = 0; i < num_vertices; i++)
	{
		if(vertex[i].id == -1) //if this vertex has been merged, ignore
					continue;

		cout << "Original graph members of vertex " << i << " : \n";

		//COME BACK AND CHANGE THIS (FOR DEBUGGING ONLY)
		std::sort(vertex[i].origNodes.begin(), vertex[i].origNodes.end());


		for(unsigned int j = 0; j < vertex[i].origNodes.size(); j++)
		{
			cout << vertex[i].origNodes[j] + 1  << "  ";
			fout << vertex[i].origNodes[j] + 1 << " ";
		}
		fout << "\n";
		cout << " [ " << vertex[i].weight << " , " << vertex[i].in_links << ", " << vertex[i].total << " ]  ";
		cout << "Degree of vertex = " << vertex[i].degree << "\n";
		cout << "Vertex is connected to clusters with phm: \n";
		pair<int, int> edge;
		for(unsigned int j = 0; j < vertex[i].neighbors.size(); j++)
		{
			unsigned int a = vertex[i].neighbors[j];
			if(i < a)
			{
				edge = make_pair(i, a);
				cross_edges_it = edges.cross_edges.find(edge);
				cross_phm_it = edges.cross_phm.find(edge);
			}
			else if(i > a)
			{
				edge = make_pair(a, i);
				cross_edges_it = edges.cross_edges.find(edge);
				cross_phm_it = edges.cross_phm.find(edge);
			}
			cout << vertex[i].neighbors[j] << " - " << cross_edges_it->second << ", " << cross_phm_it->second << "     ";
		}
		cout << "\n \n";
	}
	cout << "Number of edges = " << edges.cross_edges.size() << "\n\n";

	fout.close();
}

void WeightedGraph::calc_edge_total()
{
	std::unordered_map<pair<int, int>, double >::iterator edge_weight;
	std::unordered_map<pair<int, int>, double >::iterator edge_frac;
	edgeTotal.reserve(edges.cross_edges.size());
	std::pair<int, int> edge;
	double frac;
	for(int i = 0; i < num_vertices; i++)
	{
		for(unsigned int j = 0; j < vertex[i].neighbors.size(); j++)
		{
			if(i < vertex[i].neighbors[j])
			{
				edge = make_pair(i, vertex[i].neighbors[j]);
			}
			else
			{
				edge = make_pair(vertex[i].neighbors[j], i);
			}
			edge_weight = edges.cross_phm.find(edge);
			frac = edge_weight->second / vertex[i].total;
			edge_frac = edgeTotal.find(edge);
			if(edge_frac == edgeTotal.end()) //if this is the first time this is being inserted
			{
				edgeTotal.insert(make_pair(edge, frac));
			}
			else
			{
				edge_frac->second += frac;
			}
		}
	}
}

void WeightedGraph::mergeNodes(int node1, int node2)
{
	//find and remove node2 using std::remove (change later for efficiency)
	vertex[node1].neighbors.erase(std::remove(vertex[node1].neighbors.begin(),
									vertex[node1].neighbors.end(),
									node2),
									vertex[node1].neighbors.end());

	--vertex[node1].degree; //reduce degree by 1

	//create edge (node1,node2)
	pair<int, int> n1_n2;

	if(node1 < node2)
	{
		n1_n2 = make_pair(node1, node2);
	}

	else
	{
		n1_n2 = make_pair(node2, node1);
	}

	//get the edge (node1,node2)
	auto n1_n2_edge_it = edges.cross_edges.find(n1_n2);
	auto n1_n2_phm_it = edges.cross_phm.find(n1_n2);

	//update in_links for node1 (crossing edges + in_links of node2)
	vertex[node1].in_links += n1_n2_edge_it->second + vertex[node2].in_links;

	//update the weight and total of node1
	vertex[node1].weight += vertex[node2].weight + n1_n2_phm_it->second;
	vertex[node1].total += vertex[node2].weight; //since the outgoing phm is already counted

	//add the original nodes of node2 into node1
	vertex[node1].origNodes.insert(vertex[node1].origNodes.end(),
									vertex[node2].origNodes.begin(),
									vertex[node2].origNodes.end());

	//remove edge(node1,node2) from both maps
	edges.cross_edges.erase(n1_n2);
	edges.cross_phm.erase(n1_n2);

	//invalidate this vertex (NEEDS TO BE CHANGED LATER)
	vertex[node2].id = -1;

	//iterate over the neighbors of node2 to update the graph
	for(auto it = vertex[node2].neighbors.begin(); it != vertex[node2].neighbors.end(); it++)
	{
		//if we come across the node we are merging with, skip
		if(*it == node1)
		{
			continue;
		}

		//form the edge with node1 and test if that edge already exists
		pair<int, int> edge;

		if(*it < node1)
		{
			edge = make_pair(*it, node1);
		}
		else
		{
			edge = make_pair(node1, *it);
		}

		//form the edge (node2, neighbor)
		pair<int, int> nb_edge;
		if(*it < node2)
		{
			nb_edge = make_pair(*it, node2);
		}
		else
		{
			nb_edge = make_pair(node2, *it);
		}

		auto edge_it = edges.cross_edges.find(edge); //lookup the edge (crossing number)
		auto phm_it = edges.cross_phm.find(edge); //also get crossing pheromone

		auto nb_edge_it = edges.cross_edges.find(nb_edge); //get edge (node2,neighbor) cross_edges
		auto nb_phm_it = edges.cross_phm.find(nb_edge);

		if(edge_it == edges.cross_edges.end()) //if the edge with node1 does not exist
		{
			//insert this edge into both maps, with the same data for cross edges & phm
			edges.cross_edges.insert(make_pair(edge, nb_edge_it->second));
			edges.cross_phm.insert(make_pair(edge, nb_phm_it->second));

			//remove (node2,neighbor) from both maps
			edges.cross_edges.erase(nb_edge);
			edges.cross_phm.erase(nb_edge);

			//add both node1 and neighbor to each others adjacency lists
			vertex[node1].neighbors.push_back(*it);
			vertex[*it].neighbors.push_back(node1);

			vertex[*it].neighbors.erase(std::remove(vertex[*it].neighbors.begin(),
															vertex[*it].neighbors.end(),
															node2),
															vertex[*it].neighbors.end());

			//increment the degree of node1
			++vertex[node1].degree;
		}
		else //if the edge with node1 exists
		{
			//increment the crossing edges between these 2 by the amount of edge (node2,neighbor)
			edge_it->second = edge_it->second + nb_edge_it->second;

			//also increment the crossing pheromone
			phm_it->second = phm_it->second + nb_phm_it->second;

			//remove (node2,neighbor) from both maps
			edges.cross_edges.erase(nb_edge);
			edges.cross_phm.erase(nb_edge);

			//remove node2 from neighbors adjacency list
			vertex[*it].neighbors.erase(std::remove(vertex[*it].neighbors.begin(),
												vertex[*it].neighbors.end(),
												node2),
												vertex[*it].neighbors.end());

			--vertex[*it].degree;

			//increment node1 degree as new edge was added for it
			//++vertex[node1].degree; (WRONG!)
		}
	} //Done updating the graph
}

void WeightedGraph::mergeClusters(std::vector<pair<pair<int, int>, double > >& fracEdges)
{
	for(auto it = fracEdges.begin(); it != fracEdges.end(); it++) //iterate over the sorted edges
	{
		if(it->second <= 0.1)
			continue;

		pair<int, int> edge = it->first;
		auto edge_it = edges.cross_phm.find(edge); //get the edge, check if it is still valid
		if(edge_it == edges.cross_phm.end()) //edge not found, has been previously deleted
		{
			continue; //then do nothing
		}

		int node1 = it->first.first;
		int node2 = it->first.second;

		//if any node has already been merged with another then skip
		if(vertex[node1].id == -1 || vertex[node2].id == -1)
			continue;

		double node1_frac, node2_frac; //the weight of each node is calculated (normalized)
		node1_frac = vertex[node1].weight / vertex[node1].total;
		node2_frac = vertex[node2].weight / vertex[node2].total;

		if((edge_it->second / vertex[node1].total) > 0.5)
		{
			//if node1 has more elements
			if(vertex[node1].origNodes.size() >= vertex[node2].origNodes.size())
			{
				mergeNodes(node1, node2);
			}
			else //node2 has more elements
			{
				mergeNodes(node2, node1);
			}

		}

		else if((edge_it->second / vertex[node2].total) > 0.5)
		{
			//if node1 has more elements
			if(vertex[node1].origNodes.size() >= vertex[node2].origNodes.size())
			{
				mergeNodes(node1, node2);
			}
			else //node2 has more elements
			{
				mergeNodes(node2, node1);
			}
		}
		//if both nodes are very well connected inside (>=50%), then no don't merge
		else if((node1_frac >= 0.5) && (node2_frac >= 0.5))
		{
			continue;
		}
		else //proceed to merge
		{
			//if node1 has more elements
			if(vertex[node1].origNodes.size() >= vertex[node2].origNodes.size())
			{
				mergeNodes(node1, node2);
			}
			else //node2 has more elements
			{
				mergeNodes(node2, node1);
			}
		}

	}
}

void WeightedGraph::displayFrac()
{
	cout << "\n";
	for(auto it = edgeTotal.begin(); it != edgeTotal.end(); it++)
	{
		cout << "(" << it->first.first << ", " << it->first.second << ") - " <<it->second << "\n";
	}
}

double WeightedGraph::modularity(Graph& g)
{
	double q = 0;
	int tot_deg;
	for(int i = 0; i < num_vertices; i++)
	{
		if(vertex[i].id == -1)
			continue;

		tot_deg = 0;
		for(unsigned int j = 0; j < vertex[i].origNodes.size(); j++)
		{
			tot_deg += g.vertex[vertex[i].origNodes[j]].degree;
		}
		double d = (double) tot_deg / (2 * g.num_edges);
		q += ( ((double) vertex[i].in_links / g.num_edges) - (pow(d, 2)));
	}
	return q;
}
