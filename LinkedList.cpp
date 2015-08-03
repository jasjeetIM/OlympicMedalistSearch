#include "stdafx.h"
#include "LinkedList.h"
using namespace std; 

template <class T>
void LinkedList<T>::displayList(void visit(T)) const
{
	Node<T> *nodePtr = headPtr;
	while (nodePtr != 0)
	{
		visit(nodePtr->getItem());
		nodePtr = nodePtr->getNext();
	}
	cout << endl;
}

template <class T>
void LinkedList<T>::insertNode(T nodePtr)
{
	Node<T> *newNode;
	Node<T> *previousLocation;
	Node<T> *previousPtr = NULL;

	newNode = new Node<T>(); // create new node
	newNode->data = nodePtr;
	newNode->next = 0;

	if (headPtr == 0)
	{
		headPtr = newNode;
	}
	else
	{

		previousLocation = headPtr;
		previousPtr = 0;

		while (previousLocation != 0 && previousLocation->data < nodePtr)
		{
			previousPtr = previousLocation;
			previousLocation = previousLocation->next;
		}

		if (previousPtr == 0)
		{
			headPtr = newNode;
			newNode->next = previousLocation;
		}

		else
		{
			previousPtr->next = newNode;
			newNode->next = previousLocation;
		}
	}
	itemCount++; // increment the count
}

template <class T>
bool LinkedList<T>::deleteNode(T nodePtr)
{
	Node<T> *previousLocation;
	Node<T> *previousNodePtr;

	if (!headPtr)
		return false;


	previousLocation = headPtr;
	previousNodePtr = 0;
	while (previousLocation != 0 && previousLocation->data < nodePtr)
	{
		previousNodePtr = previousLocation;
		previousLocation = previousLocation->next;
	}

	if (previousLocation != 0 && previousLocation->data == nodePtr)
	{
		itemCount--;
		if (previousNodePtr)
			previousNodePtr->next = previousLocation->next;
		else
			headPtr = previousLocation->next;
		delete previousLocation;
		return true;
	}
	return false;
}