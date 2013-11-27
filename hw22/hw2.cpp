//============================================================================
// Name        : hw2.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <cassert>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <utility>
#include "Graph.h"


#define NDEBUG			//for debug info, also disables assert.h

using namespace std;

//calculate probability
double prob() {
	return (static_cast<double>(rand()) / RAND_MAX);
}
//operator for comparison of a link object
bool operator>(Link & r, Link & k) {return r.cost > k.cost;}

//constructor with size
Graph::Graph(int sz):edges(sz) {
	size = sz; //graph size
	edge=0;
	//edges=sz;	//initialize vector of edges

	/*****Adjacency matrix used to represent Graph
	 Adjacency list can also be used in that case however in that case we need to implement it using linked list  ***/

	graph = new bool*[size]; //pointer array pointing to all edges in Graph with 'graph' as base pointer
	cost = new double*[size]; //pointer array pointing to weight of edges thus graph

	//list adj_matrix;		//pair of edge cost and if there exits an edge in Graph

	for (int j = 0; j < size; j++) {
		graph[j] = new bool[size]; //allocate memory for Graph array
		cost[j] = new double[size]; //allocate memory to cost/weight array
	}
}
void Graph::print() {
	ofstream out("random_graph.txt"); //print to file

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (graph[i][j]&&graph[j][i]) //if edge exits here in graph
			{
				cout << i<< ","<<j<<'\t' << cost[i][j] <<endl; //print its cost

				out << cost[i][j] << " "; //output to file
			}
		}
	}
}
bool Graph::adjacent(int x, int y) {
	for (int i = 0; i < adj_matrix.size(); i++) {
			//print edge cost from node x to y (cost, x, y)
			if ((adj_matrix[i].second.first ==x) && (adj_matrix[i].second.second == y))
				if (adj_matrix[i].first==true)
					cout << "Edge exit between 4 and 5";
				else
					cout << "Edge does not exit between 4 and 5";
		}
}

std::vector<Link>	Graph::Dijkstra(int start)
{
	std::vector<Link> short_path(get_V());		//vector containing the shortest path, initialized

	std::vector<bool> closed_set(get_V());		//if vertex is in closed set or not(shortest length from source already determined or not)
	std::vector<int> T;						// names of neighbors/links to current vertex
	T.reserve(get_V());                                   // Reserve place
	/*
	std::priority_queue<Link, std::vector<Link>, std::greater<Link> > queue;		//define queue
	queue.push(li);
*/
	short_path[start]=Link(0,0.0);				//distance of source to itself is zero
	T.push_back(start);				//put the unvisited node name in vector

	while(!T.empty())
	{
		//implement functionality like a priority queue
		//get the smallest element in the shortest path list
		int minimum=0;
		for(std::vector<int>::size_type i=1; i<T.size();++i)
		{
			if(short_path[T[i]].cost < short_path[T[minimum]].cost)		//find the smallest element in list
			{	minimum=i;	}		//make this one minimum
		}

		std::swap(T[minimum],T.back());		//put minimum at end of list
		const int tail=T.back();			//assign last element/vertex in T(minimum) to tail
		T.pop_back();						//remove this from list

		assert(!closed_set[tail]);		//make sure this vertex is not already in closed set
		closed_set[tail]=true;			//  put it in closed set

		//traverse the adjacency list of this vertex, make a pointer
		std::vector<Edge>& edge_pt = edges[tail];		//for tail=0 adjacency list would be first row in matrix edges[][]--> e.g.[0 1 3 4 9 0]

		for(std::vector<Edge>::size_type i =0; i<edge_pt.size(); i++)
		{
			const Edge&  edge = edge_pt[i];
			const double cost_temp =edge.cost;
			const int head = edge.head ;

			if(closed_set[head])		//if this vertex already in closed set quit this iteration and look for next one
			{
				continue;
			}

			const double new_cost = cost_temp + short_path[tail].cost;		//add cost of tail with cost of adjacent vertex = (total cost from source)

			if(short_path[head].ancestor == -1)		//if we have seen this vertex for the first time
			{
				T.push_back(head);			//put it in list containing neighbors, it will be processed in next iterations of main loop
				short_path[head]=Link(tail,new_cost);	//put tail as ancestor of this neighboring vertex and its cost
			}
			else
			{
				if(new_cost < short_path[head].cost)			//if distance to this node from source is smaller than earlier known distance
				{
					short_path[head] = Link(tail,new_cost);	//put tail as ancestor of this neighboring vertex and its cost
				}
			}
		}//end traverse list for
	}//end T while
	return short_path;		//return vector containing shortest path
}

void Graph::gen_graph(double den, int dist_rng) {

	//put edges in graph
	//when we put j=i+1 that means there will be no link to itself (e.g. 1 1, 3 3)
	//when we put j=i that means there will be a link to itself
	//but in that case we make it false here

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				graph[i][j] = false;
				//adj_matrix.push_back(std::make_pair(0,graph[i][j]));		//no edge exists
			} else {
				if (prob() < den) {
					graph[i][j] = graph[j][i] = true; //if probability less than density, put an edge here
					edge++; //increment edge count
				}
			}
		}
	}
	//put costs in edges
	for (int i = 0; i < size; i++) {
		for (int j = i ; j < size; j++) {
			if (graph[i][j]) {
				cost[i][j] = cost[j][i] = prob() * dist_rng; //give weights to edges

				edges[i].push_back(Edge(i,j,cost[i][j]));		//give weights
				edges[j].push_back(Edge(j,i,cost[j][i]));		//both ways as its undirected

//				cout << edges[i][j].tail << "," << edges[i][j].head << " "<< edges[i][j].cost << "   printing through vector  "<< std::endl;
//				cout << edges[j][i].tail << "," << edges[j][i].head << " "<< edges[j][i].cost << "   printing through vector  "<< std::endl;
				//save edge cost between associated nodes(i,j) as a pair into vector
				adj_matrix.push_back(
						std::make_pair(cost[i][j], std::make_pair(i, j)));
				adj_matrix.push_back(
										std::make_pair(cost[j][i], std::make_pair(j, i)));
				//adj_matrix.push_back(
					//		std::make_pair(cost[j][i], std::make_pair(j, i)));
			}
		}
	}
	/*for (int i = 0; i < adj_matrix.size(); i++) {
		//print edge cost from node x to y (cost, x, y)
		cout << adj_matrix[i].first << " " << adj_matrix[i].second.first << ","
				<< adj_matrix[i].second.second << "   printing through vector  "
				<< std::endl;
	}*/
	ofstream out("random_graph.txt"); //print to file
	for (std::vector<std::vector<Edge> >::size_type i = 0; i < edges.size(); ++i)
	{
		for (std::vector<Edge>::size_type j = 0; j < edges[i].size(); ++j)
		{
		//print edge cost from node x to y (cost, x, y)
		cout << edges[i][j].tail << "," << edges[i][j].head << " "<< edges[i][j].cost << "  printing through vector"<< std::endl;
		out << edges[i][j].cost << " "; //output to file

		}
	}

/*	int i,j;
	for ( i = 0; i < size; i++){
			for ( j = i+1 ; j < size; j++){
				cout <<i << "   " << j << "   ";}
	cout <<std::endl;
	}*/
}

int main() {

	srand(time(0)); //seed random number generator
	int size = 50;	//graph size
	double density=0.1;	//density of graph
	int range=15;		//distance range between nodes
	int start_vertex=0;	//start node
	Graph g(size);
	g.gen_graph(density, range);

#ifdef NDEBUG

	cout << "Debug info :: start time of graph generation ";
	//const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	time_t start,end;
	time(&start);
#endif
	cout << "Number of edges in graph :: " << g.get_E()<<endl;

	std::vector<Link> short_path = g.Dijkstra(start_vertex);		//print shortest path using Dijkstra

	double accumulate=0.0;
	int count=0;
	std::vector<Link>& p=short_path;
	for(std::vector<Link>::size_type i=0; i< p.size();++i)
	{
		const double cost = p[i].cost;
		accumulate+=cost;
		++count;
	}
#ifdef NDEBUG
	cout << "Debug info :: End time of graph generation ";
	//const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	time(&end);
	cout << "Debug info :: Total time of graph generation "<< end-start << endl;
#endif
	cout << "Average shortest path:: " << accumulate/count << endl;

	return 0;
}
