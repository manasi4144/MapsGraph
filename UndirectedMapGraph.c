// undirectedgraph.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <limits.h>
#include <string.h>
#include <string> 
#include<stdio.h>
#include <sstream>
#include "Header.h"
#include <array>
using namespace std;
//GLOBAL variables

graph::graph()
{
	this->list = NULL;
	this->start = NULL;
	this->edges = 0;
	this->nodes = 0;
}

graph::~graph()
{
	//do nothing? clear the nodes? call clear?
}

void graph::insert(string name)
{
	//comes into here only after search is done, this can be void
	node* temp = new node;
	temp->cityname = name;
	temp->parent = NULL;
	temp->adj = NULL;
	temp->vcolor = white;
	temp->d = LONG_MAX;
	temp->degree = 0;

	if (this->start == NULL)
	{
		this->start = temp;
		this->nodes++;
		return;
	}

	node* current = this->start;
	while (current->adj != NULL)
	{
		current = current->adj;
	}

	current->adj = temp;
	this->nodes++;
	return;

}

void graph::setd(string city1, string city2, double distance)
{
	//comes into here only after search is done, this can be void

	//node* temp;
	adjlist* current;

	adjlist* first = new adjlist;
	first->cityname = city2;
	first->weight = distance;
	first->next = NULL;
	first->adj = NULL;

	adjlist* second = new adjlist;
	second->cityname = city1;
	second->weight = distance;
	second->next = NULL;
	second->adj = NULL;
	adjlist* head = this->list;
	//if the list has no nodes
	if (head == NULL)
	{
		current = new adjlist;
		current->cityname = city1;
		current->weight = 0;

		adjlist* another = new adjlist;
		another->cityname = city2;
		another->weight = 0;
		current->next = another;

		current->adj = first;
		another->adj = second;
		another->next = NULL;

		this->list = current;
		this->edges++;
		return;
	}
	else
	{
		bool citone = false;
		bool cittwo = false;

		while (true)
		{
			if (head->cityname == city1)
			{
				adjlist* temp = head;
				while (temp->adj != NULL)
				{
					temp = temp->adj;
				}

				temp->adj = first;
				citone = true;
			}

			if (head->cityname == city2)
			{
				adjlist* temp1 = head;
				while (temp1->adj != NULL)
				{
					temp1 = temp1->adj;
				}

				temp1->adj = second;
				cittwo = true;
			}
			if (head->next != NULL)
			{
				head = head->next;
			}
			else
			{
				break;
			}

		}

		//if city node not existing within the list
		if (!citone)
		{
			current = new adjlist;
			current->cityname = city1;
			current->weight = 0;
			current->next = NULL;
			current->adj = first;

			head->next = current;

		}

		//if city2 node not within the list
		if (!cittwo)
		{
			current = new adjlist;
			current->cityname = city2;
			current->weight = 0;
			current->next = NULL;
			current->adj = second;

			head->next = current;
		}

		this->edges++;
		return;
	}

	return;
}

bool graph::search(string name)
{
	node* head = this->start;
	if (head == NULL)
	{
		return false;
	}
	if (head->cityname == name)
	{
		return true;
	}

	while (true)
	{
		if (head->cityname == name)
		{
			return true;
		}
		if (head->adj != NULL)
		{
			head = head->adj;
		}
		else
		{
			break;
		}
	}

	return false;
}



double graph::distance(string city1, string city2)
{
	adjlist* head = this->list;

	while (true)
	{
		if (head->cityname == city1 || head->cityname == city2)
		{
			adjlist* temp = head;
			while (temp->adj != NULL)
			{
				if (temp->adj->cityname == city1 || temp->adj->cityname == city2)
				{
					return temp->adj->weight;
				}
				temp = temp->adj;
			}

			return -1;
		}
		if (head->next != NULL)
		{
			head = head->next;
		}
		else
		{
			break;
		}

	}

	return -1;
}

int graph::finddegree(string name)
{
	adjlist* head = this->list;
	int count = 0;

	while (true)
	{
		if (head->cityname == name)
		{
			adjlist* temp = head;
			while (true)
			{
				if (temp->adj != NULL)
				{
					temp = temp->adj;
					count++;
				}
				else
				{
					break;
				}
			}

			return count;
		}

		if (head->next != NULL)
		{
			head = head->next;
		}
		else
		{
			break;
		}

	}

	return count;
}

void buildheap(node** arr, int end, int n)
{
	for (int i = (n / 2); i >= end; i--)
	{
		heapify(arr, i, n - 1);
	}

	heapifyup(arr, n);
	/*for (int j = 0; j < n; j++)
	{
		cout << arr[j]->cityname << " ";
	}
	cout << endl;*/

	return;
}

void heapifyup(node** arr, int n)
{
	for (int j = 1; j < n; j++)
	{
		if (arr[j - 1]->d > arr[j]->d)
		{
			node* temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
		}

	}
	return;
}

void heapify(node** arr, int i, int n)
{
	int l = 2 * i;
	int r = 2 * i + 1;
	node* left = arr[l];
	node* right = arr[r];
	node* end = arr[n];
	int smallest = 0;

	if ((l <= n) && (left->d < end->d))
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}

	node* small = arr[smallest];

	if ((r <= n) && (right->d < small->d))
	{
		smallest = r;
	}

	if (smallest != i)
	{
		node* temp = arr[i];
		arr[i] = arr[smallest];
		arr[smallest] = temp;
		//	cout << arr[i]->cityname << endl;
			//cout << arr[smallest]->cityname << endl;
		heapify(arr, smallest, n);
	}

	return;
}


double graph::shortest_distance(string city1, string city2)
{
	//making the array of pointers to the nodes for the heap

	if (this->start == NULL)
	{
		return -1;
	}

	node** arr = new node * [this->nodes];
	node* tail = this->start;
	arr[0] = this->start;

	for (int i = 1; i < this->nodes; i++)
	{
		arr[i] = tail->adj;
		if (tail->cityname == city1)
		{
			tail->d = 0;
		}
		tail = tail->adj;
	}

	//test this out!

	int n = this->nodes;
	buildheap(arr, 0, n);

	//searching for the source node in the node list
	for (int i = 0; i < this->nodes; i++)
	{
		buildheap(arr, 0, n);

		//picking source here
		node* head = arr[i];
		node* source = this->start;
		//bool found = false;

		while (true)
		{
			if (source->cityname == head->cityname)
			{
				break;
			}
			if (source->adj != NULL)
			{
				source = source->adj;
			}
			else
			{
				break;
			}
		}

		//searching for the adjacent list of the source node

		adjlist* vertex = this->list;
		while (true)
		{
			if (vertex->cityname == head->cityname)
			{
				break;
			}
			if (vertex->next != NULL)
			{
				vertex = vertex->next;
			}
			else
			{
				break;
			}
		}

		//navigate through each adjacent node 

		while (true)
		{
			string name = vertex->cityname;
			node* adj = this->start;
			//finding the node to change the parameters
			while (true)
			{
				if (adj->cityname == name)
				{
					break;
				}
				if (adj->adj != NULL)
				{
					adj = adj->adj;
				}
				else
				{
					break;
				}
			}
			double alt = 0;
			//relaxation
			if (adj->d != LONG_MAX)
			{
				alt = source->d + vertex->weight;
				if (adj->d > alt && adj->vcolor != black)
				{
					adj->d = alt;
					adj->parent = source;
				}
			}
			else
			{
				alt = source->d + vertex->weight;
				adj->d = alt;
				adj->parent = source;
			}

			if (vertex->adj != NULL)
			{
				vertex = vertex->adj;
			}
			else
			{
				break;
			}
		}


		source->vcolor = black;

	}

	node* sort = this->start;

	while (true)
	{
		if (sort->cityname == city2)
		{
			break;
		}
		sort = sort->adj;
	}

	return sort->d;

}

void graph::clear()
{
	//change this later 
	this->start = NULL;
	this->list = NULL;
	this->nodes = 0;
	this->edges = 0;

}

void graph::print(string city1, string city2)
{
	//first find the destination city
	node* head = this->start;

	while (true)
	{
		if (head->cityname == city2)
		{
			break;
		}
		if (head->adj != NULL)
		{
			head = head->adj;
		}
		else
		{
			break;
		}
	}

	node* temp = this->start;
	string* array = new string[this->edges];
	//initialize array
	for (int i = 0; i < this->edges; i++)
	{
		array[i] = "none";
	}

	int i = this->edges - 1;

	while (head->parent != NULL)
	{
		array[i] = head->cityname;
		i--;
		head = head->parent;
	}
	array[i] = head->cityname; //adding the final one

	//printing it out
	for (int j = 0; j < this->edges; j++)
	{
		if (array[j] != "none")
		{
			cout << array[j] << " ";
		}
	}

	return;

}

int main()
{
	//declaring variables
	string input;
	string word;
	string city1;
	string city2;
	double distance = 0;
	string name;
	graph Graph;

	while (getline(cin, input))
	{
		//get a whole line
		stringstream eachline(input);

		//get the function 

		getline(eachline, word, ' ');


		if (word == "i")
		{

			//get the second line
			getline(eachline, word, ' ');

			//convert the word to the integer
			name = word;
			bool res;
			res = Graph.search(name);
			if (res)
			{
				cout << "failure" << endl;
			}
			else
			{
				Graph.insert(name);
				cout << "success" << endl;
			}

		}
		else if (word == "s")
		{

			getline(eachline, word, ' ');
			name = word;

			bool result;
			result = Graph.search(name);

			if (result)
			{
				cout << "found " << word << endl;
			}
			else
			{
				cout << "not found" << endl;

			}

		}

		else if (word == "setd")
		{
			getline(eachline, word, ';');
			city1 = word;

			getline(eachline, word, ';');
			city2 = word;

			getline(eachline, word, ' ');
			distance = stod(word);


			bool result1 = Graph.search(city1);
			bool result2 = Graph.search(city2);

			if (result1 || result2)
			{
				Graph.setd(city1, city2, distance);
				cout << "success" << endl;

			}
			else
			{
				cout << "failure" << endl;
			}
		}

		else if (word == "degree")
		{
			getline(eachline, word, ' ');
			name = word;
			bool result1 = Graph.search(name);

			if (result1)
			{
				int result2 = Graph.finddegree(name);
				cout << "degree of " << name << " " << result2 << endl;
			}
			else
			{
				cout << "not found" << endl;
			}

		}

		else if (word == "graph_nodes")
		{
			cout << "number of nodes " << Graph.nodes << endl;
		}

		else if (word == "graph_edges")
		{
			cout << "number of edges " << Graph.edges << endl;
		}

		else if (word == "d")
		{
			getline(eachline, word, ';');
			city1 = word;

			getline(eachline, word, ' ');
			city2 = word;

			bool result1 = Graph.search(city1);
			bool result2 = Graph.search(city2);

			if (result1 || result2)
			{
				double result3 = Graph.distance(city1, city2);
				if (result3 == -1 || result3 == 0)
				{
					cout << "failure" << endl;
				}
				else
				{
					cout << "direct distance " << city1 << " to " << city2 << " " << result3 << endl;
				}
			}
			else
			{
				cout << "failure" << endl;
			}
		}

		else if (word == "shortest_d")
		{
			getline(eachline, word, ';');
			city1 = word;

			getline(eachline, word, ' ');
			city2 = word;

			bool result1 = Graph.search(city1);
			bool result2 = Graph.search(city2);

			if (result1 || result2)
			{
				double result3 = Graph.shortest_distance(city1, city2);
				if (result3 == LONG_MAX)
				{
					cout << "failure" << endl;
				}
				else
				{
					cout << "shortest distance " << city1 << " to " << city2 << " " << result3 << endl;
				}
			}
			else
			{
				cout << "failure" << endl;
			}
		}

		else if (word == "print_path")
		{
			getline(eachline, word, ';');
			city1 = word;

			getline(eachline, word, ' ');
			city2 = word;

			if (Graph.start == NULL)
			{
				cout << " " << endl;
			}
			else
			{
				bool result1 = Graph.search(city1);
				bool result2 = Graph.search(city2);

				if (result1 && result2)
				{
					Graph.print(city1, city2);
					cout << endl;
				}
				else
				{
					cout << " " << endl;
				}
			}
		}
		else if (word == "clear")
		{
			Graph.clear();
			cout << "success" << endl;

		}

	}
	return 0;
}
