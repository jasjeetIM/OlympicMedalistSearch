#ifndef _HashedTable_H_
#define _HashedTable_H_

#include "HashTable.h"; 
#include <vector>; 



class HashedTable
{
private:
	int size;
	int numberOfAthletes;
	HashTable *nodePtr;

	int hashingFunction(string name);
	int collisionResolution(int index, string name);
public:
	HashedTable(int size)
	{
		this->size = size;
		nodePtr = new HashTable[this->size];
		numberOfAthletes = 0;
	}
	HashedTable(HashedTable* oldTable, const vector <Athlete*> &array,
		int numOfAthletes);
	~HashedTable()
	{
		delete[] nodePtr;
	}
	bool insert(Athlete* nodePtr);
	string stringToLower(string name);
	bool deleteAthlete(string Athlete);
	bool deleteAthlete(Athlete* nodePtr);
	void display(void visit(Athlete* ptr));
	bool findAthlete(string Athlete, class Athlete* & returnPointerToAthlete);
	void displayStats();

};

#endif _HashedTable_H_