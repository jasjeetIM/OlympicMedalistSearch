#ifndef _HashTable_H_
#define _HashTable_H

#include "Athlete.h";
#include <iostream>;



class HashTable
{
private:
    Athlete * nodePtr;
	bool        status;
	int         numberOfCollisions;
public:
	HashTable()
	{
		nodePtr = 0;
		status = false;
		numberOfCollisions = 0;
	}
	~HashTable()
	{
		if (nodePtr != 0)
			delete nodePtr;
	}
	void setWasUsed(bool value)      { status = value; }
	void setItemPtr(Athlete* ptr) { nodePtr = ptr; status = true; }
	void deleteNode()
	{
		if (nodePtr)
			delete nodePtr;
		nodePtr = 0;
		status = true;
	}
	void displayNode()
	{
		cout << nodePtr->getName() << " " << nodePtr->getYear() << endl;
	}
	void collisionIncrease(int num)  { numberOfCollisions = num; }
	int  getCollisions()             { return numberOfCollisions; }
	Athlete* getItemPtr()           { return nodePtr; }
	bool hadBeenUsed()              { return status; }
};

#endif _HashTable_H_
