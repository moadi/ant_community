#include "cluster_tabu_list.h"

ClusterTabuList::ClusterTabuList()
{
	cluster_id = new int[LIST_SIZE];
	for(int i = 0; i < LIST_SIZE; i++)
		cluster_id[i] = -1;
	head = 0;
}

void ClusterTabuList::addToList(int id)
{
	cluster_id[head] = id;
	head = (head+1)%(LIST_SIZE);
}

bool ClusterTabuList::searchList(int id)
{
	for (int i=0; i < LIST_SIZE; i++)
	{
		if(cluster_id[i] == id)
		{
			return true;
		}
	}
	return false;
}

void ClusterTabuList::displayList()
{
	for(int i=0; i < LIST_SIZE; i++)
		std::cout << "List item at position " << i << " = " << cluster_id[i]<<"\n";
	std::cout<<"\n";
}

void ClusterTabuList::clearList()
{
	for(int i=0; i < LIST_SIZE; i++)
		cluster_id[i] = -1;
	head = 0;
}

ClusterTabuList::~ClusterTabuList()
{
	delete[] cluster_id;
}
