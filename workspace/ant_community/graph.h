#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <cstring>
#include <utility>
#include <string>
#include <vector>

using namespace std;


/*
 * Specialize std::hash for pair so we can use it as a key
 * in the hashtable
 */
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
  template<typename S, typename T> struct hash<pair<S, T>>
  {
    inline size_t operator()(const pair<S, T> & v) const
    {
      size_t seed = 0;
      ::hash_combine(seed, v.first);
      ::hash_combine(seed, v.second);
      return seed;
    }
  };
}

class Edge
{
	public:
		Edge();
		int v1;
		int v2;  //the two end points
		double phm; //pheromone value for the edge
		double initPhm; //initial pheromone value of the edge
		int nVisited; //number of times this edge has been visited by ants
};

class Vertex
{
	public:
		int id; //id of vertex from GML file
		int degree; //degree of each vertex
		int * neighbors; //set of 1-hop neighbors of this vertex
		int * common; //intersection size with each neighbor of this vertex

		//~Vertex(); //destructor for the vertex
};

class Graph
{
	public:
		int num_vertices; //total number of vertices in the graph
		int num_edges; //total number of edges in the graph
		Vertex * vertex; //array of vertices
		unordered_map<pair<int, int>, Edge> edges;

		Graph(char * fileName); //constructor for the graph, takes as parameter
								//the file which contains the graph
		void displayCount();
		//~Graph(); //graph destructor
};

#endif /* GRAPH_H_ */
