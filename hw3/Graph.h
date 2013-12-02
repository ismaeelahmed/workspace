/*
 * Grapgh.h
 *
 *  Created on: Nov 8, 2013
 *      Author: mavrick
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <fstream>

//contains info about each vertex
struct Edge
{
	Edge(int t, int h,double c):tail(t),head(h),cost(c) {}
	int tail;
	int head;
	double cost;
};

//used to traverse the links in shortest path
struct Link
{
	Link():ancestor(-1),cost(0.0){}
	Link(int a, double c):ancestor(a),cost(c){}
	int ancestor;
	double cost;
};

class Graph

{

public:

	Graph(): size(0),edge(0)
	{}
	Graph(int sz);		//constructor with size
	Graph(std::string s);		//constructor that reads from a file

	std::vector<Link> Dijkstra(int start) ;		//shortest Path Algorithm, Dijkstra
	std::pair<int, Graph> Prim_mst(int start) ;		//Minimum Spanning Tree Algorithm, Prim

	void gen_graph(double edg_d, int dist_r);	//function to generate graph
	void print();								//print graph
	void set_V(int sz) {size=sz;}				//set graph size
	int get_V() {return size;}					//return number of vertices
	int get_E() {return edge;}					//return number of edges
	bool adjacent(int x, int y);		//tests whether there is an edge from node x to node y
	std::vector<int> neighbours(int x);				// lists all nodes y such that there is an edge from x to y
	void add_edge(int src,int dst, double cost);		//edge from source to destination and its cost
	int get_node_value(int x);			// returns the value associated with the node x
	double get_edge_value(int x,int y);	// returns the value/cost associated with edge from x to y


private:
	int size;			//number of vertices
	int edge;			//number of edges in graph
	int edge_den, dist_rng;

	bool ** graph;		//edge graph
	double ** cost;		//cost of edges

	std::vector<std::vector<int> > data;		//define 2D vector to hold input graph

	std::vector<std::vector<Edge> > edges;			//vector containing a vector of edges, head tail and cost


};


#endif /* GRAPH_H_ */
