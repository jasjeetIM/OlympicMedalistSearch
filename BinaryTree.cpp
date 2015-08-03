#include "stdafx.h"
#include "BinaryTree.h";

template<class AthleteType>
BinaryNode<AthleteType>* BinaryTree<AthleteType>::_copyTree(const BinaryNode<AthleteType>* nodePtr, vector <AthleteType> &arr, AthleteType visit(AthleteType))
{
	BinaryNode<AthleteType>* newNodePtr = 0;

	if (nodePtr != 0)
	{
		AthleteType tempCopy = visit(nodePtr->getItem());
		arr.push_back(tempCopy);
		newNodePtr = new BinaryNode<AthleteType>(tempCopy);
		newNodePtr->setLeftPtr(_copyTree(nodePtr->getLeftPtr(), arr, visit));
		newNodePtr->setRightPtr(_copyTree(nodePtr->getRightPtr(), arr, visit));
	}

	return newNodePtr;
}

template<class AthleteType>
void BinaryTree<AthleteType>::destroyTree(BinaryNode<AthleteType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;

	}
}

template<class AthleteType>
void BinaryTree<AthleteType>::_preorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		AthleteType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class AthleteType>
void BinaryTree<AthleteType>::_inorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		AthleteType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class AthleteType>
void BinaryTree<AthleteType>::_postorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		AthleteType item = nodePtr->getItem();
		visit(item);
	}
}



template<class AthleteType>
void BinaryTree<AthleteType>::_breadthtraversal(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const
{
	ofstream out;
	out.open("Output.txt");


	queue<BinaryNode<AthleteType>*> q;
	q.push(nodePtr);

	BinaryNode <AthleteType>* tmp = q.front();


	while (!q.empty())
	{

		tmp = q.front();
		q.pop();

		Athlete * item = tmp->getIte();
		out << item->getName() << "," << item->getAge() << "," << item->getCountry() << "," << item->getYear() << endl;

		if (tmp->getLeftPtr() != NULL)
			q.push(tmp->getLeftPtr()); 

		if (tmp->getRightPtr() != NULL)
			q.push(tmp->getRightPtr());

	}
	out.close();
}



template<class AthleteType>
void BinaryTree<AthleteType>::_postorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent) const
{
	if (nodePtr != 0)
	{



		_postorderprint(visit, nodePtr->getLeftPtr(), indent + 2);


		_postorderprint(visit, nodePtr->getRightPtr(), indent + 2);

		if (indent) cout << std::setw(indent) << ' ';

		if (nodePtr->getRightPtr() != 0) cout << " /\n" << setw(indent) << ' ';

		AthleteType item = nodePtr->getItem();
		visit(item);

		if (nodePtr->getLeftPtr() != 0) cout << std::setw(indent) << ' ' << " \\\n";

	}
}


template<class AthleteType>
void BinaryTree<AthleteType>::_preorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent) const
{
	if (nodePtr != 0)
	{
		if (indent) cout << std::setw(indent) << ' ';

		if (nodePtr->getRightPtr() != 0) cout << " /\n" << setw(indent) << ' ';

		AthleteType item = nodePtr->getItem();
		visit(item);

		if (nodePtr->getLeftPtr() != 0) cout << std::setw(indent) << ' ' << " \\\n";

		_preorderprint(visit, nodePtr->getLeftPtr(), indent + 2);
		_preorderprint(visit, nodePtr->getRightPtr(), indent + 2);


	}
}

template<class AthleteType>
void BinaryTree<AthleteType>::_inorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent) const
{
	if (nodePtr != 0)
	{

		_inorderprint(visit, nodePtr->getLeftPtr(), indent + 2);
		if (indent) cout << std::setw(indent) << ' ';

		if (nodePtr->getRightPtr() != 0) cout << " /\n" << setw(indent) << ' ';

		AthleteType item = nodePtr->getItem();
		visit(item);

		if (nodePtr->getLeftPtr() != 0)
		{
			cout << std::setw(indent) << ' ' << " \\\n";
			_inorderprint(visit, nodePtr->getRightPtr(), indent + 2);
		}

	}
}








template <class AthleteType>
void BinaryTree<AthleteType>::_RNLorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const	// For reverse alphabetical order.
{
	if (nodePtr != 0)
	{
		_RNLorder(visit, nodePtr->getRightPtr());
		AthleteType item = nodePtr->getItem();
		visit(item);
		_RNLorder(visit, nodePtr->getLeftPtr());
	}
}

template <class AthleteType>
void BinaryTree<AthleteType>::_RNLorder(void visit(AthleteType &, int), BinaryNode<AthleteType>* nodePtr, int & width) const
{
	if (nodePtr != 0)
	{
		width += 4;
		_RNLorder(visit, nodePtr->getRightPtr(), width);
		AthleteType item = nodePtr->getItem();
		visit(item, width);
		_RNLorder(visit, nodePtr->getLeftPtr(), width);
		width -= 4;
	}
}

template <class AthleteType>
BinaryTree<AthleteType> & BinaryTree<AthleteType>::operator=(const BinaryTree<AthleteType> & sourceTree)
{
	clear();
	root = sourceTree.root;
	count = sourceTree.count;

	return *this;
}
template <class AthleteType>
void BinaryTree<AthleteType>:: clear() { destroyTree(root); root = 0; count = 0; }