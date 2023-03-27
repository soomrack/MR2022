//
// Created by user on 3/26/23.
//

#ifndef HELLO_WORLD_GRAPHITERATOR_H
#define HELLO_WORLD_GRAPHITERATOR_H


#include "Graph.h"


class Graph;
class Vertex;


class GraphIterator {
private:
    Graph* graph;
    Vertex* vertex;

public:
    explicit GraphIterator(Graph* _graph, Vertex* _vertex=nullptr);
    Vertex* find(int data);
    int get();
    Vertex* getVertex();
    void deleteVertex();
    Vertex* getHead();
    Vertex* getTail();
    void setHead();
    void setTail();
    void shiftToHead();
    void shiftToTail();
};


#endif //HELLO_WORLD_GRAPHITERATOR_H
