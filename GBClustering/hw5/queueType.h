#pragma once
#include <iostream>
#include "linkedQueueType.h"
#include "queueADT.h"

using namespace std;

template <class qType>
class queueType : public queueADT<qType>
{
public:
	const queueType<qType>& operator=(const queueType<qType>&);
	//Overload the assignment operator.
	bool isEmptyQueue() const;
	//Function to determine whether the queue is empty.
	//Postcondition: Returns true if the queue is empty,
	// otherwise returns false.
	bool isFullQueue() const;
	//Function to determine whether the queue is full.
	//Postcondition: Returns true if the queue is full,
	// otherwise returns false.
	void initializeQueue();
	//Function to initialize the queue to an empty state.
	//Postcondition: The queue is empty.
	qType front() const;
	//Function to return the first element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: If the queue is empty, the program
	// terminates; otherwise, the first element of the
	// queue is returned.
	qType back() const;
	//Function to return the last element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: If the queue is empty, the program
	// terminates; otherwise, the last element of the queue
	// is returned.
	void addQueue(const qType& queueElement);
	//Function to add queueElement to the queue.
	//Precondition: The queue exists and is not full.
	//Postcondition: The queue is changed and queueElement is
	// added to the queue.
	void deleteQueue();
	//Function to remove the first element of the queue.
	//Precondition: The queue exists and is not empty.
	//Postcondition: The queue is changed and the first element
	// is removed from the queue.
	queueType(int queueSize = 100);
	//Constructor
	queueType(const queueType<qType>& otherQueue);
	//Copy constructor
	~queueType();
	//Destructor
private:
	int maxQueueSize; //variable to store the maximum queue size
	int count; //variable to store the number of
			   //elements in the queue
	int queueFront; //variable to point to the first
					//element of the queue
	int queueRear; //variable to point to the last
				   //element of the queue
	qType *list; //pointer to the array that holds
				//the queue elements
};

template<class qType>
const queueType<qType>& queueType<qType>::operator=(const queueType<qType>& x) {
	list = x.list;
}

template<class qType>
queueType<qType>::queueType(const queueType<qType>& otherQueue) {
	list = otherQueue;
}

template <class qType>
bool queueType<qType>::isEmptyQueue() const
{
	return (count == 0);
} //end isEmptyQueue
template <class qType>
bool queueType<qType>::isFullQueue() const
{
	return (count == maxQueueSize);
} //end isFullQueue

template <class qType>
void queueType<qType>::initializeQueue()
{
	queueFront = 0;
	queueRear = maxQueueSize - 1;
	count = 0;
} //end initializeQueue

template <class qType>
qType queueType<qType>::front() const
{
	assert(!isEmptyQueue());
	return list[queueFront];
} //end front

template <class qType>
qType queueType<qType>::back() const
{
	assert(!isEmptyQueue());
	return list[queueRear];
} //end back

template <class qType>
void queueType<qType>::addQueue(const qType& newElement)
{
	if (!isFullQueue())
	{
		queueRear = (queueRear + 1) % maxQueueSize; //use the
													//mod operator to advance queueRear
													//because the array is circular
		count++;
		list[queueRear] = newElement;
	}
	else
		cout << "Cannot add to a full queue." << endl;
} //end addQueue

template <class qType>
void queueType<qType>::deleteQueue()
{
	if (!isEmptyQueue())
	{
		count--;
		queueFront = (queueFront + 1) % maxQueueSize; //use the
													  //mod operator to advance queueFront
													  //because the array is circular
	}
	else
		cout << "Cannot remove from an empty queue" << endl;
} //end deleteQueue

template <class qType>
queueType<qType>::queueType(int queueSize)
{
	if (queueSize <= 0)
	{
		cout << "Size of the array to hold the queue must "
			<< "be positive." << endl;
		cout << "Creating an array of size 100." << endl;
		maxQueueSize = 100;
	}
	else
		maxQueueSize = queueSize; //set maxQueueSize to
								  //queueSize
	queueFront = 0; //initialize queueFront
	queueRear = maxQueueSize - 1; //initialize queueRear
	count = 0;
	list = new qType[maxQueueSize]; //create the array to
								   //hold the queue elements
} //end constructor

template <class qType>
queueType<qType>::~queueType()
{
	delete[] list;
}