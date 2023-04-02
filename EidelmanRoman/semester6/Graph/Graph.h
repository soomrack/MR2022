#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H


#include <cstdint>
#include <vector>
#include "Array.h"


class Edge {
private:
    double* previous_peak;
    double* next_peak;
public:
    Edge(double* previous_address, double* next_address);
    ~Edge();

    double* getPreviousPeak() {return previous_peak;};
    double* getNextPeak() {return next_peak;};
};


Edge::Edge(double* previous_address, double* next_address) {
    previous_peak = previous_address;
    next_peak = next_address;
}


Edge::~Edge() {
    previous_peak = nullptr;
    next_peak = nullptr;
}


class Peak {
public:
    double value;
    double* pvalue;
    Peak(double item);
    ~Peak();

    double getValue() {return value;}
    double* getAddress() {return pvalue;}
};


Peak::Peak(double item) {
    value = item;
    pvalue = new double[1];
    pvalue[1] = value;  //?
}


Peak::~Peak() {
    delete[] pvalue;
}


class Graph {
private:
    uint8_t peaks = 2;
    Array edges();
    void addEdge(Peak peak1, Peak peak2);
public:
    Graph() = default;
    Graph(Peak peak1, Peak peak2);
    ~Graph();

    void addPeak(double new_item);
    void deletePeak();
};


void Graph::addEdge(Peak peak1, Peak peak2) {
    auto* edge = new Edge(peak1.pvalue, peak2.pvalue);  //???
}

#endif //MR2022_GRAPH_H
