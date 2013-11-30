/*
 * driver.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: muddy
 */

#include "community.h"
#include "graph.h"
#include "tabulist.h"
#include "ant.h"
#include "helper.h"


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

int maxSteps;
int updatePeriod;
double eta = 0.5;
double maxPhm = 10000.0;
double minPhm = 1;

void calcNeighborhoodSize(Graph*);

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
int chooseNext(Ant * ant, Graph * g, Helper &helper)
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
	//Generate a random number uniformly distributed in the range [0,sum)

	//std::uniform_real_distribution<> dis(0, sum);
	double decision = helper.randomNumber();

	//Choose the next vertex for the ant
	int vertex; //result
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
void updatePheromone(Graph * g)
{
	for(auto edge_it = g->edges.begin(); edge_it != g->edges.end(); edge_it++)
	{
		edge_it->second.phm = (1.0 - eta) * edge_it->second.phm + edge_it->second.nVisited * edge_it->second.initPhm;
		if(edge_it->second.phm < 1)
			edge_it->second.phm = 1;
		edge_it->second.nVisited = 0;
	}
}

/*Function which moves all
 * the ants on the graph
 * in parallel.
 */

void antsMove(Ant * ants, Graph * g, Helper &helper)
{
	bool moved;
	typename unordered_map<pair<int, int>, Edge>::iterator edge_it;
	pair<int, int> edge;

	for(int j=1; j <= maxSteps; j++)
	{
		{
			updatePheromone(g);
		}
		//for all ants update their positions if possible
		for(int i=0; i < g->num_vertices; i++)
		{
			int cur_vertex = ants[i].location.id;
			ants[i].tabulist.addToList(cur_vertex);
			int numTries = 0;
			moved = false;
			while(numTries < 5 && !moved)
			{
				int next_vertex = chooseNext(&ants[i], g, helper);

				//if the next vertex if not in the tabulist, then move the ant and add this
				//vertex to the tabulist

				if(ants[i].tabulist.searchList(next_vertex) == false)// || ants[i].location.degree <= 2  )
				{
					//ants[i].tabulist.addToList(next_vertex);
					ants[i].location = g->vertex[next_vertex];
					/*
					 * Just a test
					 */
					/*if(ants[i].location.degree == 1)
					{
						ants[i].tabulist.clearList();
					}*/
					//ants[i].tabulist.addToList(next_vertex);
					moved = true;
					if(cur_vertex < next_vertex)
					{
						edge = make_pair(cur_vertex, next_vertex);
						edge_it = g->edges.find(edge);
						edge_it->second.nVisited++;
					}
					else
					{
						edge = make_pair(next_vertex, cur_vertex);
						edge_it = g->edges.find(edge);
						edge_it->second.nVisited++;
					}
				}
				else
					numTries++;
			}
		}
	}
}

int main(int argc, char **argv)
{
	cout<<"Argument is: "<<argv[1]<<"\n\n";

	clock_t start; //calculates time for iteration

	start = clock();

	if(argc != 2)
	{
		cout << "Invalid parameters! \n";
		return 0;
	}

	//read in the graph, given as a command line parameter
	Graph g(argv[1]);

	cout<<"Time for reading graph = "<<(clock() - start)/ (double)(CLOCKS_PER_SEC/1000)<<" ms \n\n";

	start = clock();

	cout<<"Finalizing 1-hop neighborhood...\n\n";

	//sort the adjacent nodes for each vertex to compute intersection easily
	for(int i=0; i<g.num_vertices; i++)
		sort(g.vertex[i].neighbors, g.vertex[i].neighbors+g.vertex[i].degree);

	//calculate the intersection size of each node with its neighbor
	calcNeighborhoodSize(&g);

	cout<<"Completed...\n\n";

	cout<<"Time for finalizing neighborhood = "<<(clock() - start)/ (double)(CLOCKS_PER_SEC/1000)<<" ms \n\n";

	//create the ants and place them on the graph
	Ant * ants = new Ant[g.num_vertices];
	for(int i = 0; i < g.num_vertices; i++)
	{
		ants[i].location = g.vertex[i];
	}

	cout<<"The total number of edges is = "<<g.num_edges<<"\n\n";

	cout<<"The number of vertices is = "<<g.num_vertices<<"\n\n";

	if(g.num_vertices > 113)
	{
		maxSteps = 75;
		updatePeriod = maxSteps / 3;
	}
	else
	{
		maxSteps = (int) ((2.0/3.0) * g.num_vertices);
		updatePeriod = maxSteps / 3;
	}

	Helper helper(g);

	start = clock();

	//exploration of the graph is done by the ants
	for(int i = 0; i < 100; i++)
	{
		antsMove(ants, &g, helper);
		resetAnts(ants, &g, helper);
		eta = eta * 0.95;
		if (eta < 0.02)
		{
			eta = 0.02;
		}
	}

	cout<<"Time for function antsMove = "<<(clock() - start)/ (double)(CLOCKS_PER_SEC/1000)<<" ms \n\n";

	std::vector<Edge> finalEdges;

	for(auto it = g.edges.begin(); it != g.edges.end(); it++)
	{
		finalEdges.push_back(it->second);
	}

	std::sort(finalEdges.begin(), finalEdges.end(), greater_than_key());

	/*for(auto it = finalEdges.begin(); it != finalEdges.end(); it++)
	{
		int a = it->v1;
		int b = it->v2;
		cout << "(" << ++a << "," << ++b << ")" << setw(10) << "	:	" << setw(5) << it->phm << "\n";
	}*/
	delete[] ants; //remove the ants
	cout << "\n";

	Community c(g);
	WeightedGraph wg = c.partition_one_level(g, finalEdges);

	//wg.displayGraph();
	wg.calc_edge_total();

	std::vector<pair<pair<int, int>, double > > fracEdges;

	//fracEdges.resize(wg.edgeTotal.size());

	for(auto it = wg.edgeTotal.begin(); it != wg.edgeTotal.end(); it++)
	{
		pair<int, int> edge = it->first;
		double frac = it->second;
		pair<pair<int, int>, double > frac_edge(edge, frac);
		fracEdges.push_back(frac_edge);
	}

	std::sort(fracEdges.begin(), fracEdges.end(), greater_than_key_2());



	cout << "Graph Modularity = " << wg.modularity(g) << "\n\n";

	/*for(auto it = fracEdges.begin(); it != fracEdges.end(); it++)
	{
		cout << "(" << it->first.first << ", " << it->first.second << ") - " <<it->second << "\n";
	}*/

	wg.mergeClusters(fracEdges);

	cout <<"\n\n";

	wg.displayGraph();

	cout << wg.modularity(g) << "\n\n";


	return 0;
}

void calcNeighborhoodSize(Graph * graph)
{
	for(int i=0; i < graph->num_vertices; i++)
	{
		graph->vertex[i].common = new int[graph->vertex[i].degree];
		for(int j=0; j < graph->vertex[i].degree; j++)
		{
			int neighbor = graph->vertex[i].neighbors[j];
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
