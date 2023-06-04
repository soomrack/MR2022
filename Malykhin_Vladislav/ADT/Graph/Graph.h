#ifndef GRAPH_H
#define GRAPH_H


#include "DArray.h"

class DArray;
class Node {
protected:
    double data;
    DArray links;
   // unsigned int links_count;
public:
    Node(double data);
    ~Node();
    void print();
    void add_link(Node *node_link);
    Node * get_link(unsigned int idx);
    double get_data();
    unsigned int get_links_count();
};



/*
class Iterator {
public:
    Node *ptr;
    Iterator();
    ~Iterator();
    void go(int idx);
    void set(Node *in_node);
    double get_data();
};
*/



class Graph{
protected:
    DArray nodes;
public:
    Graph();
    ~Graph();

    void add_node(double in_data);
    void add_link(Node * start_node, Node * finish_node);
    void print();
    Node * get_node(unsigned int idx);
};


Node::Node(double new_data){
    data = new_data;
    links = DArray();
   // links_count = 0;
}


Node::~Node() = default;


void Node::print() {
    std::cout << "data:" << data << "; ";
    if(get_links_count() > 0) {
        for (int idx = 0; idx < get_links_count(); idx++) {
            std::cout << "link" << idx + 1 << ":" << links[idx]->data << "; ";
        }
        std::cout << "\n";
        return;
    }
    std::cout << "there is no links.\n";
}


void Node::add_link(Node *node_link) {
    //++links_count;
    links.resize(get_links_count() + 1);
    links[get_links_count() - 1] = node_link;
}


Node * Node::get_link(unsigned int idx) {
    return links[idx];
}


double  Node::get_data() {
    return data;
}


unsigned int Node::get_links_count(){
    return links.get_size();
};



/*Iterator::Iterator() = default;



Iterator::~Iterator() = default;


double Iterator::get_data() {
    return ptr->get_data();
}


void Iterator::set(Node *in_node) {
    ptr = in_node;
}


void Iterator::go(int idx) {
    ptr = ptr->get_link(idx);
}
*/


Graph::Graph() {
    nodes = DArray();
}


void Graph::add_node(double in_data) {
    Node * new_node = new Node(in_data);
    nodes.resize(nodes.get_size() + 1);
    nodes[nodes.get_size() - 1] = new_node;
}

void Graph::add_link(Node *start_node, Node *finish_node) {
   // bool collision = false;  // проверка на коллизию путей
    for(unsigned int idx = 0; idx < start_node->get_links_count(); ++idx)
        if (start_node->get_link(idx) == finish_node) return;//collision = true;
    start_node->add_link(finish_node);
}

Graph::~Graph() = default;

void Graph::print() {
    for(unsigned int idx = 0; idx < nodes.get_size(); ++idx){
        std::cout << "node" << idx <<":" << nodes[idx]->get_data() <<"; ";
    }
    std::cout << "\n";
}

Node *Graph::get_node(unsigned int idx) {
    return nodes[idx];
}

#endif //GRAPH_H
