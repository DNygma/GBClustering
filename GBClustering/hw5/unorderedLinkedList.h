#pragma once

#ifndef unorderedLinkedList_h
#define unorderedLinkedList_h
#include <iostream>
#include "linkedListType.h"
using namespace std;

template <class qType> 
class unorderedLinkedList : public linkedListType<qType> {
public:
	bool search(const qType& searchItem) const;
	//Function to determine whether searchItem is in the list.
	//Postcondition: Returns true if searchItem is in the list,
	// otherwise the value false is returned.
	void insertFirst(const qType& newItem);
	//Function to insert newItem at the beginning of the list.
	//Postcondition: first points to the new list, newItem is
	//inserted at the beginning of the list, last points to the last node,
	//and count is incremented by 1.
	void insertLast(const qType& newItem);
	//Function to insert newItem at the end of the list.
	//Postcondition: first points to the new list, newItem is
	// inserted at the end of the list, last points to the
	// last node, and count is incremented by 1.
	void deleteNode(const qType& deleteItem);
	//Function to delete deleteItem from the list.
	//Postcondition: If found, the node containing deleteItem
	// is deleted from the list. first points to the first
	// node, last points to the last node of the updated
	// list, and count is decremented by 1.
	void destroyList();
};


template <class qType> 
bool unorderedLinkedList<qType>::search(const qType& searchItem) const
{
	nodeType<qType> *current; //pointer to traverse the list
	bool found = false;
	current = this->first; //set current to point to the first
						   //node in the list
	while (current != NULL && !found) //search the list
		if (current->info == searchItem) //searchItem is found
			found = true;
		else
			current = current->link; //make current point to
									 //the next node
	return found;
}//end search

template <class qType> 
void unorderedLinkedList<qType>::insertFirst(const qType& newItem) {
	nodeType<qType> *newNode; //pointer to create the new node
	newNode = new nodeType<qType>; //create the new node
	newNode->info = newItem; //store the new item in the node
	newNode->link = this->first; //insert newNode before first
	this->first = newNode; //make first point to the actual first node count++; //increment count
	if (this->last == NULL) //if the list was empty, newNode is also //the last node in the list
		this->last = newNode;
}//end insertFirst


template <class qType> 
void unorderedLinkedList<qType>::insertLast(const qType& newItem) {
	nodeType<qType> *newNode; //pointer to create the new node
	newNode = new nodeType<qType>; //create the new node
	newNode->info = newItem; //store the new item in the node
	newNode->link = NULL; //set the link field of newNode to NULL
	if (this->first == NULL) //if the list is empty, newNode is //both the first and last node
	{
		this->first = newNode;
		this->last = newNode;
		this->count++;
		//increment count
	}
	else //the list is not empty, insert newNode after last
	{
		this->last->link = newNode; //insert newNode after last
		this->last = newNode; //make last point to the actual
							  //last node in the list
		this->count++;        //increment count
	}
}//end insertLast

template <class qType> 
void unorderedLinkedList<qType>::deleteNode(const qType& deleteItem) {
	nodeType<qType> *current; //pointer to traverse the list
	nodeType<qType> *trailCurrent; //pointer just before current
	bool found;
	if (this->first == NULL)    //Case 1; the list is empty.
		cout << "Cannot delete from an empty list." << endl;
	else
	{
		if (this->first->info == deleteItem) //Case 2
		{
			current = this->first;
			this->first = this->first->link;
			this->count--;

			if (this->first == NULL) //the list has only one node
				this->last = NULL;

			delete current;
		}
		else //search the list for the node with the given info
			 //set trailCurrent to point
			 //to the first node
			 //set current to point to
			 //the second node
		{
			found = false;
			trailCurrent = this->first;
			current = this->first->link;

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current->link;
				}
				else found = true;
			}//end while

			if (found) //Case 3; if found, delete the node
			{
				trailCurrent->link = current->link;
				this->count--;
				if (this->last == current) //node to be deleted was the //last node
					this->last = trailCurrent; //update the value of last delete current; //delete the node from the list
			}
			else
				cout << "The item to be deleted is not in the list." << endl;

		}//end else
	}//end else
}//end deleteNode


template <class qType>
void unorderedLinkedList<qType>::destroyList() {
	nodeType<qType> *temp; //pointer to deallocate the memory
						  //occupied by the node
	if (this->first = NULL) {
		return;
	}		
	while (this->first != NULL) { //while there are nodes in the list
		temp = this->first; //set temp to the current node
		this->first = this->first->link; //advance first to the next node
		delete temp; //deallocate the memory occupied by temp
	}
	this->last = NULL; //initialize last to NULL; first has already
				 //been set to NULL by the while loop
	this->count = 0;
}
#endif /* unorderedLinkedList_h */