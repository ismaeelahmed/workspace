/*
 * tapio_prim.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: mavrick
 */

/* I give here a simple and straightforward solution to the homework problem using Prim
 algorithm. The implementation of the algorithm is not optimal what reagards to the time
 complexity. It could be improved by e.g. using a heap */

//  Use -std=c++11 to compile.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class graph {
private:
    //Graphs represented as adjaceny matrix. adj[i][j] == 0 means no edge between i and j.
    //Otheriwse adj[i][j] stores the edge cost between i and j.
    vector<vector<int> > adj;
    int node_number;

public:
    //Initialize a graph of size n without edges.
    graph(int n) {
        node_number = n;
        adj.resize(n, vector<int>(n, 0));
    }

    // Reads a graph from a file.
    graph(string filename) {
        int source, target, cost;
        ifstream ifp(filename);
        ifp >> node_number;
        adj.resize(node_number, vector<int>(node_number,0));
        while(ifp >> source >> target >> cost) {
              add_edge(source, target, cost);
        }
    }

    int get_cost(int i, int j) {
        return adj[i][j];
    }

    void add_edge(int source, int target, int cost) {
        adj[source][target] = cost;
        adj[target][source] = cost;
    }

    int get_node_number() {
        return node_number;
    }

    vector<int> get_neighbors(int v) {
        vector<int> neighbors;
        for(int i=0; i<node_number; i++) {
            if(adj[v][i]) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    // Print the graph assuming our graphs are undirected.
    // Every edge is printed only once.
    void print() {
        for(int i=0; i<node_number; i++) {
            for(int j=i; j<node_number; j++) {
                    if(adj[i][j]>0) {
                        cout << i << "\t" << j << "\t" << adj[i][j] << endl;
                    }
            }
        }
    }

    pair<int, graph> prim();
};

//Prim algorithm implemented here. Returns the minimum spanning tree and it's cost.
pair<int, graph> graph::prim() {
    // Stores whether a node already is in a spanning tree.
    vector<bool> mst(node_number);
    // Here is stored what is the minimum distance between the tree and a node outside of the tree.
    vector<int> min_dist(node_number, INT_MAX);
    // This will be the minimum spanning tree itself
    graph tree = graph(node_number);
    // The cost of the tree
    int cost = 0;

    // Start from the graph node 0
    mst[0] = true;
    min_dist[0] = 0;
    for(int i: get_neighbors(0)) {		//get distance of all neighbors
        min_dist[i] = get_cost(0,i);
        cout<<" " << min_dist[i];
    }

    // Then add the rest of the nodes.
    for(int i=0; i<node_number-1; i++ ) {
           // Find the closest vertex outside of the tree. actually find the node with minimum distance from start
           int index;
           int min_distance = INT_MAX;
           for(int j=0; j<node_number; j++) {
                if(!mst[j] && min_dist[j] < min_distance) {
                    index = j;
                    min_distance = min_dist[j];
                }
           }

           //Index is a new vertex in minimum spanning tree.
           mst[index] = true;

           //Find an edge that connects index to the minimum spanning tree.
           for(int i: get_neighbors(index)) {
                if(get_cost(i, index) == min_distance && mst[i]) {	//which node has minimum distance from index
                    tree.add_edge(i, index, min_distance);		//add it to tree that will be returned
                    cost += min_distance;
                    break;
                }
           }
           // Update distances if more than one node connects to index
           for(int i: get_neighbors(index)) {
                if(!mst[i] && get_cost(i, index) < min_dist[i]) {
                    min_dist[i] = get_cost(i, index);
                }
           }
    }
    pair<int, graph> result(cost, tree);

    return result;
};

int main()
{
graph g("HW3_sample_data");
pair<int, graph> p = g.prim();
// the total cost printied will be 30.
cout << "The total cost of the minimum spanning tree is " << p.first << endl << endl;
cout << "The minimum spanning tree in format (vertex,vertex,cost)" << endl << endl;
(p.second).print();

return 0;
}


