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

    void createVertex(int data);
    bool createEdge(Vertex* from_vertex, Vertex* to_vertex, bool is_bidirectional);
    bool createEdge(int from_data, int to_data, bool is_bidirectional);

    uint64_t getSize() const;

    void getVertices();
    void getEdges();

    Vertex* find(int data);

    void deleteVertex(int data);
    void deleteEdge(Vertex* vertex1, Vertex* vertex2);
    void deleteEdge(int data1, int data2);
};


#endif //HELLO_WORLD_GRAPH_H
