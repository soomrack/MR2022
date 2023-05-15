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
        List<int>* edges;
    };
    map<int, Vertex*> graph;

public:
    Graph();
    void addVertex(int value);
    void addEdge(int v1, int v2, int weight);
    void removeVertex(int value);
    void removeEdge(int v1, int v2);
    void display();
    void fillWithRandom();
    int getSize();
    List<int>*  getList(int value);
    int searchElementWeight(int v);
    void primAlgorithm();
    void kruskalAlgorithm();
};


Graph::Graph() {}

void Graph::addVertex(int value) {
    if (graph.find(value) != graph.end()) {
        return;
    }
    Vertex* vertex = new Vertex;
    vertex->data = value;
    vertex->edges = new List<int>;
    graph[value] = vertex;
}

void Graph::addEdge(int v1, int v2, int weight) {
    if (graph.find(v1) == graph.end() || graph.find(v2) == graph.end()) {
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
    for (auto& element : graph) {
        element.second->edges->delete_position(vertex->data);
    }
    graph.erase(value);
    delete vertex->edges;
    delete vertex;
}

void Graph::removeEdge(int v1, int v2) {
    if (graph.find(v1) == graph.end() || graph.find(v2) == graph.end()) {
        return;
    }
    graph[v1]->edges->delete_position(v2);
    graph[v2]->edges->delete_position(v1);
}

void Graph::display() {
    for (const auto& element : graph) {
        cout << element.first << " -> ";
        element.second->edges->display();
        cout << endl;
    }
}

int Graph::getSize() {
    return graph.size();
}

List<int>* Graph::getList(int value) {
    if (graph.find(value) == graph.end()) {
        return nullptr;
    }
    return graph[value]->edges;
}

int Graph::searchElementWeight(int v) {
    List<int>* edges = getList(v);
    if (edges == nullptr) {
        return -1;
    }
    for (int i = 1; i <= edges->get_size(); i++) {
        if (edges->get_element(i) == v) {
            return edges->get_element(i + 1);
        }
    }
    return -1;
}

void Graph::primAlgorithm() {
    if (graph.empty()) {
        return;
    }
    int startVertex = graph.begin()->first;
    List<int> parent;
    parent.createList(getSize(), -1);
    List<bool> visited;
    visited.createList(getSize(), false);
    List<int> distance;
    distance.createList(getSize(), INT_MAX);

    parent.change_element(startVertex, -1);
    distance.change_element(startVertex, 0);
    visited.change_element(startVertex, true);

    for (int i = 0; i < getSize(); i++) {
        int currentVertex = -1;
        int minDistance = INT_MAX;
        for (const auto& element : graph) {
            int v = element.first;
            if (!visited.get_element(v) && distance.get_element(v) < minDistance) {
                currentVertex = v;
                minDistance = distance.get_element(v);
            }
        }

        if (currentVertex == -1) {
            break;
        }

        visited.change_element(currentVertex, true);

        List<int>* edges = getList(currentVertex);
        for (int j = 1; j <= edges->get_size(); j += 2) {
            int v = edges->get_element(j);
            int weight = edges->get_element(j + 1);
            if (!visited.get_element(v) && weight < distance.get_element(v)) {
                parent.change_element(v, currentVertex);
                distance.change_element(v, weight);
            }
        }
    }

    for (const auto& element : graph) {
        int v = element.first;
        int p = parent.get_element(v);
        //if (p != -1) {
            cout << v << " - " << p << "\tweight: " << distance.get_element(v) << endl;
       // }
    }
}

void Graph::kruskalAlgorithm() {
    if (graph.empty()) {
        return;
    }

    // create Disjoint-Set
    map<int, int> sets;
    for (const auto& element : graph) {
        sets[element.first] = element.first;
    }

    // create sorted edges list
    vector<pair<int, pair<int, int>>> edges;
    for (const auto& element : graph) {
        int source = element.first;
        for (int i = 1; i <= element.second->edges->get_size(); i += 2) {
            int dest = element.second->edges->get_element(i);
            int weight = element.second->edges->get_element(i + 1);
            if (source < dest) {
                edges.push_back({ weight, { source, dest } });
            }
        }
    }
    sort(edges.begin(), edges.end());

    // find MST
    Graph mst;
    for (const auto& e : edges) {
        int weight = e.first;
        int source = e.second.first;
        int dest = e.second.second;

        if (sets[source] != sets[dest]) {
            // add to MST
            mst.addVertex(source);
            mst.addVertex(dest);
            mst.addEdge(source, dest, weight);

            // merge sets
            int oldSet = sets[dest];
            int newSet = sets[source];
            for (auto& s : sets) {
                if (s.second == oldSet) {
                    s.second = newSet;
                }
            }
        }
    }

    // display MST
    mst.display();
}
#endif  // graph_h
