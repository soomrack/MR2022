#ifndef graph_h
#define graph_h

#include <iostream>
#include <vector>
#include <map>
#include "list_h.h"

using namespace std;

class Graph {
private:
    struct Vertex {
        int data;
        List* edges;
    };
    std::map<int, Vertex*> graph;

public:
    Graph();
    void addVertex(int value);
    void addEdge(int v1, int v2, int weight);
    void removeVertex(int value);
    void removeEdge(int v1, int v2);
    void display();
    void fillWithRandom();
};

Graph::Graph() {}

void Graph::addVertex(int value) {
    if (graph.find(value) != graph.end()) {
        return;
    }
    Vertex* vertex = new Vertex;
    vertex->data = value;
    vertex->edges = new List;
    graph[value] = vertex;
}

void Graph::addEdge(int v1, int v2, int weight) {
    if (graph.find(v1) == graph.end()) {
        return;
    }
    if (graph.find(v2) == graph.end()) {
        return;
    }
    graph[v1]->edges->push_tail(v2);
    graph[v2]->edges->push_tail(v1);
}

void Graph::removeVertex(int value) {
    if (graph.find(value) == graph.end()) {
        return;
    }
    Vertex* vertex = graph[value];
    for (std::pair<int, Vertex*> element : graph) {
        element.second->edges->delete_position(element.second->edges->searchElementPosition(vertex->data));
    }
    graph.erase(value);
    delete vertex->edges;
    delete vertex;
}

void Graph::removeEdge(int v1, int v2) {
    if (graph.find(v1) == graph.end()) {
        return;
    }
    if (graph.find(v2) == graph.end()) {
        return;
    }
    graph[v1]->edges->delete_position(graph[v1]->edges->searchElementPosition(v2));
    graph[v2]->edges->delete_position(graph[v2]->edges->searchElementPosition(v1));
}

void Graph::display() {
    for (std::pair<int, Vertex*> element : graph) {
        cout << element.first << " -> ";
        element.second->edges->display();
        cout << endl;
    }
}

void Graph::fillWithRandom() {
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int v1 = rand() % 20;
        int v2 = rand() % 20;
        int weight = rand() % 100;
        addVertex(v1);
        addVertex(v2);
        addEdge(v1, v2, weight);
    }
}

#endif  // graph_h