#ifndef _BinaryTree_H_
#define _BinaryTree_H_

#include <vector>
#include "BinaryNode.h"
#include "BinaryTree.h"




template<class AthleteType>
class BinaryTree
{
private:
	void destroyTree(BinaryNode<AthleteType>* nodePtr);
	BinaryNode<AthleteType>* _copyTree(const BinaryNode<AthleteType>* nodePtr, vector <AthleteType> &arr, AthleteType visit(AthleteType));
	void _preorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const;
	void _inorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const;
	void _postorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const;
	void _postorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent = 0) const;
	void _preorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent = 0) const;
	void _inorderprint(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr, int indent = 0) const;
	void _RNLorder(void visit(AthleteType &), BinaryNode<AthleteType>* nodePtr) const;
	void _RNLorder(void visit(AthleteType &, int), BinaryNode<AthleteType>* nodePtr, int & width) const;
	void _breadthtraversal(void visit(AthleteType &), BinaryNode<AthleteType>*nodePtr) const;
protected:
	BinaryNode<AthleteType>* root;
	int count;
public:
	BinaryTree()
	{
		root = 0;
		count = 0;
	}
	BinaryTree(const BinaryTree<AthleteType> & tree, AthleteType visit(AthleteType))
	{
		root = _copyTree(tree.root, visit);
		count = tree.count;
	}
	virtual ~BinaryTree() { clear(); }
	BinaryTree & operator=(const BinaryTree & sourceTree);
	bool isEmpty() const				{ return count == 0; }
	int size() const					{ return count; }
	void clear(); 
	void preOrder(void visit(AthleteType &)) const							{ _preorder(visit, root); }
	void inOrder(void visit(AthleteType &)) const							{ _inorder(visit, root); }
	void postOrder(void visit(AthleteType &)) const						    { _postorder(visit, root); }
	void postOrderPrint(void visit(AthleteType&)) const                     { _postorderprint(visit, root, 0); }
	void preOrderPrint(void visit(AthleteType&)) const                     { _preorderprint(visit, root, 0); }
	void inOrderPrint(void visit(AthleteType&)) const                     { _inorderprint(visit, root, 0); }
	void breadthTraversal(void visit(AthleteType &)) const                     { _breadthtraversal(visit, root); }
	void RNLOrder(void visit(AthleteType &)) const							{ _RNLorder(visit, root); }
	void RNLOrder(void visit(AthleteType &, int), int & width) const		{ _RNLorder(visit, root, width); }
	void deleteBackup()
	{
		root = 0;
		count = 0;
	}
	void copyTree(const BinaryTree<AthleteType> & copyItem, vector <AthleteType> &arr,
		AthleteType visit(AthleteType))
	{
		clear(); root = _copyTree(copyItem.root, arr, visit);
		count = copyItem.count;
	}
	virtual bool insert(AthleteType & newData, bool visit(AthleteType, AthleteType, string)) = 0;
	virtual bool remove(const AthleteType & data, bool visit(AthleteType, AthleteType, string)) = 0;
	virtual bool getEntry(const AthleteType & anEntry, AthleteType & returnedItem, bool visit(AthleteType, AthleteType, string)) const = 0;
};

#endif _BinaryTree_H_