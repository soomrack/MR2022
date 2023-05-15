#include <iostream>
#include <vector>


class Node {
public:
    int value;
    std::vector<Node*> edges;

public:
    Node(int new_value) {value = new_value;};
    ~Node() = default;

public:
    void add_edge (Node* neighbour) {edges.push_back(neighbour);};
};


class Graph {
public:
    std::vector<Node> nodes;

public:
    Graph() {} ;
    ~Graph() = default;

public:
    void add_node(int value);
    void delete_node();
};

void Graph::add_node(int value) {
    nodes.push_back(Node(value));
}




int main() {
    Graph graph;
    graph.add_node(22);
    graph.add_node(11);
    graph.nodes[0].add_edge(&graph.nodes[1]);

    std::cout << graph.nodes[0].value << '\n';
    std::cout << graph.nodes[1].value << '\n';
    std::cout << graph.nodes[0].edges[0]->value << '\n';


    return 0;
}
