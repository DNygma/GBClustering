#pragma once

#ifndef linkedListType_h
#define linkedListType_h

#include "linkedListIterator.h"
#include <iostream>

using namespace std;


template <class qType> 
class linkedListType {
public:
	const linkedListType<qType>& operator=(const linkedListType<qType>&);
	//Overload the assignment operator
	void initializeList();
	//Initialize the list to an empty state.
	//Postcondition: first = NULL, last = NULL, count = 0;
	bool isEmptyList() const;
	//Function to determine whether the list is empty. //Postcondition: Returns true if the list is empty, otherwise it returns false.
	void print(ofstream &out) const;
	//Function to output the data contained in each node. //Postcondition: none
	int length() const;
	//Function to return the number of nodes in the list. //Postcondition: The value of count is returned.
	void destroyList();
	//Function to delete all the nodes from the list. //Postcondition: first = NULL, last = NULL, count = 0;
	qType front() const;
	//Function to return the first element of the list. //Precondition: The list must exist and must not be empty. //Postcondition: If the list is empty, the program terminates; // otherwise, the first element of the list is returned.
	qType back() const;
	//Function to return the last element of the list. //Precondition: The list must exist and must not be empty. //Postcondition: If the list is empty, the program
	// terminates; otherwise, the last
	//               element of the list is returned.
	virtual bool search(const qType& searchItem) const = 0;
	//Function to determine whether searchItem is in the list. //Postcondition: Returns true if searchItem is in the list,
	// otherwise the value false is returned.
	virtual void insertFirst(const qType& newItem) = 0; //Function to insert newItem at the beginning of the list. //Postcondition: first points to the new list, newItem is
													   // inserted at the beginning of the list, last points to
													   // the last node in the list, and count is incremented by
													   // 1.
	virtual void insertLast(const qType& newItem) = 0; //Function to insert newItem at the end of the list. //Postcondition: first points to the new list, newItem is
													  // inserted at the end of the list, last points to the
													  // last node in the list, and count is incremented by 1.
	virtual void deleteNode(const qType& deleteItem) = 0; //Function to delete deleteItem from the list. //Postcondition: If found, the node containing deleteItem is
														 // deleted from the list. first points to the first node,
														 // last points to the last node of the updated list, and
														 //    count is decremented by 1.
	linkedListIterator<qType> begin();
	//Function to return an iterator at the beginning of the //linked list.
	//Postcondition: Returns an iterator such that current is set // to first.
	linkedListIterator<qType> end();
	//Function to return an iterator one element past the
	//last element of the linked list.
	//Postcondition: Returns an iterator such that current is set // to NULL.
	linkedListType();
	//default constructor
	//Initializes the list to an empty state.
	//Postcondition: first = NULL, last = NULL, count = 0;
	linkedListType(const linkedListType<qType>& otherList);
	//copy constructor
	~linkedListType();
	//destructor
	//Deletes all the nodes from the list.
	//Postcondition: The list object is destroyed
protected:
	int count; //variable to store the number of list elements
	nodeType<qType> *first; //pointer to the first node of the list
	nodeType<qType> *last; //pointer to the last node of the list
private:
	void copyList(const linkedListType<qType>& otherList);
	//Function to make a copy of otherList.
	//Postcondition: A copy of otherList is created and assigned // to this list
};

template <class qType>
bool linkedListType<qType>::isEmptyList() const {
	return (first == NULL);
}

template <class qType>
linkedListType<qType>::linkedListType() {  //default constructor
	first = NULL;
	last = NULL;
	count = 0;
}

template <class qType> 
linkedListType<qType>::~linkedListType() {  //destructor
	destroyList();
}


template <class qType> 
void linkedListType<qType>::destroyList() {
	nodeType<qType> *temp;
	while (first != NULL) {
		//pointer to deallocate the memory
		//occupied by the node
		//while there are nodes in the list
		temp = first;
		first = first->link; //advance first to the next node
		delete temp; //deallocate the memory occupied by temp
	}
	last = NULL; //initialize last to NULL; first has already //been set to NULL by the while loop
	count = 0;
}

template <class qType>
void linkedListType<qType>::initializeList() {
	destroyList(); //if the list has any nodes, delete them
}

template <class qType>
void linkedListType<qType>::print(ofstream &out) const {
	nodeType<qType> *current; //pointer to traverse the list
	current = first; //set current point to the first node
	while (current != NULL) //while more data to print
	{
		out << current->info << " ";
		cerr << current->info << " "; 
		current = current->link;
	}
}//end print

template <class qType>
int linkedListType<qType>::length() const
{
	return count;
}

template <class qType> 
qType linkedListType<qType>::front() const {
	assert(first != NULL);
	return first->info; //return the info of the first node
}//end front

template <class qType>
qType linkedListType<qType>::back() const {
	assert(last != NULL);
	return last->info; //return the info of the last node
}//end back

template <class qType> 
linkedListIterator<qType> linkedListType<qType>::begin()
{
	linkedListIterator<qType> temp(this->first);
	return temp;
}

template <class qType> 
linkedListIterator<qType> linkedListType<qType>::end() {
	linkedListIterator<qType> temp(NULL);
	return temp;
}

template <class qType> 
void linkedListType<qType>::copyList(const linkedListType<qType>& otherList) {

	nodeType<qType> *newNode; //pointer to create a node
	nodeType<qType> *current; //pointer to traverse the list
	if (first != NULL) //if the list is nonempty, make it empty
		destroyList();

	if (otherList.first == NULL) //otherList is empty
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	else
	{
		current = otherList.first; //current points to //list to be copied
		count = otherList.count;
		//copy the first node
		first = new nodeType<qType>; //create the node
		first->info = current->info;
		first->link = NULL;
		last = first;
		current = current->link; //make current point to the next

		while (current != NULL)
		{
			newNode = new nodeType<qType>; //create a node
			newNode->info = current->info; //copy the info
			newNode->link = NULL; //set the link of newNode to NULL
			last->link = newNode; //attach newNode after last
			last = newNode; //make last point to the actual last node
			current = current->link; //make current point to the next node
		}//end while
	}//end else
}//end copyList


template <class qType> 
linkedListType<qType>::linkedListType(const linkedListType<qType>& otherList) {
	first = NULL;
	copyList(otherList);
}//end copy constructor

 //overload the assignment operator
template <class qType>
const linkedListType<qType>& linkedListType<qType>::operator=(const linkedListType<qType>& otherList) {
	if (this != &otherList) //avoid self-copy
	{
		copyList(otherList);
	}
	return *this;
}

#endif /* linkedListType_h */