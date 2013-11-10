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

	Graph(): size(0)
	{}
	Graph(int sz);

	void gen_graph(double edg_d, int dist_r, int sz,bool **,int **);	//function to generate graph
	void print(bool **, int **, int size);
	int V() {return v;}							//return number of vertices
	int E() {return e;}					//return number of edges

private:
	int v;			//number of vertices
	int e;			//number of edges in graph
	int edg_den, dist_rng, size;
};


#endif /* GRAPH_H_ */
