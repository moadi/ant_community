#include "community.h"
#include "graph.h"
#include "tabulist.h"
#include "ant.h"
#include "helper.h"
#include "parameters.h"
#include "cluster_tabu_list.h"
//#include "weighted_graph.h"


#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <fstream>

using namespace std;


double eta = 0.5;
double minPhm = 1;
char * outputFile = NULL;
char * inputFile = NULL;
bool found = false; // check if clique is found

void calcNeighborhoodSize(Graph*); //function to calculate intersection size for each vertex with it's neighbors

void split_clusters(WeightedGraph&, Community&, Graph&);

void build_clique(vector<int>&, Graph&, Community&, int&);

bool check_connectivity(vector<int>&, Graph&);

void expand_clique(WeightedGraph&, vector<int>&, Graph&, Community&, int&);

void finalize(WeightedGraph&, Community&);

struct greater_than_key
{
	inline bool operator() (const Edge& e1, const Edge& e2)
	{
		return (e1.phm > e2.phm);
	}
};

struct less_than_key
{
	inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
	{
		return p1.second < p2.second;
	}
};

struct greater_than_key_2
{
	inline bool operator() (const pair<pair<int, int>, double >& p1, const pair<pair<int, int>, double >& p2)
	{
		return p1.second > p2.second;
	}
};

struct greater_than_key_3
{
	inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
	{
		return p1.second > p2.second;
	}
};

/* Function to reset the position of the ants
 * after each iteration is complete
 */

void resetAnts(Ant * ants, Graph * graph, Helper &helper)
{
	//std::uniform_real_distribution<> dis(0,1);
	//std::uniform_int_distribution<> vertex(0, graph->num_vertices-1); //generate a number between 0 and n-1
	for(int i=0; i < graph->num_vertices; i++)
	{
		if(helper.probability() < 0.5)
			ants[i].location = graph->vertex[helper.newVertex()]; //change location if random value is below 0.5
		ants[i].tabulist.clearList();
	}
}

/*Function to choose the next vertex the ant
 * should move to
 */
int chooseNext(Ant* ant, Graph* g, Helper& helper)
{
	unordered_map<pair<int, int>, Edge>::iterator edge_it;
	int cur_vertex = ant->location.id; //current location of ant
	int neighbor;
	pair<int,int> edge;
	int inter_size;
	double sum = 0.0;
	double * adjNodeFitness = new double[ant->location.degree];  //store the value for each adjacent node to the one being considered
	for(int i=0; i < ant->location.degree; i++)  //iterate and update the values
	{
		neighbor = ant->location.neighbors[i]; //get first neighbor

		//make the edge pair to look up hashtable later
		if (cur_vertex < neighbor)
			edge = make_pair(cur_vertex, neighbor);
		else
			edge = make_pair(neighbor, cur_vertex);

		inter_size = ant->location.common[i]; //get intersection size
		edge_it = g->edges.find(edge); //get the edge
		adjNodeFitness[i] = edge_it->second.phm + inter_size; //add the computed value to the array
		sum += adjNodeFitness[i]; //update sum
	}

	for(int i = 0; i < ant->location.degree; i++)
	{
		adjNodeFitness[i] = adjNodeFitness[i]/sum;
	}

	//Generate a random number uniformly distributed in the range [0,1)
	double decision = helper.randomNumber();

	//Choose the next vertex for the ant
	int vertex;// = ant->location.neighbors[0]; //result
	double fitness = 0;
	bool chosen = false;
	for(int i=0; i < ant->location.degree && !chosen; i++)
	{
		fitness += adjNodeFitness[i];
		if(fitness > decision)
		{
			vertex = ant->location.neighbors[i];
			chosen = true;
		}
	}
	delete[] adjNodeFitness;
	return vertex;
}

/*Function to update
 * the pheromone value
 * of each edge
 */
void updatePheromone(Graph* g)
{
	for(auto edge_it = g->edges.begin(); edge_it != g->edges.end(); edge_it++)
	{
		edge_it->second.phm = (1.0 - eta) * edge_it->second.phm + edge_it->second.nVisited * edge_it->second.initPhm;
		if(edge_it->second.phm < 1)
			edge_it->second.phm = 1;
		edge_it->second.nVisited = 0;
	}
}


//write the output to a file
void write_partition(char * output_file, WeightedGraph& wg, Graph& g)
{
	ofstream fout;

	//improve later
	if(outputFile == NULL)
	{
		string output(inputFile);
		string toFind("net");
		string toReplace("clu");
		if(output.find(toFind.c_str()) != string::npos)
		{
			size_t pos = output.find(toFind.c_str());
			output.replace(pos, toFind.length(), toReplace, 0, toReplace.length());
		}
		fout.open(output.c_str());
		cout << "Writing output to: " << output << "\n";
	}
	else
		fout.open(output_file);

	std::vector<int> n2c(g.num_vertices);
	int comm = 1;

	for(int i = 0; i < wg.num_vertices; i++)
	{
		if(wg.vertex[i].id != i || wg.vertex[i].origNodes.size() == 0)
		{
			//++comm;
			continue;
		}
		for(int j = 0; j < wg.vertex[i].origNodes.size(); j++)
		{
			n2c[wg.vertex[i].origNodes[j]] = comm;
			if (j - wg.vertex[i].origNodes.size() == 1)
			{
				++comm;
			}
		}
	}
	fout << "*Vertices " << g.num_vertices << "\n";
	for(int i = 0; i < n2c.size(); i++)
	{
		fout << n2c[i] << "\n";
	}
	fout.close();
}


/*
 * move all
 * the ants on the graph
 * in parallel.
 */
void antsMove(Ant * ants, Graph * g, Helper& helper, Parameters& p)
{
	bool moved;
	typename unordered_map<pair<int, int>, Edge>::iterator edge_it;
	pair<int, int> edge;

	for(int j = 1; j <= p.maxSteps; j++)
	{
		if(j % p.updatePeriod == 0)
		{
			updatePheromone(g);
		}
		//for all ants update their positions if possible
		for(int i = 0; i < g->num_vertices; i++)
		{
			if(ants[i].location.degree == 0) continue;
			int cur_vertex = ants[i].location.id;
			ants[i].tabulist.addToList(cur_vertex); // add current vertex to tabu list
			int numTries = 0;
			moved = false;
			while(numTries < p.maxTries && !moved)
			{
				int next_vertex = chooseNext(&ants[i], g, helper);
				//if the next vertex if not in the tabulist, then move the ant
				if(ants[i].tabulist.searchList(next_vertex) == false)// || ants[i].location.degree <= 2  )
				{
					ants[i].location = g->vertex[next_vertex];
					moved = true;
					if(cur_vertex < next_vertex)
					{
						edge = make_pair(cur_vertex, next_vertex);
						edge_it = g->edges.find(edge);
						if(edge_it == g->edges.end())
						{
							// do nothing
						}
						else
						{
							edge_it->second.nVisited++;
						}
					}
					else
					{
						edge = make_pair(next_vertex, cur_vertex);
						edge_it = g->edges.find(edge);
						if(edge_it == g->edges.end())
						{
							// do nothing
						}
						else
						{
							edge_it->second.nVisited++;
						}
					}
				}
				else
					numTries++;
			}
		}
	}
}

/*
 * Display usage
 */

void usage(char * progName, string errorMsg)
{
	cerr << errorMsg << "\n";
	cerr << "usage: " << progName << " inputFile [options] \n";
	cerr << "inputFile: the graph whose community structure is to be found \n";
	cerr << "-o : specify the output file, extension should be \".clu\" \n";
	exit(EXIT_FAILURE);
}

void parse_args(int argc, char** argv)
{
	if(argc < 2)
	{
		usage(argv[0], "Too few arguments");
	}

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
				case 'o':
					outputFile = argv[i+1];
					i++;
					break;
				default:
					usage(argv[0], "Incorrect options");
					break;
			}
		}
		else
		{
			if(inputFile == NULL)
			{
				inputFile = argv[i];
			}
			else
				usage(argv[0], "Multiple input files");
		}
	}
}

int main(int argc, char **argv)
{
	clock_t start; //calculates time for iteration

	parse_args(argc, argv);

	cout << "Input file : " << inputFile << "\n\n";

	start = clock();

	//read in the graph, given as a command line parameter
	Graph g(inputFile);

	//cout<<"Finalizing 1-hop neighborhood...\n\n";

	// sort the adjacent nodes for each vertex to compute intersection
	for(int i=0; i < g.num_vertices; i++)
		std::sort(g.vertex[i].neighbors, g.vertex[i].neighbors + g.vertex[i].degree);

	//calculate the intersection size of each node with its neighbor
	calcNeighborhoodSize(&g);

	//cout << "Completed...\n\n";
	//cout << "Time for finalizing neighborhood = "<< (clock() - start)/ (double)(CLOCKS_PER_SEC/1000) << " ms \n\n";

	//create the ants and place them on the graph
	Ant * ants = new Ant[g.num_vertices];
	for(int i = 0; i < g.num_vertices; i++)
	{
		ants[i].location = g.vertex[i];
	}

	cout<<"Number of edges = " << g.num_edges << "\n\n";

	cout<<"Number of vertices = " << g.num_vertices << "\n\n";

	Parameters p(g);

	Helper helper(g);

	cout << "Exploration phase....\n\n";

	//exploration of the graph is done by the ants
	for(int i = 0; i < p.maxIterations; i++)
	{
		antsMove(ants, &g, helper, p);
		resetAnts(ants, &g, helper);
		eta = eta * p.decay;
		if (eta < 0.02) //we don't want the evaporation factor to get too small
		{
			eta = 0.02;
		}
	}

	//cout<<"Time for function antsMove = "<<(clock() - start)/ (double)(CLOCKS_PER_SEC/1000)<<" ms \n\n";

	std::vector<Edge> finalEdges;

	for(auto it = g.edges.begin(); it != g.edges.end(); it++)
	{
		finalEdges.push_back(it->second);
	}

	std::sort(finalEdges.begin(), finalEdges.end(), greater_than_key());

	/*for(int i = 0; i < finalEdges.size(); i++)
	{
		cout << finalEdges[i].v1 << " " << finalEdges[i].v2 << " " << finalEdges[i].phm << "\n";
	}*/

	delete[] ants; //remove the ants
	//cout << "\n";


	/*
	 * Begin local optimization
	 */
	cout << "Local optimization....\n\n";
	Community c(g);
	WeightedGraph wg = c.partition_one_level(g, finalEdges);
	//cout << "Modularity of initial partition = " << wg.modularity(g) << "\n\n";


	WeightedGraph best_wg; //keeps track of the best partition so far

	best_wg = c.partition_one_level(g, finalEdges);


	ClusterTabuList * perturb_tabu_list = new ClusterTabuList[g.num_vertices]; //tabu list for each vertex, we don't want to reassign to the same cluster

	//ClusterTabuList* cluster_tabu_list = new ClusterTabuList[g.num_vertices];

	double new_modularity, prev_modularity, best_modularity; //keeps track of modularity

	/*
	 * Initialize all the modularities
	 */
	prev_modularity = wg.modularity(g);
	best_modularity = prev_modularity;

	int decrease = 0, round_one_decrease = 0, final_decrease = 0; // keeps track of number of rounds without improvement

	while(final_decrease < p.max_decrease)
	{
		while(round_one_decrease < p.max_decrease)
		{
				while(decrease < 5)
				{
					c.reset_degrees();
					c.recalc_degrees(finalEdges);
					c.sort_out_degrees();
					c.reassign_communities();
					//c.reassign_communities(cluster_tabu_list);
					//c.reassign_communities_sigmoid(helper);
					//c.reassign_communities_sigmoid(helper, cluster_tabu_list);
					wg = c.rebuild_graph(finalEdges);

					new_modularity = wg.modularity(g);

					if(new_modularity > prev_modularity)
					{
						prev_modularity = new_modularity;
						if(new_modularity > best_modularity)
						{
							best_wg = c.rebuild_graph(finalEdges);
							best_modularity = new_modularity;
						}
					}
					else
					{
						prev_modularity = new_modularity;
						++decrease;
					}
				}

				//best_wg.displayGraph();

				decrease = 0;

				// set the cluster assignments to the best wg
				for(int i = 0; i < best_wg.num_vertices; ++i)
				{
					if((best_wg.vertex[i].id != i) || (best_wg.vertex[i].origNodes.size() == 0))
									continue;

					for(auto it = best_wg.vertex[i].origNodes.begin(); it != best_wg.vertex[i].origNodes.end(); it++)
					{
						c.n2c[*it] = i;
					}
				}
				best_modularity = best_wg.modularity(g);
				wg = c.rebuild_graph(finalEdges); // store the best graph so far in wg

				//merging step
				wg.calc_edge_total();
				std::vector<pair<pair<int, int>, double > > fracEdges;
				fracEdges.resize(wg.edgeTotal.size());
				for(auto it = wg.edgeTotal.begin(); it != wg.edgeTotal.end(); it++)
				{
					pair<int, int> edge = it->first;
					double frac = it->second;
					pair<pair<int, int>, double > frac_edge(edge, frac);
					fracEdges.push_back(frac_edge);
				}
				std::sort(fracEdges.begin(), fracEdges.end(), greater_than_key_2());
				wg.mergeClusters(fracEdges, p); //merge the clusters

				// if there is an improvement, save it to the final_best_wg
				new_modularity = wg.modularity(g);
				if(new_modularity > best_modularity)
				{
					//change cluster assignments to wg as it's better
					for(int i = 0; i < wg.num_vertices; i++)
					{
						if((wg.vertex[i].id != i) || (wg.vertex[i].origNodes.size() == 0))
							continue;

						for(auto it = wg.vertex[i].origNodes.begin(); it != wg.vertex[i].origNodes.end(); it++)
						{
							c.n2c[*it] = i;
						}
					}

					best_modularity = new_modularity;
					best_wg = c.rebuild_graph(finalEdges);
				}

				c.reset_degrees();
				c.recalc_degrees(finalEdges);

				/*
				 * Perturb the best wg
				 */

				//consider reassigning only those nodes with delta in specified range
				for(int i = 0; i < g.num_vertices; i++)
				{
					int max_out_degree = 0;
					int cluster;
					//if the range matches
					if((c.delta[i] > 0) && (c.delta[i] <= 2))
					{
						if(c.out_degree[i].empty()) // if it has no outgoing connections
							continue;

						for(auto it = c.out_degree[i].begin(); it != c.out_degree[i].end(); it++)
						{
							cluster = it->first;
							//if this cluster had been previously considered
							if(perturb_tabu_list[i].searchList(cluster) == true)
								continue; //skip

							if(max_out_degree < 2*abs(c.delta[i]))
								continue;

							if(it->second > max_out_degree)
							{
								cluster = it->first;
								max_out_degree = it->second;
							}
						}

						perturb_tabu_list[i].addToList(c.n2c[i]); //add cluster to tabu list
//						if(cluster_tabu_list[i].searchList(c.n2c[i]) == false)
//						{
//							cluster_tabu_list[i].addToList(c.n2c[i]);
//						}
						c.n2c[i] = cluster;
						//cout << "Replacing...." << "\n\n";
					}
				}

				// recompute the degrees because reassigning clusters might change that
				c.reset_degrees();
				c.recalc_degrees(finalEdges);

				wg = c.rebuild_graph(finalEdges);
				new_modularity = wg.modularity(g);

				// check for improvement
				if(new_modularity > best_modularity) // just change to check
				{
					best_modularity = new_modularity;
					best_wg = c.rebuild_graph(finalEdges);
				}
				else
				{
					++round_one_decrease;
					prev_modularity = new_modularity;
				}
		} // round one of local optimization is complete
		round_one_decrease = 0;

		// reassign cluster assignments to final_best_wg
		for(int i = 0; i < best_wg.num_vertices; i++)
		{
			if((best_wg.vertex[i].id != i) || (best_wg.vertex[i].origNodes.size() == 0))
				continue;

			for(auto it = best_wg.vertex[i].origNodes.begin(); it != best_wg.vertex[i].origNodes.end(); it++)
			{
				c.n2c[*it] = i;
			}
		}

		wg = c.rebuild_graph(finalEdges);

		// try splitting the best_wg
		split_clusters(wg, c, g);
		c.reset_degrees();
		c.recalc_degrees(finalEdges);
		wg = c.rebuild_graph(finalEdges);
		new_modularity = wg.modularity(g);

		// check if splitting improves the solution
		if(new_modularity > best_modularity)
		{
			best_wg = c.rebuild_graph(finalEdges);
			best_modularity = new_modularity;
		}
		else
		{
			++final_decrease;
		}
	}

/*
	// reassign cluster assignments to final_best_wg
	for(int i = 0; i < best_wg.num_vertices; i++)
	{
		if((best_wg.vertex[i].id != i) || (best_wg.vertex[i].origNodes.size() == 0))
			continue;

		for(auto it = best_wg.vertex[i].origNodes.begin(); it != best_wg.vertex[i].origNodes.end(); it++)
		{
			c.n2c[*it] = i;
		}
	}

	for(int i = 0; i < best_wg.num_vertices; i++)
	{
		if((best_wg.vertex[i].id != i) || (best_wg.vertex[i].origNodes.size() == 0))
			continue;

		for(int j = 0; j < best_wg.vertex[i].origNodes.size(); j++)
		{
			cout << best_wg.vertex[i].origNodes[j] << "\n";
		}

		cout << "\n\n";
	}
*/


	cout << "Writing to output.dat...\n\n";

	best_wg.displayGraph();

	//cout << best_wg.modularity(g) << "\n\n";

	cout << helper.seed << "\n\n";

	cout << "Final modularity = " << best_wg.modularity(g) << "\n\n";

	cout << "Total time = " << (clock() - start)/ (double)(CLOCKS_PER_SEC) << " s \n\n";

	std::vector<int> comm_id(4);
	//int j = 0;

	/*for(int i = 0; i < best_wg.num_vertices; i++)
	{
		if(best_wg.vertex[i].origNodes.size() == 0)
			continue;
		else
		{
			comm_id[j] = i;
			j++;
		}
	}

	// Write edges in the same community
	for(auto it = g.edges.begin(); it != g.edges.end(); ++it)
	{
		Edge e = it->second;
		int u = e.v1;
		int v = e.v2;

		if((c.n2c[u]==comm_id[0]) && (c.n2c[v]==comm_id[0]))
		{
			cout << u << " " << v << "\n";
		}
	}

	cout <<"\n\n";

	for(auto it = g.edges.begin(); it != g.edges.end(); ++it)
	{
		Edge e = it->second;
		int u = e.v1;
		int v = e.v2;

		if((c.n2c[u]==comm_id[1]) && (c.n2c[v]==comm_id[1]))
		{
			cout << u << " " << v << "\n";
		}
	}

	cout <<"\n\n";

	for(auto it = g.edges.begin(); it != g.edges.end(); ++it)
	{
		Edge e = it->second;
		int u = e.v1;
		int v = e.v2;

		if((c.n2c[u]==comm_id[2]) && (c.n2c[v]==comm_id[2]))
		{
			cout << u << " " << v << "\n";
		}
	}

	cout <<"\n\n";

	for(auto it = g.edges.begin(); it != g.edges.end(); ++it)
	{
		Edge e = it->second;
		int u = e.v1;
		int v = e.v2;

		if((c.n2c[u]==comm_id[3]) && (c.n2c[v]==comm_id[3]))
		{
			cout << u << " " << v << "\n";
		}
	}

	cout << "\n\n";


	//Write edges in different communities
	for(auto it = g.edges.begin(); it != g.edges.end(); ++it)
	{
		Edge e = it->second;
		int u = e.v1;
		int v = e.v2;

		if(c.n2c[u] != c.n2c[v])
		{
			cout << u << " " << v << "\n";
		}
	}*/


	//cout << (clock() - start)/(double)(CLOCKS_PER_SEC/1000) << "\n\n";

	//cout << "Seed = " << helper.seed << "\n\n";

	// reassign cluster assignments to final_best_wg
//	for(int i = 0; i < best_wg.num_vertices; i++)
//	{
//		if((best_wg.vertex[i].id != i) || (best_wg.vertex[i].origNodes.size() == 0))
//			continue;
//
//		for(auto it = best_wg.vertex[i].origNodes.begin(); it != best_wg.vertex[i].origNodes.end(); it++)
//		{
//			c.n2c[*it] = i;
//		}
//	}
//
//
//	finalize(best_wg, c);
//
//	wg = c.rebuild_graph(finalEdges);
//
//	new_modularity = wg.modularity(g);
//
//	if(new_modularity > best_modularity)
//	{
//		best_modularity = new_modularity;
//		best_wg = c.rebuild_graph(finalEdges);
//	}
//
//	//wg.displayGraph();
//
//	cout << "\n\n Modularity = " << wg.modularity(g) << "\n\n";

	//write_partition(outputFile, new_wg, g);

	//delete[] cluster_tabu_list;
	delete[] perturb_tabu_list;

	return 0;
}

void split_clusters(WeightedGraph& wg, Community& c, Graph& g)
{
	for(int i = 0; i < wg.num_vertices; i++)
	{
		if(wg.vertex[i].origNodes.size() == 0)// || wg.vertex[i].origNodes.size() <= 15) // if empty cluster
		{
			continue;
		}
		std::vector<pair<int, int> > vertices;

		// add the vertices of the cluster to the vector. sort based on degree
		for(auto it = wg.vertex[i].origNodes.begin(); it != wg.vertex[i].origNodes.end(); ++it)
		{
			int degree = g.vertex[*it].degree;
			vertices.push_back(make_pair(*it, degree)); // pair is <vertex, degree>
		}
		std::sort(vertices.begin(), vertices.end(), greater_than_key_3());

		std::vector<int> potential_clique;
		found = false;
		for(auto it = vertices.begin(); it != vertices.end() && !found; ++it)
		{
			build_clique(potential_clique, g, c, it->first);

			// if a clique starting with the current vertex is not found, clear the current potential clique
			if(!found)
				potential_clique.clear();
		}

		if(found)
		{
			//cout << "In cluster " << i << " clique: ";
			expand_clique(wg, potential_clique, g, c, i);
			for(auto it = potential_clique.begin(); it != potential_clique.end(); ++it)
			{
				//cout << *it + 1 << "  ";
			}
			//cout << endl << endl;
		}
	}
}

void expand_clique(WeightedGraph& wg, vector<int>& potential_vertex, Graph& g, Community& c, int& cur_vertex)
{
	int new_cluster = c.comm; //assign the new cluster it's id
	c.comm++;

	/*
	 * change the community assignments for all vertices in the clique to new_cluster.
	 * remove it from the current clusters origNodes vector
	 */
	for(auto it = potential_vertex.begin(); it != potential_vertex.end(); ++it)
	{
		c.n2c[*it] = new_cluster;
		wg.vertex[cur_vertex].origNodes.erase(std::remove(wg.vertex[cur_vertex].origNodes.begin(), wg.vertex[cur_vertex].origNodes.end(), *it),
														  wg.vertex[cur_vertex].origNodes.end());
	}

	// recompute the in and out degrees of all nodes in the current cluster
	c.recalc_degrees(wg.vertex[cur_vertex].origNodes, g);

	// for every node in the current cluster, check its outdegree to new_cluster
	for(auto it = wg.vertex[cur_vertex].origNodes.begin(); it != wg.vertex[cur_vertex].origNodes.end(); ++it)
	{
		auto out_degree_it = c.out_degree[*it].find(new_cluster);

		// if this node is connected to the cluster
		if(out_degree_it != c.out_degree[*it].end())
		{
			// compare the in_degree to the out_degree to this node
			if(out_degree_it->second > c.in_degree[*it])
			{
				int prev_cluster = c.n2c[*it];
				c.n2c[*it] = new_cluster; // reassign the current node's community

				//update the degrees of nodes adjacent to it, only if in the prev_cluster
				for(int i = 0; i < g.vertex[*it].degree; i++)
				{
					int neighbor = g.vertex[*it].neighbors[i];
					if(c.n2c[neighbor] == prev_cluster)
					{
						// check if neighbor is connected to this previously or not
						auto out_degree_it_2 = c.out_degree[neighbor].find(new_cluster);

						// not connected
						if(out_degree_it_2 == c.out_degree[neighbor].end())
						{
							// reduce its in_degree
							--c.in_degree[neighbor];

							// update outdegree
							c.out_degree[neighbor].insert(make_pair(new_cluster, 1));
						}
						else
						{
							--c.in_degree[neighbor];
							++out_degree_it_2;
						}
					}
				}
			}
		}
	}
}

// add adjacent vertex with highest degree to potential clique, if possible
int choose_next(int& cur_vertex, Graph& g, Community& c, int& prev_vertex, vector<int>& potential_clique)
{
	int next_vertex = -1;
	int max_degree = 0;
	for(int i = 0; i < g.vertex[cur_vertex].degree; i++)
	{
		int neighbor = g.vertex[cur_vertex].neighbors[i];

		/*
		 * if the node is a neighbor from the previous level
		 * or if the node in consideration is already included in the
		 * current clique to be considered, ignore
		 */
		if((prev_vertex == neighbor) || (std::find(potential_clique.begin(), potential_clique.end(), neighbor) != potential_clique.end()))
		{
			continue;
		}

		// if the neighbor is in a different cluster, ignore
		if(c.n2c[neighbor] != c.n2c[cur_vertex])
		{
			continue;
		}

		if(g.vertex[neighbor].degree > max_degree)
		{
			next_vertex = neighbor;
			max_degree = g.vertex[neighbor].degree;
		}
	}
	return next_vertex;
}

void build_clique(vector<int>& potential_clique, Graph& g, Community& c, int& cur_vertex)
{
	// add starting vertex to potential clique
	potential_clique.push_back(cur_vertex);
	int prev_vertex = -1;
	while(1)
	{
		int next_vert = choose_next(cur_vertex, g, c, prev_vertex, potential_clique);
		if(next_vert == -1) // no vertices to choose from, exit
		{
			return;
		}
		else
		{
			potential_clique.push_back(next_vert);
			prev_vertex = cur_vertex;
			cur_vertex = next_vert;
		}
		if(potential_clique.size() == 4)
		{
			bool is_clique = check_connectivity(potential_clique, g);
			if(is_clique)
			{
				found = true;
				return;
			}
			else
			{
				return;
			}
		}
	}
}

// checks if potential clique is a clique
bool check_connectivity(vector<int>& potential_clique, Graph& g)
{
	bool is_clique = true;
	std::sort(potential_clique.begin(), potential_clique.end());
	for(auto it = potential_clique.begin(); it != potential_clique.end(); ++it)
	{
		vector<int> intersection(g.vertex[*it].degree);
		vector<int>::iterator inter_it = set_intersection(potential_clique.begin(),
									potential_clique.end(),
									g.vertex[*it].neighbors,
									g.vertex[*it].neighbors + g.vertex[*it].degree,
									intersection.begin());
		intersection.resize(inter_it - intersection.begin());
		if(intersection.size() != 3)
		{
			is_clique = false;
			break;
		}
		//intersection.clear();
	}
	return is_clique;
}

void finalize(WeightedGraph& wg, Community& c)
{
	//for each vertex in wg
	for(int i = 0; i < wg.num_vertices; i++)
	{
		if(wg.vertex[i].origNodes.size() == 0 || wg.vertex[i].id == -1)
			continue;

		else if(wg.vertex[i].origNodes.size() == 1)
		{
			int max_out_degree = 0, cluster;

			for(unsigned int j = 0; j < wg.vertex[i].neighbors.size(); ++j)
			{
				int neighbor = wg.vertex[i].neighbors[j];
				if(wg.vertex[neighbor].id == -1)
				{
					continue;
				}
				pair<int, int> edge;
				if(i < neighbor)
				{
					edge = make_pair(i, neighbor);
				}
				else
				{
					edge = make_pair(neighbor, i);
				}
				auto it = wg.edges.cross_edges.find(edge);
				if(it->second > max_out_degree)
				{
					max_out_degree = it->second;
					cluster = neighbor;
				}
			}

			if(wg.vertex[i].origNodes.size() >= wg.vertex[cluster].origNodes.size())
			{
				for(unsigned int k = 0; k < wg.vertex[cluster].origNodes.size(); k++)
				{
					c.n2c[wg.vertex[cluster].origNodes[k]] = i;
				}
				wg.vertex[cluster].id = -1;
			}
			else
			{
				for(unsigned int k = 0; k < wg.vertex[i].origNodes.size(); k++)
				{
					c.n2c[wg.vertex[i].origNodes[k]] = cluster;
				}
				wg.vertex[i].id = -1;
			}

		}
		// if it has 3 vertices but is not a clique
		else if((wg.vertex[i].origNodes.size() == 3) && (wg.vertex[i].in_links == 2))
		{
			int max_out_degree = 0, cluster;

			for(unsigned int j = 0; j < wg.vertex[i].neighbors.size(); ++j)
			{
				int neighbor = wg.vertex[i].neighbors[j];
				if(wg.vertex[neighbor].id == -1)
				{
					continue;
				}
				pair<int, int> edge;
				if(i < neighbor)
				{
					edge = make_pair(i, neighbor);
				}
				else
				{
					edge = make_pair(neighbor, i);
				}
				auto it = wg.edges.cross_edges.find(edge);
				if(it->second > max_out_degree)
				{
					max_out_degree = it->second;
					cluster = neighbor;
				}
			}

			if(wg.vertex[i].origNodes.size() >= wg.vertex[cluster].origNodes.size())
			{
				for(unsigned int k = 0; k < wg.vertex[cluster].origNodes.size(); k++)
				{
					c.n2c[wg.vertex[cluster].origNodes[k]] = i;
				}
				wg.vertex[cluster].id = -1;
			}
			else
			{
				for(unsigned int k = 0; k < wg.vertex[i].origNodes.size(); k++)
				{
					c.n2c[wg.vertex[i].origNodes[k]] = cluster;
				}
				wg.vertex[i].id = -1;
			}
		}

		else if(wg.vertex[i].origNodes.size() == 2)
		{
			int max_out_degree = 0, cluster, smallest_cluster = 999999;

			for(unsigned int j = 0; j < wg.vertex[i].neighbors.size(); ++j)
			{
				int neighbor = wg.vertex[i].neighbors[j];
				if(wg.vertex[neighbor].origNodes.size() < smallest_cluster)
				{
					smallest_cluster = neighbor;
				}
				if(wg.vertex[neighbor].id == -1)
				{
					continue;
				}
				pair<int, int> edge;
				if(i < neighbor)
				{
					edge = make_pair(i, neighbor);
				}
				else
				{
					edge = make_pair(neighbor, i);
				}
				auto it = wg.edges.cross_edges.find(edge);
				if(it->second > max_out_degree)
				{
					max_out_degree = it->second;
					cluster = neighbor;
				}
			}
			// if the outdegree is only 1 to multiple clusters, choose the one with smaller size
			if((max_out_degree == 1) && wg.vertex[i].neighbors.size() > 1)
			{
				if(wg.vertex[i].origNodes.size() >= wg.vertex[smallest_cluster].origNodes.size())
				{
					for(unsigned int k = 0; k < wg.vertex[smallest_cluster].origNodes.size(); k++)
					{
						c.n2c[wg.vertex[smallest_cluster].origNodes[k]] = i;
					}
					wg.vertex[smallest_cluster].id = -1;
				}
				else
				{
					for(unsigned int k = 0; k < wg.vertex[i].origNodes.size(); k++)
					{
						c.n2c[wg.vertex[i].origNodes[k]] = smallest_cluster;
					}
					wg.vertex[i].id = -1;
				}
			}
			else
			{
				if(wg.vertex[i].origNodes.size() >= wg.vertex[cluster].origNodes.size())
				{
					for(unsigned int k = 0; k < wg.vertex[cluster].origNodes.size(); k++)
					{
						c.n2c[wg.vertex[cluster].origNodes[k]] = i;
					}
					wg.vertex[cluster].id = -1;
				}
				else
				{
					for(unsigned int k = 0; k < wg.vertex[i].origNodes.size(); k++)
					{
						c.n2c[wg.vertex[i].origNodes[k]] = cluster;
					}
					wg.vertex[i].id = -1;
				}
			}
		}

	}
}

void calcNeighborhoodSize(Graph* graph)
{
	for(int i=0; i < graph->num_vertices; i++)
	{
		graph->vertex[i].common = new int[graph->vertex[i].degree]();

		for(int j=0; j < graph->vertex[i].degree; j++)
		{
			int neighbor = graph->vertex[i].neighbors[j];
			if(graph->vertex[neighbor].degree == 0)
			{
				continue;
			}
			vector<int> intersection(graph->vertex[i].degree);
			vector<int>::iterator it;
			it = set_intersection(graph->vertex[i].neighbors,
								  graph->vertex[i].neighbors + graph->vertex[i].degree,
								  graph->vertex[neighbor].neighbors,
								  graph->vertex[neighbor].neighbors + graph->vertex[neighbor].degree,
								  intersection.begin());
			intersection.resize(it - intersection.begin());
			graph->vertex[i].common[j] = intersection.size();
			intersection.clear();
		}
	}
}
