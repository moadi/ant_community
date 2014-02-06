/*
 * graph.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: muddy
 */

#include "graph.h"

using namespace std;

int edge_counter;

/*
 * Function to reset the file pointer to the beginning of GML file
 * Takes as a parameter a reference to the file pointer, clears the
 * flags and sets the pointer to the beginning.
 */
void reset_pointer(ifstream &fin)
{
	fin.clear();
	fin.seekg(0, fin.beg);
}


/*
 * Function to count the number of vertices in GML file.
 * Scans the file for "node" entries and updates the counter.
 * Returns the number of vertices.
 */
int count_vertices(ifstream &fin) {
	string line;
	int result = 0;
	while (!fin.eof())
	{
		getline(fin, line);
		if (string::npos != line.find("node"))
			result++;
		if (string::npos != line.find("edge"))
			break;
	}
	reset_pointer(fin);
	return result;
}

/*
 * Count vertices in Pajek file
 */
int count_vertices_pajek(ifstream& fin)
{
	string line;
	char * ptr;
	int result;
	getline(fin, line);
	if(string::npos != line.find("Vertices"))
	{
		ptr = new char[line.size() + 1];
		ptr[line.size()] = '\0';
		memcpy(ptr, line.c_str(), line.size());
		ptr = strstr(ptr, "Vertices");
		sscanf(ptr, "Vertices %d", &result);
	}
	return result;
}

Graph::Graph(char * fileName)
{
	ifstream fin(fileName);
	if(!fin)
	{
		cerr << "Invalid file name! \n";
		exit(EXIT_FAILURE);
	}
	string file(fileName);
	if (string::npos != file.find(".net"))
	{
		string line;
		num_vertices = count_vertices_pajek(fin);
		vertex = new Vertex[num_vertices];
		for(int i = 0; i < num_vertices; i++)
		{
			vertex[i].id = i;
			vertex[i].degree = 0;
		}
		//Read vertex IDs
		do
		{
			getline(fin, line);
			string id_text;
			if(string::npos != line.find("Edges"))
				break;
			/*int start_pos = line.find("\"");
			int id;
			if (string::npos != start_pos)
			{
				++start_pos;
				int i;
				for(i = start_pos; line[i] != '\"'; i++);
				id_text = line.substr(start_pos, i - start_pos);
				id = atoi(id_text.c_str());
				id--;
				vertex[id].id = id;
				vertex[id].degree = 0;
			}*/
		}
		while(!fin.eof());



		int source, target;

		//Calculate the degree of each vertex
		while(fin >> source >> target)
		{
			vertex[--source].degree++;
			vertex[--target].degree++;
		}

		//Calculate the number of edges to resize the map
		int tot_deg = 0;
		for(int i = 0;i < num_vertices; i++)
		{
			tot_deg += vertex[i].degree;
		}
		num_edges = tot_deg/2;

		edges.reserve(num_edges);

		reset_pointer(fin);

		//Loop till we reach the edges entry again
		while(!fin.eof())
		{
			getline(fin, line);
			if (string::npos != line.find("Edges"))
				break;
		}

		//Initialize the neighbors
		for(int i = 0; i < num_vertices; i++)
		{
			vertex[i].neighbors = new int[vertex[i].degree];
		}
		int * count = new int[num_vertices]();
		while (fin >> source >> target)
		{
			source--;
			target--;
			pair<int, int> edge_key;
			Edge edge;
			if(source < target)
			{
				edge.v1 = source;
				edge.v2 = target;
				edge_key = make_pair(source, target);
			}
			else
			{
				edge.v1 = target;
				edge.v2 = source;
				edge_key = make_pair(target, source);
			}
			edges.insert(make_pair(edge_key, edge));
			vertex[source].neighbors[count[source]] = target;
			vertex[target].neighbors[count[target]] = source;
			count[source]++;
			count[target]++;
		}
		delete[] count;
		count = NULL;
		fin.close();
	}
	else
	{
		cout<<"Calculating number of vertices... \n";
		num_vertices = count_vertices(fin); //count all vertices
		cout<<"Done \n";

		vertex = new Vertex[num_vertices]; //create array of vertices

		//Get all vertex IDs
		string line;
		char * ptr;
		int id;
		for(int i=0; i < num_vertices; i++)
		{
			vertex[i].degree = 0;
			do
			{
				getline(fin, line);
			}
			while(!(string::npos != line.find("node")));

			do
			{
				getline(fin, line);
				if (string::npos != line.find("id")) {
				ptr = new char[line.size()+1];
				ptr[line.size()]='\0';
				memcpy(ptr, line.c_str(), line.size());
				ptr = strstr(ptr, "id");
				if(strcmp(fileName, "karate.gml") == 0)
				{
					sscanf(ptr, "id %d", &id);
					id--;
					vertex[i].id = id;
				}
				else
					sscanf(ptr, "id %d", &vertex[i].id);
			}
			if (string::npos != line.find("]"))
				break;
			}
			while(!fin.eof());
		}

		//Get the degree of each vertex
		int source, target;
		while (!fin.eof())
		{
			getline(fin, line);
			if (!(string::npos != line.find("edge")))
				continue;

			source = target = -1;
			do
			{
				getline(fin, line);
				if(string::npos != line.find("source"))
				{
					ptr = new char[line.size()+1];
					ptr[line.size()]='\0';
					memcpy(ptr, line.c_str(), line.size());
					ptr = strstr(ptr, "source");
					sscanf(ptr, "source %i", &source);
				}
				if(string::npos != line.find("target"))
				{
					ptr = new char[line.size()+1];
					ptr[line.size()]='\0';
					memcpy(ptr, line.c_str(), line.size());
					ptr = strstr(ptr, "target");
					sscanf(ptr, "target %i", &target);
				}
				if(string::npos != line.find("]"))
					break;
			}
			while(!fin.eof());

			if(source>=0 && target>=0)
			{
				if(strcmp(fileName, "karate.gml") == 0)
				{
					vertex[--source].degree++;
					vertex[--target].degree++;
				}
				else
				{
					vertex[source].degree++;
					vertex[target].degree++;
				}
			}
		}

		//Calculate the number of edges to resize the map
		int tot_deg = 0;
		for(int i = 0;i < num_vertices; i++)
		{
			tot_deg += vertex[i].degree;
		}
		num_edges = tot_deg/2;

		edges.reserve(num_edges);

		//Read in the edges
		reset_pointer(fin);
		int * count;
		for(int i=0; i < num_vertices; i++)
		{
			vertex[i].neighbors = new int[vertex[i].degree];
		}

		count = new int[num_vertices](); //zero-initialize temporary edge counts
		while(!fin.eof())
		{
			getline(fin, line);
			if (!(string::npos != line.find("edge"))) //loop till edge entry
					continue;

			source = target = -1;
			do
			{
				getline(fin, line);
				if(string::npos != line.find("source"))
				{
					//grab the source
					ptr = new char[line.size()+1];
					ptr[line.size()]='\0';
					memcpy(ptr, line.c_str(), line.size());
					ptr = strstr(ptr, "source");
					sscanf(ptr, "source %i", &source);
				}
				if(string::npos != line.find("target"))
				{
					//grab the target
					ptr = new char[line.size()+1];
					ptr[line.size()]='\0';
					memcpy(ptr, line.c_str(), line.size());
					ptr = strstr(ptr, "target");
					sscanf(ptr, "target %i", &target);
				}
				if(string::npos != line.find("]")) //break if "]" is found
					break;
			}
			while(!fin.eof());
			if (source>=0 && target>=0)
			{
				if(strcmp(fileName, "karate.gml") == 0)
				{
					target--;
					source--;
				}
				vertex[source].neighbors[count[source]] = target;
				vertex[target].neighbors[count[target]] = source;

				//update counts
				count[source]++;
				count[target]++;

				if(source < target)
				{
					pair<int, int> key;
					key = make_pair(source, target);
					Edge edge;
					edge.v1 = source;
					edge.v2 = target;
					edges.insert(make_pair(key, edge));
					//edges[key] = edge;
				}
				else
				{
					pair<int, int> key;
					key = make_pair(target, source);
					Edge edge;
					edge.v1 = target;
					edge.v2 = source;
					edges.insert(make_pair(key, edge));
					//edges[key] = edge;
				}
			}
		}
		delete[] count; //delete count to free up space
		fin.close();
	}
}

/*Graph::~Graph()
{
	delete[] vertex;
}*/

/*Vertex::~Vertex()
{
	delete[] neighbors;
	delete[] common;
}*/

void Graph::displayCount()
{
	int total_degree = 0;
	cout<<"The number of vertices in this graph is = "<<num_vertices<<"\n";
	for(int i=0; i < num_vertices; i++)
	{
		total_degree+=vertex[i].degree;
	}
	cout<<"The number of edges in this graph is = "<<total_degree/2<<"\n";
}

Edge::Edge()
{
	initPhm = 1.0;
	phm = 1.0;
	nVisited = 0;
}
