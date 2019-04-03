#ifndef GRAPH_H
#define GRAPH_H
using namespace std;
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Vertex.h"

using namespace std;

class Graph
{
  private:

  public:
    vector<Vertex*> vertex_list;
    void addVertex(Vertex* v);
    Graph();
};

#endif

/**
* Add an edge connecting vertex <tt>v1</tt> to
* <tt>v2</tt>. The edge must not already be in the
* graph. In an undirected graph, this edge is bidirectional.
* @param v1 The source vertex; must not be
* <tt>null</tt> and must be a vertex in this graph.
* param v2 The destination vertex; must not be
* <tt>null</tt> and must be a vertex in this graph.
* @throws IllegalArgumentException if <tt>v1</tt> or
* <tt>v2</tt> are <tt>null</tt>, are not in this
* graph, or if the edge already exists.
void addEdge( Vertex<T> v1 , Vertex<T> v2 );
*/
