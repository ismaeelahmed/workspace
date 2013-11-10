/*
 * Grapgh.h
 *
 *  Created on: Nov 8, 2013
 *      Author: mavrick
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph

{

public:

	Graph(): size(0),edge(0)
	{}
	Graph(int sz);		//constructor with size

	void gen_graph(double edg_d, int dist_r);	//function to generate graph
	void print();
	void set_V(int sz) {size=sz;}				//set graph size
	int get_V() {return size;}					//return number of vertices
	int get_E() {return edge;}					//return number of edges
	bool adjacent(Graph *, int x, int y);		//tests whether there is an edge from node x to node y
	int neighbour(Graph *, int x);				// lists all nodes y such that there is an edge from x to y
	int get_node_value(Graph *,int x);			// returns the value associated with the node x
	int get_edge_value( Graph *,int x,int y);	// returns the value/cost associated to the edge (x,y)

private:
	int size;			//number of vertices
	int edge;			//number of edges in graph
	int edge_den, dist_rng;

	bool ** graph;
	int ** cost;
};


#endif /* GRAPH_H_ */
