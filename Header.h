#pragma once

// Author: Manasi Tirukachi
#include <iostream>
using namespace std;

#ifndef HEADER_H
#define HEADER_H
enum color {white, black };

struct node
{
	string cityname; //name of this city
	double d; //distance of this city 
	int degree; //degree
	color vcolor; //color of node/v
	node* parent; //to set the parent node
	node* adj; //links to the adjacent city
};

struct adjlist
{
	string cityname;
	adjlist* adj;
	adjlist* next; //links to the next city	
	double weight = 0;
};

class graph
{
public:

	adjlist* list; //adjacency list to show the connection of edges
	node* start; //list to connect the nodes with information to one another

	int nodes;
	int edges;
	//constructor and destructor 
	graph();
	~graph();

	void insert(string name);
	void setd(string city1, string city2, double distance);

	bool search(string name);

	int finddegree(string name);

	
	double distance (string city1, string city2);
	
	double shortest_distance (string city1, string city2);

	void print(string city1, string city2);
	void clear();

};
//heapify functions
void buildheap(node** arr, int end, int n);
void heapify(node** arr, int i, int n);
void heapifyup(node** arr, int n);
#endif
