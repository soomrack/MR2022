#include <iostream>
#include "algorithm"
#include "Dynamic_Array.h"


const int MAX_COUNT = 999999;



class Node {

public:
    unsigned int value;

    Dynamic_array<Node*> neighbors;
    Dynamic_array<int> weights;



public:

    Node();
    Node(const unsigned int x);
    Node(const Node& x);

    Node& operator=(const Node& x);
    friend bool operator== (const Node &x, const Node &y);


    void push_next(Node* x);
    void push_prev(Node* x);

    Node* next();
    Node* prev();


};


class Graph {

private:
    Dynamic_array<Node> vertexs;


public:

    void add_node(const unsigned int new_name);
    void add_path(const unsigned int from, const unsigned int to, const int cost, const bool add_reverse = false);

    bool contains(const unsigned int node_name);

    void output();


private:

    Node* get(const unsigned int node_name);

};


Node::Node() {
    value = 0;
    neighbors = Dynamic_array<Node*>();
    weights = Dynamic_array<int>();
}


Node::Node(const unsigned int x) {
    value = x;
    neighbors = Dynamic_array<Node*>();
    weights = Dynamic_array<int>();
}


Node::Node(const Node &x) {
    value = x.value;
    neighbors = x.neighbors;
    weights = x.weights;
}


Node& Node::operator=(const Node &x) {
    value = x.value;
    neighbors = x.neighbors;
    weights = x.weights;
    return *this;
}


bool operator==(const Node &x, const Node &y) {
    if (x.value == y.value) return true;
    return false;
}


void Graph::add_node(const unsigned int new_name) {
    vertexs.push_back(Node(new_name));
}


void Graph::add_path(const unsigned int from, const unsigned int to, const int cost, const bool add_reverse) {
    if (!contains(from)) add_node(from);
    if (!contains(to)) add_node(to);

    Node* node_from = get(from);
    Node* node_to = get(to);

    unsigned int pos_of_to = node_from->neighbors.position(node_to);
    if (pos_of_to == 0) {
        node_from->neighbors.push_back(node_to);
        node_from->weights.push_back(cost);
    } else {
        node_from->weights[pos_of_to - 1] = std::min(node_from->weights[pos_of_to - 1], cost);
    }

    if (add_reverse){
        add_path(to, from, cost, false);
    }

}


bool Graph::contains(const unsigned int node_name) {
    if (vertexs.length() == 0) return false;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return true;
    }
    return false;
}


void Graph::output() {
    if (vertexs.length() == 0) {
        std::cout << "There is no elements in this graph\n\n";
        return;
    }

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        std::cout << vertexs[idx].value << "   [";

        if (vertexs[idx].neighbors.length() != 0){
            for (unsigned int jdx = 0; jdx < vertexs[idx].neighbors.length(); jdx++){
                std::cout << " " << vertexs[idx].neighbors[jdx]->value << "{" << vertexs[idx].weights[jdx] << "} ";
            }
        }

        std::cout << "]\n";
    }
    std::cout << "\n";
}


Node* Graph::get(const unsigned int node_name) {
    if (!contains(node_name)) return nullptr;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return &vertexs[idx];
    }

    return nullptr;
}



int main() {

    Graph A;
    A.add_node(5);
    A.add_node(4);

    A.add_path(2, 3, 6);
    A.add_path(3, 5, 1);

    A.output();

    A.add_path(3, 2, 5, true);
    A.output();


    return 0;
}