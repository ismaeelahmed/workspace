/*
 * prim_algo.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: mavrick
 */

#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <cassert>
#include <fstream>
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
Graph::Graph(int sz) {

	size=sz;
	data.resize(sz,vector<int>(sz,0));	//initialize 2D vector of dimensions size*size with zeros
}

Graph::Graph(string file) {

	ifstream in(file);							//open file
	in>>size;									//read size of graph as its the first element

	data.resize(size,vector<int>(size,0));		//resize vector according to graph size and initialize with 0's

	int i,j,cost;		//cost from node i to j

	while (!in.eof())	//read file character by character
	{
		in >> i >> j >> cost;		//read from file and write to variables
		add_edge(i,j,cost);			//build graph
	}

/*	for(unsigned int i=0;i<data.size();i++)
	{
		for(unsigned int j=1;j<data.size();j++)
			if(data[i][j] >0 )
				cout<<i<<" "<<j<<" "<<data[i][j]<<endl;
	}
	*/
}
std::vector<int> Graph::neighbours(int node_name)
{
	std::vector<int> neighbour;

	for (int i=0; i< data.size(); i++)
	{
		if(data[node_name][i] > 0)		//if there is an edge between this node and other nodes in graph
		{
			neighbour.push_back(i);		//add this node to neighbours list
		}
	}
	return neighbour;		//return neighbour list
}

void Graph::print()
{
	for(int i=0;i<size;i++)
	{
		for(int j=i;j<size;j++)
		{
			if(data[i][j]>0)
				cout<<i<<" "<<j<<" "<<data[i][j]<<endl;
		}
	}
}
void Graph::add_edge(int src,int dst,double cost)
{
	data[src][dst]=cost;
	data[dst][src]=cost;		//since it is undirected graph
}
bool Graph::adjacent(int x, int y)
{
		//print edge cost from node x to y (cost, x, y)
			if( data[x][y] > 0 )
			{	cout << "Edge exit between "<< x<<" and "<<y;
				return true;
			}
			else
			{	cout << "Edge does not exit between "<< x<<" and "<<y;
				return false;
			}
}

double Graph::get_edge_value(int x, int y)
{
	return data[x][y];
}

std::pair<int,Graph> Graph::Prim_mst(int start)		//Minimum Spanning Tree Algorithm, Prim
{
	std::vector<bool>	is_present_mst(get_V());	//if node is present in minimum spanning tree
	std::vector<int>	min_dist(get_V(),INT_MAX);		//array to hold minimum distance of nodes from mst

	Graph tree = Graph(get_V());		//create a graph to hold minimum spanning tree
	min_dist[start] = 0;	//start node has zero distance from itself
	is_present_mst[0]=true;
	int cost =0;		//total length of mst
	//get neighbors of source in a separate for loop
	for(unsigned int i=1 ;i <= neighbours(0).size();i++)	//or for loop with range "int i: get_neighbors(0)" can be used
	{
		min_dist[i]= get_edge_value(0,i);		//get values already stored in our graph container, namely data[][]
		//cout<<" "<<min_dist[i];
	}
		//now get the node with minimum distance in all nodes (functionality of a priority queue)
		for(int i=0; i<size;i++)
		{
			int index;
			int min_dis = INT_MAX;
			for(int j=0; j<size;j++)
			{
				if(!is_present_mst[j] && min_dist[j] < min_dis)
				{
					index=j;	//index would be the node with minimum distance from source
					min_dis=min_dist[j];
				}
			}
			is_present_mst[index]=true;	//put in mst

			//now find neighbors of index to see which one has shortest distance from mst
			for(int i: neighbours(index))		//now using new for loop(it uses range)
			{
				if(is_present_mst[i] && get_edge_value(i,index) == min_dis)	//if this is the known minimum distance for this node from mst
				{
					tree.add_edge(i,index,min_dis);		//add this edge to mst
					cost+=min_dis;	//add cost to total cost of mst
					break;		//and exit current for loop
				}
			}
			//update nodes that connect to index
			//as index ix now in mst
			//so update their costs from mst
			for(int i: neighbours(index))
			{
				if(!is_present_mst[i] && get_edge_value(i,index) < min_dist[i])	//if this is less than known minimum distance for this node from mst
				{
					min_dist[i]=get_edge_value(i,index);		//update min distance for this node
				}
			}
		}
	std::pair<int,Graph> result(cost,tree);
	return result;
}

int main() {

	Graph mst("HW3_sample_data");	//read graph from file


#ifdef NDEBUG
	const std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	cout << "Debug info :: start time of graph generation "<<endl;
#endif

	std::pair<int, Graph> tree = mst.Prim_mst(0);		//print shortest path using Dijkstra
	cout << "Cost of Graph:: "<< tree.first	<< endl;
	tree.second.print();

#ifdef NDEBUG
	cout << "Debug info :: End time of graph generation "<<endl;
	const std::chrono::time_point<std::chrono::system_clock> stop = std::chrono::system_clock::now();
	const std::chrono::duration<double> duration = stop - start;
	const double total = duration.count();
	cout << "Debug info :: Total time of graph generation "<< total<< endl;
#endif

return 0;
}



