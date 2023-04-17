#include <iostream>
#include "Graph.h"


int main() {

    Node node1(1);
    Node node2(2);
    Node node3(3);
    Node node4(4);

    Graph graph(node1, node2);
    graph.add_node(node2, node3);
    graph.add_node(node1, node4);
    graph.add_edge(node2, node4);
    std::cout<<graph.get_count_of_edges()<<"\n";



    return 0;
}