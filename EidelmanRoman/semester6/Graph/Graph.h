#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H


#include <cstdint>
#include <vector>


class Node {
private:
    double value;
public:
    Node(double item) {value = item;};
    ~Node() = default;

    double get_value() {return value;};
    void set_value(double item) {value = item;};
};


class Edge {
private:
    Node* source;
    Node* target;
public:
    Edge(Node* node1, Node* node2);
    ~Edge();

    Node get_source() {return *source;};
    Node get_target() {return *target;};
};


Edge::Edge(Node* previous_node, Node* next_node) {
    source = previous_node;
    target = next_node;
}


Edge::~Edge() {
    source = nullptr;
    target = nullptr;
}


class Graph {
public:
    int8_t items;
    std::vector<Edge> edge_list;

    Graph() = default;
    Graph(Node node1, Node node2);
    ~Graph() = default;

    void add_edge(Node node1, Node node2);
    void delete_edge(Node node1, Node node2);
    void add_node(Node graph_node, Node new_node);
    void delete_node();
    int8_t get_count_of_edges() {return edge_list.size();};
};


void Graph::add_edge(Node node1, Node node2) {
    Node* pnode1 = &node1;
    Node* pnode2 = &node2;
    Edge edge(pnode1, pnode2);
    edge_list.push_back(edge);
}


Graph::Graph(Node node1, Node node2) {
    add_edge(node1, node2);
}


void Graph::add_node(Node graph_node, Node new_node) {
    add_edge(graph_node, new_node);
};

#endif //MR2022_GRAPH_H
