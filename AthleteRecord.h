#ifndef _AthleteRecord_H_
#define _AthleteRecord_H_

#include "BinarySearchTree.h"
#include "HeapMostSearch.h"
#include "Athlete.h"
#include "HashedTable.h"
#include "BinaryTree.h"


class AthleteRecord
{
private:
	int count;
	BinarySearchTree<Athlete*> item;
	Athlete indentedTree;
	HashedTable *hashPtr;
	HeapMostSearch<Athlete*> heapSearch;
	int backupCount;
	BinarySearchTree<Athlete*> backupItem;
	HashedTable * backupHashPtr;
	HeapMostSearch<Athlete*> backupHeapSearch;
public:
	static Athlete * copyValue(Athlete * copyItem);
	AthleteRecord();
	~AthleteRecord() { delete hashPtr; delete backupHashPtr; }
	static void printFull(Athlete* & sample) { sample->printAll(); cout << endl; }
	static void print(Athlete * & sample) { sample->printKey(); }
	static void visit(Athlete* ptr) { cout << ptr->getName() << endl; }
	static void copy(Athlete*ptr, HashedTable* hashPtr);
	void add(string input, string age, string country, string year);	// Adds into BST and HashedTable
	void deleteData(string input);										// Delete function
	bool search(string input);											// Search function (HashedTable)
	void hashList() const { hashPtr->display(visit); cout << endl; }		// Displays the HashedTable
	void bstKey() const { item.inOrder(print); cout << endl; }			// Prints out the BST data in order
	void breadthSave() const { item.breadthTraversal(printFull); cout << "The data has been outputted using breadth first traversal of the BST. :) " << endl; }
	void postOrder() const { item.postOrderPrint(print); cout << endl; }     // print out indented tree
	void preOrder() const { item.preOrderPrint(print); cout << endl; }
	void inOrder() const { item.inOrderPrint(print); cout << endl; }
	void hashStats() const { hashPtr->displayStats(); cout << endl; }		// Prints out the Hash Statistics
	void compare();														// Compare function
	void mostSearched(int num);											// HONORS: Shows the most searched for items

	//void printTree()		{ int width = 0; item.RNLOrder(width); }	// Prints out the indented tree
	Athlete& getAth() { return indentedTree; }
	BinarySearchTree<Athlete *>  getTree() { return item; }

};

#endif _AthleteRecord_H_