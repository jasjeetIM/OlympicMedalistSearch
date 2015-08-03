#ifndef _Node_H_
#define _Node_H_


template<class AthleteType>
class Node
{
private:
	AthleteType        item;
	Node<AthleteType>* next;
public:
	Node() { item = anItem; next = 0; };
	Node(const AthleteType& anItem)				    { item = anItem; next = 0; }
	void setItem(const AthleteType& anItem)		    { item = anItem; }
	void setNext(Node<AthleteType>* nextNodePtr)	{ next = nextNodePtr; }
	AthleteType getItem() 					    { return item; }
	Node<AthleteType>* getNext() const				{ return next; }
};

#endif _Node_H_ 



