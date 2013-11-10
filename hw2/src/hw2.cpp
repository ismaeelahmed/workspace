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

Graph::Graph(int size)
{

}
void Graph::print(bool **g, int **co, int size)
{
	ofstream out("random_graph.txt");

	for(int i=0;i<size;i++ )
		{
			for(int j=0;j<size;j++)
			{
				if(g[i][j])	//if edge exits here in graph
				{
					cout<<co[i][j]<< " ";	//print its cost

					out<< co[i][j]<< " ";
				}
			}
		}
}
void Graph::gen_graph(double den, int dist_rng, int size, bool **graph,int ** cost )
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
				graph[i][j]=graph[j][i]=(prob()<den);	//if probability less than density, put an edge here
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

int main() {

	Graph g;
		srand(time(0)); //seed random number generator
		//cout<< prob()<<endl;
		int size = 15;
		double density;
		int range;

		cout << "Enter size of Graph : ";
		cin >> size;
		cout << "Enter density : ";
		cin >> density;
		cout << "Enter max range of Distance (between 1 and 30): ";
		cin >> range;

		bool ** graph;
		int ** cost;
		graph= new bool*[size];
		cost= new int*[size];
		for(int j=0;j<size;j++)
		{
			graph[j]=new bool[size];
			cost[j]=new int[size];
			// cout<<cost[j]<< " ";	//print its cost
		}

	g.gen_graph(density,range,size,graph,cost);
	g.print(graph,cost,size);



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
