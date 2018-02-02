#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "unorderedLinkedList.h"
#include "linkedQueueType.h"
#include "linkedListIterator.h"
#include "orderedLinkedList.h"
using namespace std;

template<class gType>
class msTreeType {
public:
	void weightedCheckerBoard(ifstream &infile, ofstream &outfile); //createSpanningGraph
	void UNeed2CutIt(); //cut highest weights from adjacent list
	void AdjustTree();	// adjust adjacent list to show cuts
	void minimumSpanning(int sVertX); //minimum Spanning Tree to get the shortest distance
	void printTreeAndWeight(); // Print Tree
	msTreeType(int size = 0);
	~msTreeType();
	void clearGraph();
	void breadthFirstTraversal(ofstream &out);
protected:
	int source;
	double **weights;
	int *edges;
	double *edgeWeights;
	int cluster;
	unorderedLinkedList<int> *graph; //array to create adjacency lists
public:
	int gSize; //current number of vertices
	int maxSize; //maximum number of vertices
};

template<class gType>
void msTreeType<gType>::weightedCheckerBoard(ifstream &infile, ofstream &outfile) {
	for (int i = 0; i < gSize; i++) {					
		for (int j = 0; j < gSize; j++) {
			weights[i][j] = -999;		//set all weights in the graph to -999
		}
	}
	string lineByline, next;
	int index = 0;
	while (!infile.eof()) {
		getline(infile, lineByline);
		stringstream ss(lineByline);
		if (lineByline == "") {
			break;
		}
		while (ss >> next) {
			int x = stoi(next, nullptr, 10);
			graph[index].insertLast(x);
		}
		index++;
	} index = 0;
	int vertX = 0, adjVertX = 0;
	while (!infile.eof()) {
		getline(infile, lineByline);
		stringstream ss(lineByline);
		if (lineByline == "") {
			break;
		}
		while (ss >> next) {
			int x = stoi(next, nullptr, 10);
			weights[vertX][adjVertX] = x;
			adjVertX++;
		}
		vertX++;
		if (adjVertX != gSize) {
			outfile << "";
			exit(0);
		}
		adjVertX = 0;
	}
	if (vertX != gSize) {
		outfile << "";
		exit(0);
	}
}

template<class gType>
void msTreeType<gType>::AdjustTree() { //create a new spanning tree
	int tempTree = gSize; //set the tempTree to gSize
	clearGraph(); //clear original graph
	gSize = tempTree; //set gSize back to tempTree
	tempTree = 0; //tempTree back to normal for next iteration
	for (int xCord = 0; xCord < gSize; xCord++) {
		if (edges[xCord] == xCord || edgeWeights[xCord] == -999) { //dont insert if same value or empty
			continue;
		}
		else {
			graph[edges[xCord]].insertLast(xCord); //push both coordinates (x, y)
			graph[xCord].insertLast(edges[xCord]); //and (y, x)
		}
	}
}

template<class qType>
void msTreeType<qType>::UNeed2CutIt() { 
	int at = 0;
	double tempWeight = 0;
	for (int x = 0; x < gSize; x++) {
		if (tempWeight < edgeWeights[x]) {  // if temp weight is less than the edgeWeight
			tempWeight = edgeWeights[x]; // set the tempWeight to the highest edgeWeight
			at = x;	// get the position of that weight
		}
	}
	edgeWeights[at] = -999; // set it to -999
}

template<class gType>
void msTreeType<gType>::minimumSpanning(int sVertex) {
	int startVertex, endVertex;
	double minWeight;
	source = sVertex;
	bool *mstv;
	mstv = new bool[gSize];
	for (int j = 0; j < gSize; j++)	{
		mstv[j] = false;
		edges[j] = source;
		edgeWeights[j] = weights[source][j];
	}
	mstv[source] = true;
	edgeWeights[source] = 0;
	for (int i = 0; i < gSize - 1; i++) {
		minWeight = DBL_MAX;
		for (int j = 0; j < gSize; j++)
			if (mstv[j])
				for (int k = 0; k < gSize; k++)
					if (!mstv[k] && weights[j][k] < minWeight && weights[j][k] != -999)
					{
						endVertex = k;
						startVertex = j;
						minWeight = weights[j][k];
					}
		mstv[endVertex] = true;
		edges[endVertex] = startVertex;
		edgeWeights[endVertex] = minWeight;
	} 
}

template<class gType>
void msTreeType<gType>::printTreeAndWeight() {
	double treeWeight = 0;
	cout << "Source Vertex: " << source << endl;
	cout << "Edges Weight" << endl;
	for (int j = 0; j < gSize; j++)
	{
		if (edges[j] != j) {
			treeWeight = treeWeight + edgeWeights[j];
			cout << "(" << edges[j] << ", " << j << ") "
				<< edgeWeights[j] << endl;
		}
	}
	cout << endl;
	cout << "Minimum spanning Tree Weight: "
		<< treeWeight << endl;
}

template<class gType>
msTreeType<gType>::msTreeType(int size) {
	if (gSize != 0) //if the graph is not empty, make it empty
		clearGraph();
	maxSize = size * 10;
	gSize = size;
	graph = new unorderedLinkedList<int>[size];
	weights = new double*[size];
	for (int i = 0; i < size; i++)
		weights[i] = new double[size];
	edges = new int[size];
	edgeWeights = new double[size];
}

template<class gType>
msTreeType<gType>::~msTreeType() {
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];
	delete[] weights;
	delete[] edges;
	delete[] edgeWeights;
}

template <class gType>
void msTreeType<gType>::clearGraph() {
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();
	gSize = 0;
}

template <class gType>
void msTreeType<gType>::breadthFirstTraversal(ofstream &out) {
	linkedQueueType<int> queue;
	orderedLinkedList<int> temp;
	bool *visited;
	visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; 
	linkedListIterator<int> graphIt;
	for (int index = 0; index < gSize; index++)
		
		if (!visited[index]) {
			queue.addQueue(index);
			visited[index] = true;
			temp.destroyList();
			temp.insert(index);
			while (!queue.isEmptyQueue()) {
				int u = queue.front();
				queue.deleteQueue();
				for (graphIt = graph[u].begin();
					graphIt != graph[u].end(); ++graphIt) {
					int w = *graphIt;
					if (!visited[w]) {
						queue.addQueue(w);
						visited[w] = true;
						temp.insert(w);
					}
				}
			} 			
			temp.print(out);
			out << endl;
			cerr << endl;
		}
	delete[] visited;
}