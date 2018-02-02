#pragma once
#include <cassert>
#include "queueType.h"
using namespace std;

template <class qType>
struct nodeType
{
qType info;
nodeType<qType> *link;
};

template <class qType>
class linkedQueueType : public queueADT<qType>
{
public:
	//const linkedQueueType<Type>& operator=(const linkedQueueType<Type>&);
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
	//Postcondition: queueFront = NULL; queueRear = NULL
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
	// terminates; otherwise, the last element of the
	// queue is returned.
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
	linkedQueueType();
	//Default constructor
	linkedQueueType(const linkedQueueType<qType>& otherQueue);
	//Copy constructor
	~linkedQueueType();
	//Destructor
private:
	nodeType<qType> *queueFront; //pointer to the front of the queue
	nodeType<qType> *queueRear; //pointer to the rear of the queue
};

template <class qType>
bool linkedQueueType<qType>::isEmptyQueue() const
{
	return(queueFront == NULL);
} //end
template <class qType>
bool linkedQueueType<qType>::isFullQueue() const
{
	return false;
} //end isFullQueue

template <class qType>
void linkedQueueType<qType>::initializeQueue()
{
	nodeType<qType> *temp;
	while (queueFront != NULL) //while there are elements left
							   //in the queue
	{
		temp = queueFront; //set temp to point to the current node
		queueFront = queueFront->link; //advance first to
									   //the next node
		delete temp; //deallocate memory occupied by temp
	}
	queueRear = NULL; //set rear to NULL
} //end initializeQueue


template <class qType>
void linkedQueueType<qType>::addQueue(const qType& newElement)
{
	nodeType<qType> *newNode;
	newNode = new nodeType<qType>; //create the node
	newNode->info = newElement; //store the info
	newNode->link = NULL; //initialize the link field to NULL
	if (queueFront == NULL) //if initially the queue is empty
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else //add newNode at the end
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}
}//end addQueue


template <class qType>
qType linkedQueueType<qType>::front() const
{
	assert(queueFront != NULL);
	return queueFront->info;
} //end front

template <class qType>
qType linkedQueueType<qType>::back() const
{
	assert(queueRear != NULL);
	return queueRear->info;
} //end back

template <class qType>
void linkedQueueType<qType>::deleteQueue()
{
	nodeType<qType> *temp;
	if (!isEmptyQueue())
	{
		temp = queueFront; //make temp point to the first node
		queueFront = queueFront->link; //advance queueFront
		delete temp; //delete the first node
		if (queueFront == NULL) //if after deletion the
								//queue is empty
			queueRear = NULL; //set queueRear to NULL
	}
	else
		cout << "Cannot remove from an empty queue" << endl;
}//end deleteQueue


template<class qType>
linkedQueueType<qType>::linkedQueueType()
{
	queueFront = NULL; //set front to null
	queueRear = NULL; //set rear to null
} //end default constructor

template<class qType>
linkedQueueType<qType>::linkedQueueType(const linkedQueueType<qType>& otherQueue) {
	queueFront = otherQueue.queueFront;
	queueRear = otherQueue.queueRear;
}

/*template<class Type>
linkedQueueType<Type>::linkedQueueType<int>&operator=(const linkedQueueType<Type>& otherQueue) {
	queueFront = otherQueue.queueFront;
	queueRear = otherQueue.queueRear;
}*/


template<class qType>
linkedQueueType<qType>::~linkedQueueType(){
	initializeQueue();
	queueFront = NULL; //set front to null
	queueRear = NULL; //set rear to null
} //end default destructor