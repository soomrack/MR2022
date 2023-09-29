#ifndef graph_h
#define graph_h
#include <iostream>
#include <vector>
#include <algorithm>


class Node {
public:
    double value;
    std::vector<unsigned int> neighbors;
    explicit Node(double value) : value(value) {};
};


class Graph {
private:
    Node* get_node(int data);
    std::vector<Node*> vnode;

public:
    void add_edge(double valueA, double valueB);
    void add_node(double value);
    void del_edge(double valueA, double valueB);
    void del_node(double value);
    void print();
};


void Graph::add_node(double value) {
    auto *node = new Node(value);
    vnode.push_back(node);
}


void Graph::add_edge(double valueA, double valueB) {
    auto *nodeA = get_node(valueA);
    auto *nodeB = get_node(valueB);
    if (nodeA == nodeB) return;
    nodeA->neighbors.push_back(valueB);
    nodeB->neighbors.push_back(valueA);
}



Node* Graph::get_node(int data) {
    for (int number = 0; number < vnode.size(); number++) {
        if (vnode[number]->value == data) {
            return vnode[number];
        }
    }
    return nullptr;
}


void Graph::del_edge(double data1, double data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    node1->neighbors.erase(std::remove(node1->neighbors.begin(),node1->neighbors.end(), data2), node1->neighbors.end());
    node2->neighbors.erase(std::remove(node2->neighbors.begin(),node2->neighbors.end(), data1), node2->neighbors.end());
}


void Graph::del_node(double value) {
    for (auto it = vnode.begin(); it != vnode.end(); it++) {
        if ((*it)->value == value) {
            Node *nodeRemove = *it;
            vnode.erase(it);
            for (auto neighbour : nodeRemove->neighbors) {
                Node *neighbourNode = get_node(neighbour);
                neighbourNode->neighbors.erase(std::remove(neighbourNode->neighbors.begin(), neighbourNode->neighbors.end(), value), neighbourNode->neighbors.end());
            }
            delete nodeRemove;
            return;
        }
    }
}


void Graph::print() {
    for (int number = 0; number < vnode.size(); number++) {
        Node *node = vnode[number];
        std::cout << node->value << "-> ";
        for (int number = 0; number < node->neighbors.size(); number++) {
            std::cout << node->neighbors[number] << "  ";
        }
        std::cout << std::endl;
    }
}



#endif /* graph_h */
