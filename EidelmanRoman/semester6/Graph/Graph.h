#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H


#include <cstdint>
#include <vector>
#include "Array.h"


class Edge {
private:
    double* source;
    double* target;
public:
    Edge(double* node1, double* node2);
    ~Edge();

    double get_source() {return *source;};
    double get_target() {return *target;};
};


Edge::Edge(double* previous_node, double* next_node) {
    source = previous_node;
    target = next_node;
}


Edge::~Edge() {
    source = nullptr;
    target = nullptr;
}


class Node {
private:
    double value;
public:
    Node(double item) {value = item;};
    ~Node();

    double get_value() {return value;};
    double set_value(double item) {value = item;};
};


class Graph {
private:

public:
    Graph() = default;
    Graph(Node peak1, Node peak2);
    ~Graph();

    void addEdge(Node peak1, Node peak2);
    void addPeak(double new_item);
    void deletePeak();
};


void Graph::addEdge(Node peak1, Node peak2) {
    auto* edge = new Edge(peak1.pvalue, peak2.pvalue);  //???
}

#endif //MR2022_GRAPH_H
