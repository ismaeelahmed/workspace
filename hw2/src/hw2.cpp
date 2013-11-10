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
#include <stdlib.h>
#include "Graph.h"
using namespace std;

double prob() {
	return (static_cast<double>(rand()) / RAND_MAX);
}

//constructor with size and
Graph::Graph(int sz)
{
	size=sz;			//graph size

	//Adjacency matrix used to represent Graph
	//Adjacency list can also be used in that case we need to implement it using linked list

	graph= new bool*[size];	//pointer array pointing to all nodes in Graph with 'graph' as base pointer
	cost= new int*[size];	//pointer array pointing to weight of edges thus graph
	for(int j=0;j<size;j++)
	{
		graph[j]=new bool[size];	//allocate memory for Graph array
		cost[j]=new int[size];		//allocate memory to cost/weight array
		//cout<<*cost[j]<< " "<<endl;	//what is cost now
	}
}
void Graph::print()
{
	ofstream out("random_graph.txt");		//print to file

	for(int i=0;i<size;i++ )
		{
			for(int j=0;j<size;j++)
			{
				if(graph[i][j])	//if edge exits here in graph
				{
					cout<<cost[i][j]<< " ";	//print its cost

					out<< cost[i][j]<< " ";
				}
			}
		}
}
void Graph::gen_graph(double den, int dist_rng)
{

	//put edges in graph
	for(int i=0;i<size;i++ )
	{
		for(int j=0;j<size;j++)
		{
			if(i==j)
			{
				graph[i][j]=false;
			}
			else
			{
				if (prob()<den)
				{
				graph[i][j]=graph[j][i]=true;	//if probability less than density, put an edge here
				edge++;			//increment edge count
				}
			}
		}
	}
	//put costs in edges
	for(int i=0;i<size;i++ )
	{
		for(int j=0;j<size;j++)
		{
			if(graph[i][j])
			{
				cost[i][j]=cost[j][i]=prob()*dist_rng;	//give weights to edges
			}
		}
	}

}
bool Graph::adjacent(Graph *g, int x, int y)
{

	return (true);
}

int main() {


		srand(time(0)); //seed random number generator
		int size = 15;
		double density;
		int range;

		cout << "Enter size of Graph : ";
		cin >> size;
		//g.set_V(size);			//set value in graph object
		cout << "Enter density : ";
		cin >> density;
		cout << "Enter max range of Distance (between 1 and 30): ";
		cin >> range;
		Graph g(size);

	g.gen_graph(density,range);
	g.print();



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
