/*
 * tabulist.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: muddy
 */

#include "tabulist.h"

TabuList::TabuList()
{
	vertex_id = new int[LIST_SIZE];
	for(int i = 0; i < LIST_SIZE; i++)
		vertex_id[i] = -1;
	head = 0;
}

void TabuList::addToList(int id)
{
	vertex_id[head] = id;
	head = (head+1)%(LIST_SIZE);
}

bool TabuList::searchList(int id)
{
	for (int i=0; i < LIST_SIZE; i++)
	{
		if(vertex_id[i] == id)
		{
			return true;
		}
	}
	return false;
}

void TabuList::displayList()
{
	for(int i=0; i < LIST_SIZE; i++)
		std::cout << "List item at position " << i << " = " << vertex_id[i]<<"\n";
	std::cout<<"\n";
}

void TabuList::clearList()
{
	for(int i=0; i < LIST_SIZE; i++)
		vertex_id[i] = -1;
	head = 0;
}

TabuList::~TabuList()
{
	delete[] vertex_id;
}
