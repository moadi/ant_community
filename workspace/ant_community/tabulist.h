/*
 * tabulist.h
 *
 *  Created on: Jun 25, 2013
 *      Author: muddy
 */

#include <iostream>

#define LIST_SIZE 2

#ifndef TABULIST_H_
#define TABULIST_H_

class TabuList
{
	private:
		int * vertex_id;
		int head;

	public:
		TabuList();
		void addToList(int);
		bool searchList(int);
		void displayList();
		void clearList();
		//~TabuList();
};

#endif /* TABULIST_H_ */
