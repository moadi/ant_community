#include "community.h"

Community::Community(Graph& graph)
{
	comm = 0;

	n2c.resize(graph.num_vertices, -1);

	in_links.resize(graph.num_vertices, 0);

	in_phm.resize(graph.num_vertices, 0);

	community_neighbors.resize(graph.num_vertices);

	community_degree.resize(graph.num_vertices, 0);
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

			in_links[comm]++;
			in_phm[comm] += phm;
			comm++;
		}
		else if(n2c[a] == n2c[b]) //if they are in the same community
		{
			wg.vertex[n2c[a]].in_links++;
			wg.vertex[n2c[a]].weight += phm;
			wg.vertex[n2c[a]].total += phm;

			in_links[n2c[a]]++;
			in_phm[n2c[a]] += phm;
		}
		else if(n2c[a] == -1) //a is not in a cluster but b is, assign a to b's cluster
		{
			wg.vertex[n2c[b]].in_links++;
			wg.vertex[n2c[b]].weight += phm;
			wg.vertex[n2c[b]].origNodes.push_back(a);
			wg.vertex[n2c[b]].total += phm;

			n2c[a] = n2c[b];
			in_links[n2c[b]]++;
			in_phm[n2c[b]] += phm;
		}
		else if(n2c[b] == -1) //same as above for b
		{
			wg.vertex[n2c[a]].in_links++;
			wg.vertex[n2c[a]].weight += phm;
			wg.vertex[n2c[a]].origNodes.push_back(b);
			wg.vertex[n2c[a]].total += phm;

			n2c[b] = n2c[a];
			in_links[n2c[a]]++;
			in_phm[n2c[a]] += phm;
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
			out_phm_it = out_phm.find(edge);
			crossing_edges_it = crossing_edges.find(edge);
			std::unordered_map<pair<int, int>, int >::iterator it1;
			std::unordered_map<pair<int, int>, double >::iterator it2;
			it1 = wg.edges.cross_edges.find(edge);
			it2 = wg.edges.cross_phm.find(edge);
			if(out_phm_it == out_phm.end()) //if this pair does not exist in the table ==> first crossing edge
			{
				wg.vertex[n2c[a]].degree++;
				wg.vertex[n2c[b]].degree++;
				wg.vertex[n2c[a]].neighbors.push_back(n2c[b]);
				wg.vertex[n2c[b]].neighbors.push_back(n2c[a]);
				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;
				wg.edges.cross_edges.insert(make_pair(edge, 1));
				wg.edges.cross_phm.insert(make_pair(edge, phm));

				community_degree[n2c[a]]++;
				community_degree[n2c[b]]++;
				community_neighbors[n2c[a]].push_back(n2c[b]);
				community_neighbors[n2c[b]].push_back(n2c[a]);
				out_phm.insert(make_pair(edge, phm));
				crossing_edges.insert(make_pair(edge, 1));
			}
			else //if the pair exists, then this is another crossing edge
			{
				crossing_edges_it->second = crossing_edges_it->second + 1; //increment the number of crossing edges
				out_phm_it->second = out_phm_it->second + phm; //increment crossing pheromone

				wg.vertex[n2c[a]].total += phm;
				wg.vertex[n2c[b]].total += phm;

				it1->second = it1->second + 1;
				it2->second = it2->second + phm;
			}
		}
	}
	wg.vertex.resize(comm);
	wg.num_vertices = comm;
	in_links.resize(comm); //resize both the vectors to the number of communities found so far
	community_neighbors.resize(comm);

	communities.resize(comm);

	for(unsigned int i = 0; i < n2c.size(); i++)
	{
		communities[n2c[i]].push_back(i); //write out all the nodes corresponding to their community
	}
	return wg;
}

void Community::displayPartition()
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
}

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

double Community::modularity(Graph& g, int tot_m)
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
}

