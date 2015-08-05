#include "stdafx.h"
#include "BinarySearchTree.h"

template<class AthleteType>
bool BinarySearchTree<AthleteType>::insert(AthleteType & newEntry, bool visit(AthleteType, AthleteType, string))
{
	BinaryNode<AthleteType> * newNodePtr = new BinaryNode<AthleteType>(newEntry);
	BinarySearchTree::root = _insert(BinarySearchTree::root, newNodePtr, visit);
	BinarySearchTree::count++;

	return true;
}


template<class AthleteType>
bool BinarySearchTree<AthleteType>::remove(const AthleteType & target, bool visit(AthleteType, AthleteType, string))
{
	bool isSuccessful = false;
	BinarySearchTree::root = _remove(BinarySearchTree::root, target, isSuccessful, visit);
	if (isSuccessful)
	{
		BinarySearchTree::count--;
	}

	return isSuccessful;
}

template<class AthleteType>
bool BinarySearchTree<AthleteType>::getEntry(const AthleteType & anEntry, AthleteType & returnedItem, bool visit(AthleteType, AthleteType, string)) const
{
	BinaryNode<AthleteType> * tempFind;
	tempFind = findNode(BinarySearchTree::root, anEntry, visit);
	if (tempFind)
	{
		returnedItem = tempFind->getItem();
		return true;
	}

	return false;
}

template<class AthleteType>
BinaryNode<AthleteType>* BinarySearchTree<AthleteType>::_insert(BinaryNode<AthleteType>* nodePtr,
	BinaryNode<AthleteType>* newNodePtr, bool visit(AthleteType, AthleteType, string))
{
	if (nodePtr != 0)
	{
		if (visit(nodePtr->getItem(), newNodePtr->getItem(), ">"))
		{
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, visit));
		}
		else if (visit(nodePtr->getItem(), newNodePtr->getItem(), "<"))
		{
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, visit));
		}
	}
	else
	{
		return newNodePtr;
	}

	return nodePtr;
}

template<class AthleteType>
BinaryNode<AthleteType>* BinarySearchTree<AthleteType>::_remove(BinaryNode<AthleteType>* nodePtr,
	const AthleteType & target, bool & success, bool visit(AthleteType, AthleteType, string))
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}

	if (visit(nodePtr->getItem(), target, ">"))
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, visit));
	else if (visit(nodePtr->getItem(), target, "<"))
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, visit));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class AthleteType>
BinaryNode<AthleteType>* BinarySearchTree<AthleteType>::deleteNode(BinaryNode<AthleteType>* nodePtr)
{
	if (nodePtr->checkLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<AthleteType>* nodeToConnectPtr = nodePtr->getRightPtr();

		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<AthleteType>* nodeToConnectPtr = nodePtr->getLeftPtr();

		delete nodePtr;

		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		AthleteType newNodeValue = nodePtr->getItem();

		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);

		return nodePtr;
	}
}

template<class AthleteType>
BinaryNode<AthleteType>* BinarySearchTree<AthleteType>::removeLeftmostNode
(BinaryNode<AthleteType>* nodePtr, AthleteType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		AthleteType tempDelete = successor;
		successor = nodePtr->getItem();
		nodePtr->setItem(tempDelete);

		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

template<class AthleteType>
BinaryNode<AthleteType>* BinarySearchTree<AthleteType>::findNode(BinaryNode<AthleteType>* nodePtr,
	const AthleteType & target, bool visit(AthleteType, AthleteType, string)) const
{
	if (nodePtr != 0)
	{
		if (visit(nodePtr->getItem(), target, "=="))
		{
			return nodePtr;
		}
		else if (visit(nodePtr->getItem(), target, "<"))
		{
			return findNode(nodePtr->getRightPtr(), target, visit);
		}
		else
		{
			return findNode(nodePtr->getLeftPtr(), target, visit);
		}
	}
	else
	{
		return 0;
	}
}