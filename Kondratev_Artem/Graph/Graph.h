//
// Created by user on 3/26/23.
//

#ifndef HELLO_WORLD_GRAPH_H
#define HELLO_WORLD_GRAPH_H


#include <cstdint>
#include "Edge.h"
#include "GraphIterator.h"
#include "List.h"
#include "Vertex.h"


class Vertex;
class Edge;


class Graph {
    friend class GraphIterator;
private:
    uint64_t size;
    List<Vertex*> list;

public:
    Graph();

    void addVertex(int data);
    bool addEdge(Vertex* from_vertex, Vertex* to_vertex, bool is_directed);
    bool addEdge(int from_data, int to_data, bool is_directed);

    uint64_t getVertexNumber() const;

    void printVertices();
    void printEdges();

    Vertex* find(int data);

    void delVertex(int data);
    void delEdge(Vertex* vertex1, Vertex* vertex2);
    void delEdge(int data1, int data2);
};


#endif //HELLO_WORLD_GRAPH_H
