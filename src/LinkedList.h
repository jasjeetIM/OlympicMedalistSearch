#ifndef _LinkedList_H_
#define _LinkedList_H_

#include "Node.h"

template <class T>
class LinkedList
{
protected:

	Node<T> *headPtr;   // List head pointer
	int itemCount;

public:
	LinkedList() { headPtr = NULL; itemCount = 0; }
	~LinkedList()
	{
		Node<T> *nodePtr = headPtr;
		while (nodePtr != 0)
		{
			headPtr = headPtr->getNext();
			delete nodePtr;
			nodePtr = headPtr;
		}
	}

	// Linked list functions
	void insertNode(T); // inserts node
	bool deleteNode(T); // deleted node
	void displayList(void visit(T)) const;
};

#endif _LinkedList_H_