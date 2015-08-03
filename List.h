#ifndef _List_H_
#define _List_H_

#include "LinkedList.h"

template<class AthleteType>
class List : public LinkedList<AthleteType>  // inherited from LinkedList class
{
private:
	Node<AthleteType>* getNodeAt(int position) const;
public:
	bool insert(const AthleteType &, int newPosition = 1);
	bool remove(int position);
	bool getEntry(int position, AthleteType &) const;
};


#endif _List_H_