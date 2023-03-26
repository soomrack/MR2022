//
// Created by user on 3/26/23.
//

#ifndef HELLO_WORLD_VERTEX_H
#define HELLO_WORLD_VERTEX_H


#include <cstdint>
#include "Edge.h"
#include "Graph.h"
#include "List.h"


class Edge;


class Vertex {
    friend class Graph;

private:
    int data;
    uint64_t edges_number;
    List<Edge*> edge_list;

public:
    explicit Vertex(int _data);

    void appendEdge(Edge* edge);
    int get() const;
    uint64_t getEdgesNumber() const;
};


#endif //HELLO_WORLD_VERTEX_H
