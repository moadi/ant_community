#include "community.h"

struct greater_than_key
{
	inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
	{
		return p1.second > p2.second;
	}
};

Community::Community(Graph& graph)
{
	comm = 0;

	n2c.resize(graph.num_vertices, -1);

	in_degree.resize(graph.num_vertices, 0);

	out_degrees.resize(graph.num_vertices);

	out_degree.resize(graph.num_vertices);

	tot_out.resize(graph.num_vertices, 0);

	for(int i = 0; i < graph.num_vertices; i++)
	{
		out_degree[i].reserve(graph.vertex[i].degree);
	}
}

WeightedGraph Community::partition_one_level(Graph& g, std::vector<Edge>& finalEdges)
{
	WeightedGraph wg;

	wg.vertex.resize(g.num_vertices);

	for(auto it = finalEdges.begin(); it != finalEdges.end(); it++)
	{
		int a = it->v1;
		int b = it->v2;
		double phm = it->phm;
		if((n2c[a] == -1) && (n2c[b] == -1)) //both nodes aren't in any community
		{
			n2c[a] = comm; //assign a community to both nodes
			n2c[b] = comm;

			wg.vertex[comm].origNodes.push_back(a); //add the nodes to the orgiNodes vector
			wg.vertex[comm].origNodes.push_back(b);

			wg.vertex[comm].weight += phm; //update the weight of the new vertex and its in_links
			wg.vertex[comm].in_links++;
			wg.vertex[comm].total += phm;

			++in_degree[a];
			++in_degree[b];

			comm++;
		}
		else if(n2c[a] == n2c[b]) //if they are in the same community
		{
			wg.vertex[n2c[a]].in_links++;
			wg.vertex[n2c[a]].weight += phm;
			wg.vertex[n2c[a]].total += phm;

			++in_degree[a];
			++in_degree[b];
		}
		else if(n2c[a] == -1) //a is not in a cluster but b is, assign a to b's cluster
		{
			wg.vertex[n2c[b]].in_links++;
			wg.vertex[n2c[b]].weight += phm;
			wg.vertex[n2c[b]].origNodes.push_back(a);
			wg.vertex[n2c[b]].total += phm;

			n2c[a] = n2c[b];

			++in_degree[a];
			++in_degree[b];
		}
		else if(n2c[b] == -1) //same as above for b
		{
			wg.vertex[n2c[a]].in_links++;
			wg.vertex[n2c[a]].weight += phm;
			wg.vertex[n2c[a]].origNodes.push_back(b);
			wg.vertex[n2c[a]].total += phm;

			n2c[b] = n2c[a];

			++in_degree[a];
			++in_degree[b];
		}
		else if (n2c[a] != n2c[b]) //the 2 nodes are in a different community, update crossing edges and pheromone
		{
			pair<int, int> edge;
			if(n2c[a] < n2c[b])
			{
				edge = make_pair(n2c[a], n2c[b]);
			}
			else
			{
				edge = make_pair(n2c[b], n2c[a]);
			}
			std::unordered_map<pair<int, int>, int >::iterator it1;
			std::unordered_map<pair<int, int>, double >::iterator it2;

			it1 = wg.edges.cross_edges.find(edge);
			it2 = wg.edges.cross_phm.find(edge);

			auto out_deg_it_1 = out_degree[a].find(n2c[b]);
			auto out_deg_it_2 = out_degree[b].find(n2c[a]);

			if(it1 == wg.edges.cross_edges.end()) //if this pair does not exist in the table ==> first crossing edge
			{
				wg.vertex[n2c[a]].degree++;
				wg.vertex[n2c[b]].degree++;

				wg.vertex[n2c[a]].neighbors.push_back(n2c[b]);
				wg.vertex[n2c[b]].neighbors.push_back(n2c[a]);

				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;

				wg.edges.cross_edges.insert(make_pair(edge, 1));
				wg.edges.cross_phm.insert(make_pair(edge, phm));

			}
			else //if the pair exists, then this is another crossing edge
			{
				/*crossing_edges_it->second = crossing_edges_it->second + 1; //increment the number of crossing edges
				out_phm_it->second = out_phm_it->second + phm; //increment crossing pheromone*/

				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;

				it1->second = it1->second + 1;
				it2->second = it2->second + phm;
			}

			if(out_deg_it_1 == out_degree[a].end() && out_deg_it_2 == out_degree[b].end()) //first time this edge is encountered
			{
				out_degree[a].insert(make_pair(n2c[b], 1));
				out_degree[b].insert(make_pair(n2c[a], 1));

				tot_out[a]++;
				tot_out[b]++;
			}
			else if((out_deg_it_1 == out_degree[a].end()) && (out_deg_it_2 != out_degree[b].end()))
			{
				out_degree[a].insert(make_pair(n2c[b], 1));
				out_deg_it_2->second++;

				tot_out[a]++;
				tot_out[b]++;
			}
			else if((out_deg_it_1 != out_degree[a].end()) && (out_deg_it_2 == out_degree[b].end()))
			{
				out_degree[b].insert(make_pair(n2c[a], 1));
				out_deg_it_1->second++;

				tot_out[a]++;
				tot_out[b]++;
			}
			else
			{
				out_deg_it_1->second++;
				out_deg_it_2->second++;

				tot_out[a]++;
				tot_out[b]++;
			}
		}
	}
	wg.vertex.resize(comm);
	wg.num_vertices = comm;

	for(int i = 0; i < comm; i++)
	{
		wg.vertex[i].id = i;
	}
	/*in_links.resize(comm); //resize both the vectors to the number of communities found so far
	community_neighbors.resize(comm);

	communities.resize(comm);

	for(unsigned int i = 0; i < n2c.size(); i++)
	{
		communities[n2c[i]].push_back(i); //write out all the nodes corresponding to their community
	}*/
	return wg;
}

void Community::displayOutdegree(Graph& g)
{
	for(auto it = out_degrees.begin(); it != out_degrees.end(); it++)
	{
		cout << "Degree of " << it->first + 1 << " = " << g.vertex[it->first].degree << "  In = " << in_degree[it->first] << "  Out = " << tot_out[it->first] << "\n\n";
		for(auto it2 = out_degree[it->first].begin(); it2 != out_degree[it->first].end(); it2++)
		{
			cout << " [ " << it2->first << ", " << it2->second << " ]   ";
		}
		cout << "\n\n";
	}
}

void Community::sort_out_degrees()
{
	pair<int, int> vert_out_degree; //holds the vertex and its out degree
	for(unsigned int i = 0; i < tot_out.size(); i++)
	{
		vert_out_degree = make_pair(i, tot_out[i]);
		out_degrees[i] = vert_out_degree;
	}
	std::sort(out_degrees.begin(), out_degrees.end(), greater_than_key());
}

void Community::reassign_communities()
{
	//loop through the nodes in decreasing order of out degrees to different clusters
	int num = 0;
	for(auto it = out_degrees.begin(); it != out_degrees.end(); it++)
	{
		int cluster; //cluster to which this node has max out degree
		int max_out_degree = 0; //stores the max outdegree

		//get the cluster to which it has the max out degree
		for(auto it2 = out_degree[it->first].begin(); it2 != out_degree[it->first].end(); it2++)
		{
			if(it2->second > max_out_degree) //if the out degree to this cluster is greater, then use this
			{
				max_out_degree = it2->second;
				cluster = it2->first;
			}
		}
		//if the vertex out degree to the cluster is greater than
		//its in degree, then reassign
		if(max_out_degree > in_degree[it->first])
		{
			//cout << "New cluster for node " << it->first + 1 << " =  " << cluster << endl << endl;
			n2c[it->first] = cluster;
		}
	}
}

WeightedGraph Community::rebuild_graph(std::vector<Edge>& finalEdges)
{
	WeightedGraph wg;
	wg.num_vertices = comm;
	wg.vertex.resize(comm);

	//to avoid multiple insertions of nodes in to the origNodes vector
	//use a set to ensure only unique elements are inserted
	std::vector<std::set<int> > nodes;
	std::set<int>::iterator set_it1;
	std::set<int>::iterator set_it2;
	nodes.resize(comm);

	for(int i = 0; i < comm; i++)
	{
		wg.vertex[i].id = i;
	}

	for(auto it = finalEdges.begin(); it != finalEdges.end(); it++)
	{
		int a = it->v1;
		int b = it->v2;
		double phm = it->phm;

		if(n2c[a] == n2c[b]) //if they are in the same community
		{
			wg.vertex[n2c[a]].in_links++;
			wg.vertex[n2c[a]].weight += phm;
			wg.vertex[n2c[a]].total += phm;

			set_it1 = nodes[n2c[a]].find(a);
			set_it2 = nodes[n2c[a]].find(b);

			if((set_it1 == nodes[n2c[a]].end()) && (set_it2 == nodes[n2c[a]].end())) //if both elements aren't present in the set then add to set and origNodes
			{
				wg.vertex[n2c[a]].origNodes.push_back(a); //add the nodes to the orgiNodes vector
				wg.vertex[n2c[a]].origNodes.push_back(b);

				//add to the set as well
				nodes[n2c[a]].insert(a);
				nodes[n2c[a]].insert(b);
			}
			else if((set_it1 != nodes[n2c[a]].end()) && (set_it2 == nodes[n2c[a]].end())) //if a is present in the set but b isn't
			{
				nodes[n2c[a]].insert(b);
				wg.vertex[n2c[a]].origNodes.push_back(b);
			}
			else if((set_it1 == nodes[n2c[a]].end()) && (set_it2 != nodes[n2c[a]].end())) //if b is present in the but a isn't
			{
				nodes[n2c[a]].insert(a);
				wg.vertex[n2c[a]].origNodes.push_back(a);
			}

		}
		else
		{
			pair<int, int> edge;
			if(n2c[a] < n2c[b])
			{
				edge = make_pair(n2c[a], n2c[b]);
			}
			else
			{
				edge = make_pair(n2c[b], n2c[a]);
			}
			std::unordered_map<pair<int, int>, int >::iterator it1;
			std::unordered_map<pair<int, int>, double >::iterator it2;
			it1 = wg.edges.cross_edges.find(edge);
			it2 = wg.edges.cross_phm.find(edge);


			if(it1 == wg.edges.cross_edges.end()) //if this pair does not exist in the table ==> first crossing edge
			{
				wg.vertex[n2c[a]].degree++;
				wg.vertex[n2c[b]].degree++;

				wg.vertex[n2c[a]].neighbors.push_back(n2c[b]);
				wg.vertex[n2c[b]].neighbors.push_back(n2c[a]);

				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;

				wg.edges.cross_edges.insert(make_pair(edge, 1));
				wg.edges.cross_phm.insert(make_pair(edge, phm));

				//TEST!!!
				set_it1 = nodes[n2c[a]].find(a);
				set_it2 = nodes[n2c[b]].find(b);

				if((set_it1 == nodes[n2c[a]].end()) && (set_it2 == nodes[n2c[b]].end())) //if both elements aren't present in the set then add to set and origNodes
				{
					wg.vertex[n2c[a]].origNodes.push_back(a); //add the nodes to the orgiNodes vector
					wg.vertex[n2c[b]].origNodes.push_back(b);

					//add to the set as well
					nodes[n2c[a]].insert(a);
					nodes[n2c[b]].insert(b);
				}
				else if((set_it1 != nodes[n2c[a]].end()) && (set_it2 == nodes[n2c[b]].end())) //if a is present in the set but b isn't
				{
					nodes[n2c[b]].insert(b);
					wg.vertex[n2c[b]].origNodes.push_back(b);
				}
				else if((set_it1 == nodes[n2c[a]].end()) && (set_it2 != nodes[n2c[b]].end())) //if b is present in the but a isn't
				{
					nodes[n2c[a]].insert(a);
					wg.vertex[n2c[a]].origNodes.push_back(a);
				}

			}
			else //if the pair exists, then this is another crossing edge
			{
				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;

				it1->second = it1->second + 1;
				it2->second = it2->second + phm;
			}

		}
	}
	/*for(auto it = wg.vertex.begin(); it != wg.vertex.end();)
	{
		if(it->origNodes.size() == 0)
		{
			it = wg.vertex.erase(it);
		}
		else
		{
			it++;
		}
	}*/
	return wg;
}

/*void Community::displayPartition()
{
	for(unsigned int i = 0; i < community_neighbors.size(); i++)
	{
		cout << "Members of community " << i <<": \n";
		for(unsigned int j = 0; j < communities[i].size(); j++)
		{
			cout << communities[i][j]+1 << " ";
		}
		cout << "[ " << in_phm[i] << ", " << in_links[i] << " ]     ";
		cout << "Degree of community = " << community_degree[i];
		cout << "\n";
		cout << "Community " << i << " is connected to clusters with phm: \n";
		pair<int, int> edge;
		for(unsigned int j = 0; j < community_neighbors[i].size(); j++)
		{
			unsigned int a = community_neighbors[i][j];
			if(i < a)
			{
				edge = make_pair(i, a);
				crossing_edges_it = crossing_edges.find(edge);
				out_phm_it = out_phm.find(edge);
			}
			else if (i > a)
			{
				edge = make_pair(a, i);
				crossing_edges_it = crossing_edges.find(edge);
				out_phm_it = out_phm.find(edge);
			}
			cout << community_neighbors[i][j] << " - " << crossing_edges_it->second << ", " << out_phm_it->second << "   ";
		}
		cout << "\n \n";
	}
}*/

/*WeightedGraph Community::partition2graph()
{
	WeightedGraph g(comm, &out_phm, &crossing_edges);
	for(int i=0 ; i < g.num_vertices; i++)
	{
		g.vertex[i].degree = community_degree[i];
		g.vertex[i].id = i;
		g.vertex[i].in_links = in_links[i];
		g.vertex[i].weight = in_phm[i];
		g.vertex[i].origNodes.resize(communities[i].size());
		g.vertex[i].neighbors.resize(g.vertex[i].degree);
		for(int j = 0; j < communities[i].size(); j++)
		{
			g.vertex[i].origNodes[j] = communities[i][j];
		}
		for(int k = 0; k < community_neighbors[i].size(); k++)
		{
			g.vertex[i].neighbors[k] = community_neighbors[i][k];
		}
	}
	return g;
}*/

/*double Community::modularity(Graph& g, int tot_m)
{
	vector<int> total(comm); //total degree of each community
	int comm_degree; //degree of a community

	for(unsigned int i = 0; i < total.size(); i++)
	{
		comm_degree = 0;
		for(unsigned int j = 0; j < communities[i].size(); j++)
		{
			comm_degree += g.vertex[communities[i][j]].degree;
		}
		total[i] = comm_degree;
	}

	double q = 0;

	for(unsigned int i = 0; i < communities.size(); i++)
	{
		q += ( ( (double) in_links[i] / tot_m) - ( ( ( (double) total[i] / (2 * tot_m)) ) * ( ( (double) total[i] / (2 * tot_m)) ) ));
	}
	return q;
}*/

