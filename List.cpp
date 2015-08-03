#include "stdafx.h"
#include "List.h"

template<class AthleteType>
bool List<AthleteType>::insert(const AthleteType& entry, int newPosition)
{
	if (newPosition < 1 || newPosition > List::itemCount + 1)
		return false;

	Node<AthleteType>* newNodePtr = new Node<AthleteType>(entry);
	if (newPosition == 1)
	{
		newNodePtr->setNext(List::headPtr);
		List::headPtr = newNodePtr;
	}
	else
	{
		Node<AthleteType>* prevPtr = getNodeAt(newPosition - 1);
		newNodePtr->setNext(prevPtr->getNext());
		prevPtr->setNext(newNodePtr);
	}
	List::itemCount++;
	return true;
}

template<class AthleteType>
bool List<AthleteType>::remove(int position)
{
	if (position < 1 || position > List::itemCount)
		return false;

	Node<AthleteType>* deletePtr = 0;
	if (position == 1)
	{
		deletePtr = List::headPtr;
		List::headPtr = List::headPtr->getNext();
	}
	else
	{
		Node<AthleteType>* prevPtr = getNodeAt(position - 1);
		deletePtr = prevPtr->getNext();
		prevPtr->setNext(deletePtr->getNext());
	}
	delete deletePtr;
	List::itemCount--;
	return true;
}

template<class AthleteType>
bool List<AthleteType>::getEntry(int position, AthleteType & entry) const
{
	if (position < 1 || position > List::itemCount)
		return false;

	Node<AthleteType>* copyPtr = getNodeAt(position);
	entry = copyPtr->getItem();
	return true;
}


template<class AthleteType>
Node<AthleteType>* List<AthleteType>::getNodeAt(int position) const
{
	Node<AthleteType>* currentPtr = List::headPtr;
	for (int i = 1; i < position; i++)
		currentPtr = currentPtr->getNext();
	return currentPtr;
}