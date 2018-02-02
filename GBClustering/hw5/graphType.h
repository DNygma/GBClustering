/*#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "unorderedLinkedList.h"
#include "linkedQueueType.h"
#include "linkedListIterator.h"
#include "msTreeType.h"
using namespace std;

template <class gType>
class graphType {
public:
	bool isEmpty() const;
	//Function to determine whether the graph is empty.
	//Postcondition: Returns true if the graph is empty;
	// otherwise, returns false.
	void clearGraph();
	//Function to clear graph.
	//Postcondition: The memory occupied by each vertex
	// is deallocated.
	void printGraph() const;
	//Function to print graph.
	//Postcondition: The graph is printed.
	void depthFirstTraversal();
	//Function to perform the depth first traversal of
	//the entire graph.
	//Postcondition: The vertices of the graph are printed
	// using the depth first traversal algorithm
	void dftAtVertex(int vertex);
	//Function to perform the depth first traversal of
	//the graph at a node specified by the parameter vertex.
	//Postcondition: Starting at vertex, the vertices are
	// printed using the depth first traversal algorithm.
	void breadthFirstTraversal();
	//Function to perform the breadth first traversal of
	//the entire graph.
	//Postcondition: The vertices of the graph are printed
	// using the breadth first traversal algorithm.
	graphType(int size = 0);
	//Constructor
	//Postcondition: gSize = 0; maxSize = size;
	// graph is an array of pointers to linked lists.
	~graphType();
	//Destructor
	//The storage occupied by the vertices is deallocated.
protected:
	int maxSize; //maximum number of vertices
	int gSize; //current number of vertices
	unorderedLinkedList<int> *graph; //array to create
									 //adjacency lists
private:
	void dft(int v, bool visited[]);
	//Function to perform the depth first traversal of
	//the graph at a node specified by the parameter vertex.
	//This function is used by the public member functions
	//depthFirstTraversal and dftAtVertex.
	//Postcondition: Starting at vertex, the vertices are
	// printed using the depth first traversal algorithm
};

template <class gType>
bool graphType<gType>::isEmpty() const {
	return (gSize == 0);
}

template <class gType>
void graphType<gType>::clearGraph()
{
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();
	gSize = 0;
} //end clearGraph

template <class gType>
void graphType<gType>::printGraph() const
{
	for (int index = 0; index < gSize; index++)
	{
		cout << index << " ";
		graph[index].print();
		cout << endl;
	}
	cout << endl;
} //end printGraph

//Constructor
template <class gType>
graphType<gType>::graphType(int size) {
	maxSize = size;
	graph = new unorderedLinkedList<int>[size];
}

//Destructor
template <class gType>
graphType<gType>::~graphType()
{
	clearGraph();
}

template <class gType>
void graphType<gType>::dft(int v, bool visited[])
{
	visited[v] = true;
	cout << " " << v << " "; //visit the vertex
	linkedListIterator<int> graphIt;
	//for each vertex adjacent to v
	for (graphIt = graph[v].begin(); graphIt != graph[v].end();
		++graphIt)
	{
		int w = *graphIt;
		if (!visited[w])
			dft(w, visited);
	} //end while
} //end dft

template <class gType>
void graphType<gType>::depthFirstTraversal()
{
	bool *visited; //pointer to create the array to keep
				   //track of the visited vertices
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	//For each vertex that is not visited, do a depth
	//first traverssal
	for (int index = 0; index < gSize; index++)
		if (!visited[index])
			dft(index, visited);
	delete[] visited;
} //end depthFirstTraversal

template <class gType>
void graphType<gType>::dftAtVertex(int vertex)
{
	bool *visited;
	visited = new bool[gSize];
	for (int index = 0; index < gSize; index++)
		visited[index] = false;
	dft(vertex, visited);
	delete[] visited;
} // end dftAtVertex

template <class gType>
void graphType<gType>::breadthFirstTraversal()
{
	linkedQueueType<int> queue;
	bool *visited;
	visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; //initialize the array
							  //visited to false
	linkedListIterator<int> graphIt;
	for (int index = 0; index < gSize; index++)
		if (!visited[index]) {
			queue.addQueue(index);
			visited[index] = true;
			cout << " " << index << " ";
			while (!queue.isEmptyQueue()) {
				int u = queue.front();
				queue.deleteQueue();
				for (graphIt = graph[u].begin(); 
					graphIt != graph[u].end(); ++graphIt) {
					int w = *graphIt;
					if (!visited[w]) {
						queue.addQueue(w);
						visited[w] = true;
						cout << " " << w << " ";
					}
				}
			} //end while
		}
	cout << endl;
	delete[] visited;
} //end breadthFirstTraversal*/