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
#include <fstream>
#include <queue>
#include <stdlib.h>
#include "Graph.h"
#include "Path.h"
using namespace std;

double prob() {
	return (static_cast<double>(rand()) / RAND_MAX);
}


//constructor with size
Graph::Graph(int sz):edges(sz) {
	size = sz; //graph size
	edge=0;
	//edges=sz;	//initialize vector of edges

	/*****Adjacency matrix used to represent Graph
	 Adjacency list can also be used in that case however in that case we need to implement it using linked list  ***/

	graph = new bool*[size]; //pointer array pointing to all edges in Graph with 'graph' as base pointer
	cost = new int*[size]; //pointer array pointing to weight of edges thus graph

	//list adj_matrix;		//pair of edge cost and if there exits an edge in Graph

	for (int j = 0; j < size; j++) {
		graph[j] = new bool[size]; //allocate memory for Graph array
		cost[j] = new int[size]; //allocate memory to cost/weight array

		//cout<<*cost[j]<< " "<<endl;	//what is cost now
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
void Graph::gen_graph(double den, int dist_rng) {

	//put edges in graph
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
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
	cout<< "number of edges "<<edges.size()<<endl;
	//const std::vector<std::vector<Edge> >& incident_edges =edges;
	for (std::vector<std::vector<Edge> >::size_type i = 0; i < edges.size(); ++i) {
		for (std::vector<Edge>::size_type j = 0; j < edges[i].size(); ++j){
			//print edge cost from node x to y (cost, x, y)
		cout << edges[i][j].tail << "," << edges[i][j].head << " "
							<< edges[i][j].cost << "   printing through vector  "
							<< std::endl;
		}
		}

}

int main() {

	srand(time(0)); //seed random number generator
	int size = 5;
	double density=0.1;
	int range=15;

	//cout << "Enter size of Graph : ";
	//cin >> size;
	//g.set_V(size);			//set value in graph object
	//cout << "Enter density : ";
	//cin >> density;
	//cout << "Enter max range of Distance (between 1 and 30): ";
	//cin >> range;
	Graph g(size);
	g.gen_graph(density, range);

	cout << "Number of edges in graph :: " << g.get_E()<<endl;
	cout << "If there is an Edge between node 4 and 5" << endl;
	//Priority Queue
	g.adjacent(4,5);	//if there exist an edge from node 8 to 9
	//int PriorityQueue
	g.print(); //print graph

	/*
	 int size = 15;
	 double density;
	 cout << "graph size?" << endl;
	 cin >> size;
	 cout << "graph density (0, 1)?" << endl;
	 cin >> density;
	 bool** graph;
	 int** color;
	 int** cost;

	 graph = new bool*[size];
	 color = new int*[size];
	 cost = new int*[size];
	 for (int i = 0; i < size; ++i) {
	 graph[i] = new bool[size];
	 color[i] = new int[size];
	 cost[i] = new int[size];
	 }
	 for (int i = 0; i < size; ++i) //generate undirected edges
	 for (int j = i; j < size; ++j)
	 if (i == j)
	 graph[i][j] = false; //no loops
	 else graph[i][j] = graph[j][i] = (prob() < density);
	 */

	/*				for (int i = 0; i < size; ++i) //generate costs and color
	 for (int j = i; j < size; ++j)
	 if (graph[i][j]) {
	 color[i][j] = color[j][i] = rand() % 3;
	 cost[i][j] = cost[j][i] = prob() * 30;
	 }
	 */
	/*
	 ofstream outp("graph_data.txt");
	 outp << size << "\n";
	 for (int i = 0; i < size; ++i)
	 for (int j = 0; j < size; ++j) {
	 if (graph[i][j])
	 outp << i << '\t' << j << '\t' << cost[i][j] << '\t'
	 << color[i][j] << '\t';
	 }
	 */
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
