#include <iostream>

#ifndef TABULIST_H_
#define TABULIST_H_

class TabuList
{
	private:
		int * vertex_id;
		int head;

	public:
		static const int LIST_SIZE = 2;
		TabuList();
		void addToList(int);
		bool searchList(int);
		void displayList();
		void clearList();
		//~TabuList();
};

#endif /* TABULIST_H_ */
