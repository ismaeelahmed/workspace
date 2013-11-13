/*
 * Path.h
 *
 *  Created on: Nov 12, 2013
 *      Author: mavrick
 */
#ifndef PATH_H_
#define PATH_H_

#include "Graph.h"
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
//#include <utility>
//#include <functional>


typedef std::pair<int, std::pair <int, int> > edg;		//edge cost and node name(here name is its location i,j)
typedef std::vector<edg> list;			//list of edges in graph



class Path
{
	private:

	Graph gr;

	std::priority_queue<edg, list, std::greater<edg> > que;

	public:

	void vertices(list);			//list of vertices in Graph
	void path(int u, int w );		//find shortest path between u-w and returns the sequence of
									//vertices representing shortest path u-v1-v2-…-vn-w
	int path_size(int u,int w);		//return the path cost associated with the shortest path

};



#endif /* PATH_H_ */
