#ifndef _BinarySearchTree_H_
#define _BinarySearchTree_H_

#include "BinaryNode.h"
#include "BinaryTree.h"



template<class AthleteType>
class BinarySearchTree: public BinaryTree<AthleteType>
{
private:
	BinaryNode<AthleteType> * _insert(BinaryNode<AthleteType>* nodePtr, BinaryNode<AthleteType>* newNode, bool visit(AthleteType, AthleteType, string));
	BinaryNode<AthleteType>* _remove(BinaryNode<AthleteType>* nodePtr, const AthleteType & target, bool & success,bool visit(AthleteType, AthleteType, string));
	BinaryNode<AthleteType>* deleteNode(BinaryNode<AthleteType>* targetNodePtr);
	BinaryNode<AthleteType>* removeLeftmostNode(BinaryNode<AthleteType>* nodePtr, AthleteType & successor);
	BinaryNode<AthleteType>* findNode(BinaryNode<AthleteType>* treePtr, const AthleteType & target,
	bool visit(AthleteType, AthleteType, string)) const;
public:
	bool insert(AthleteType & newEntry, bool visit(AthleteType, AthleteType, string));
	bool remove(const AthleteType & anEntry, bool visit(AthleteType, AthleteType, string));
	bool getEntry(const AthleteType & target, AthleteType & returnedItem, bool visit(AthleteType, AthleteType, string)) const;
	//BinaryNode<AthleteType> * getRoot() { return root;  }
};

#endif _BinarySearchTree_H_