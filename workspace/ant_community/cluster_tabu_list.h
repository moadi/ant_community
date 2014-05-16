#ifndef CLUSTER_TABU_LIST_H_
#define CLUSTER_TABU_LIST_H_

#include <iostream>

class ClusterTabuList
{
	private:
		int * cluster_id;
		int head;

	public:
		static const int LIST_SIZE = 2;
		ClusterTabuList();
		void addToList(int);
		bool searchList(int);
		void displayList();
		void clearList();
		~ClusterTabuList();
};


#endif /* CLUSTER_TABU_LIST_H_ */
