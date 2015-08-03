#include "stdafx.h"
#include "HeapMostSearch.h"

template <class AthleteType>
void HeapMostSearch<AthleteType>::swap(int index1, int index2)
{
	AthleteType temp = heapArr[index1];
	heapArr[index1] = heapArr[index2];
	heapArr[index2] = temp;
}

template <class AthleteType>
void HeapMostSearch<AthleteType>::heapCreate(int numElements, bool visit(AthleteType, AthleteType, string))
{
	for (int i = (numElements - 2) / 2; i >= 0; i--)
	{
		heapRebuild(i, visit);
	}
}

template <class AthleteType>
void HeapMostSearch<AthleteType>::heapRebuild(int index, bool visit(AthleteType, AthleteType, string))
{
	AthleteType leftValue, rightValue;
	int largeIndex;

	if ((index * 2) + 1 < count)
	{
		leftValue = heapArr[(index * 2) + 1];
		if ((index * 2) + 2 > (count - 1))
		{
			largeIndex = (index * 2) + 1;
		}
		else
		{
			rightValue = heapArr[(index * 2) + 2];
			if (visit(leftValue, rightValue, ">"))
			{
				largeIndex = (index * 2) + 1;
			}
			else
			{
				largeIndex = (index * 2) + 2;
			}
		}
		if (visit(heapArr[index], heapArr[largeIndex], "<"))
		{
			swap(index, largeIndex);
			heapRebuild(largeIndex, visit);
		}
	}
}

template <class AthleteType>
bool HeapMostSearch<AthleteType>::add(AthleteType & addNode,
	bool visit(AthleteType, AthleteType, string), bool visit1(AthleteType, AthleteType))
{
	if (count == 0)
	{
		sizeArr = 10;
		heapArr = new AthleteType[sizeArr];
		heapArr[count] = addNode;
		count++;
		return true;
	}

	if (count >= sizeArr)
	{
		double height = ceil((log(count + 1.0) / log(2.0)));
		int fullSize = static_cast <int> (pow(2, height)) - 1;

		AthleteType * newHeap = heapArr;
		heapArr = new AthleteType[fullSize];
		for (int i = 0; i < sizeArr; i++)
		{
			heapArr[i] = newHeap[i];
		}
		sizeArr = fullSize;

		delete[] newHeap;
	}

	bool duplicate = false;
	int index = 0, duplicateIndex;

	while (index < count && !duplicate)
	{
		if (visit1(heapArr[index], addNode))
		{
			duplicateIndex = index;
			duplicate = true;
		}
		index++;
	}

	if (duplicate)
	{
		heapArr[duplicateIndex] = addNode;
		heapCreate(count, visit);
		return true;
	}

	heapArr[count] = addNode;
	count++;
	heapCreate(count, visit);

	return true;
}

template <class AthleteType>
bool HeapMostSearch<AthleteType>::remove(bool visit(AthleteType, AthleteType, string))
{
	if (count == 0)
	{
		return false;
	}
	if (count == 1)
	{
		count--;
		return true;
	}
	swap(0, count - 1);
	count--;
	heapRebuild(0, visit);

	return true;
}

template <class AthleteType>
bool HeapMostSearch<AthleteType>::update(const AthleteType & updateNode,
	bool visit(AthleteType, AthleteType, string), bool visit1(AthleteType, AthleteType))
{
	bool same = false;
	int index = 0, sameIndex;

	while (index < count && !same)
	{
		if (visit1(heapArr[index], updateNode))
		{
			sameIndex = index;
			same = true;
		}
		index++;
	}

	if (same)
	{
		heapArr[sameIndex] = heapArr[count - 1];
		count--;
		heapCreate(count, visit);
	}

	return true;
}

template <class AthleteType>
void HeapMostSearch<AthleteType>::copy(const HeapMostSearch<AthleteType> & copyHeap,
	const vector <AthleteType> & arr, bool visit(AthleteType, AthleteType))
{
	count = copyHeap.count;
	sizeArr = copyHeap.sizeArr;
	heapArr = new AthleteType[sizeArr];

	bool found = false;

	for (int i = 0; i < copyHeap.count; i++)
	{
		for (unsigned int j = 0; j < arr.size() && !found; j++)
		{
			found = visit(copyHeap.heapArr[i], arr[j]);
			if (found)
			{
				heapArr[i] = arr[j];
			}
		}
	}
}