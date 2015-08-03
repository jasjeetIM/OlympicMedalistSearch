#ifndef _BinaryNode_H_
#define _BinaryNode_H_

#include "Athlete.h"

template<class AthleteType>
class BinaryNode
{
private:
	AthleteType item;
	BinaryNode<AthleteType>* left;
	BinaryNode<AthleteType>* right;
public:
	BinaryNode()
	{
		left = 0;
		right = 0;
	}
	BinaryNode(const AthleteType & anItem)
	{
		item = anItem;
		left = 0;
		right = 0;
	}
	BinaryNode(const AthleteType & anItem, BinaryNode<AthleteType>* left1,
		BinaryNode<AthleteType>* right1)
	{
		item = anItem; left = left1; right = right1;
	}
	void setItem(const AthleteType & anItem)		   { item = anItem; }
	void setLeftPtr(BinaryNode<AthleteType>* left1)	   { left = left1; }
	void setRightPtr(BinaryNode<AthleteType>* right1)  { right = right1; }
	AthleteType getItem() const	       { return item; }
	AthleteType getIte() const { return item; }
	Athlete getIt() { return *item; }
	BinaryNode<AthleteType>* getLeftPtr() const	       { return left; }
	BinaryNode<AthleteType>* getRightPtr() const	   { return right; }
	bool checkLeaf() const
	{
		return (left == 0 && right == 0);
	}
};

#endif _BinaryNode_H