#pragma once
#ifndef linkedListIterator_h
#define linkedListIterator_h

#include "linkedQueueType.h"
/*template <class Type> 
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};*/


template <class qType> 
class linkedListIterator : linkedQueueType<qType> {
public:
	linkedListIterator();
	//Default constructor
	//Postcondition: current = NULL;

	linkedListIterator(nodeType<qType> *ptr);
	//Constructor with a parameter.
	//Postcondition: current = ptr;

	qType operator*();
	//Function to overload the dereferencing operator *.
	//Postcondition: Returns the info contained in the node.

	linkedListIterator<qType> operator++();
	//Overload the preincrement operator.
	//Postcondition: The iterator is advanced to the next node.

	bool operator==(const linkedListIterator<qType>& right) const;
	//Overload the equality operator.
	//Postcondition: Returns true if this iterator is equal to
	// the iterator specified by right, otherwise it returns
	// false.

	bool operator!=(const linkedListIterator<qType>& right) const;
	//Overload the not equal to operator.
	//Postcondition: Returns true if this iterator is not equal to
	// the iterator specified by right, otherwise it returns
	// false.

private:
	nodeType<qType> *current; //pointer to point to the current
							 //node in the linked list
};


template <class qType> 
linkedListIterator<qType>::linkedListIterator()
{
	current = NULL;
}

template <class qType> 
linkedListIterator<qType>::linkedListIterator(nodeType<qType> *ptr)
{
	current = ptr;
}

template <class qType>
qType linkedListIterator<qType>::operator*()
{
	return current->info;
}

template <class qType> linkedListIterator<qType> linkedListIterator<qType>::operator++()
{
	current = current->link;
	return *this;
}

template <class qType> bool linkedListIterator<qType>::operator==(const linkedListIterator<qType>& right) const
{
	return (current == right.current);
}

template <class qType> bool linkedListIterator<qType>::operator!=(const linkedListIterator<qType>& right) const
{
	return (current != right.current);
}

#endif /* linkedListIterator_h */