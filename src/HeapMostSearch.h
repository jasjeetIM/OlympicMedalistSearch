#ifndef _HeapMostSearch_H_
#define _HeapMostSearch_H_
#include <string>
#include "HeapMostSearch.h"
#include "Athlete.h"
#include <vector>

using namespace std; 

template <class AthleteType>
class HeapMostSearch
{
private:
	int count;
	int sizeArr;
	AthleteType * heapArr;

	void heapCreate(int numElements, bool visit(AthleteType, AthleteType, string));			// Function creates the heap from the array
	void heapRebuild(int index, bool visit(AthleteType, AthleteType, string));				// Rebuild heap after delete
	void swap(int a, int b);													// Function swaps value in the heap array
public:
	HeapMostSearch()
	{
		count = 0;
		heapArr = 0;
		sizeArr = 0;
	}
	~HeapMostSearch()            { clear(); }
	bool isEmpty() const         { return count == 0; }
	int getNumberOfNodes() const { return count; }
	int getHeight() const
	{
		return static_cast <int> (ceil((log(count + 1.0) / log(2.0))));
	}
	bool getTop(AthleteType & returnItem) const
	{
		if (isEmpty()) return false; returnItem = heapArr[0]; return true;
	}
	bool add(AthleteType & addNode, bool visit(AthleteType, AthleteType, string),
		bool visit1(AthleteType, AthleteType));
	bool remove(bool visit(AthleteType, AthleteType, string));
	bool update(const AthleteType & updateNode, bool visit(AthleteType, AthleteType, string),
		bool visit1(AthleteType, AthleteType));
	void clear()
	{
		count = 0;
		sizeArr = 0;
		delete[] heapArr;
		heapArr = 0;
	}
	void copy(const HeapMostSearch<AthleteType> & copyHeap, const vector <AthleteType> & arr, bool visit(AthleteType, AthleteType));
	void deleteBackup()
	{
		count = 0;
		sizeArr = 0;
		heapArr = 0;
	}
};

#endif _HeapMostSearch_H_