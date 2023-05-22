#include "Graph2.h"
int main()
{
    Graph graph;
    graph.add_node(3);
    graph.add_node(7);
    graph.add_node(2);
    graph.add_node(10);
    Iterator<node *> it = graph.nodes.begin();
    node *node1 = *it;
    ++it;
    node *node2 = *it;
    ++it;
    node *node3 = *it;
    ++it;
    node *node4 = *it;
    graph.add_edge(node1, node3);
    graph.add_edge(node2, node1);

    // Print the remaining nodes and their neighbors
    for (auto node : graph.nodes)
    {
        std::cout << "Node " << node->value << " neighbors: ";
        for (auto neighbor : node->neighbors)
        {
            std::cout << neighbor->value << " ";
        }
        std::cout << std::endl;
    }
    graph.removeNode(node3);
    for (auto node : graph.nodes)
    {
        std::cout << "Node " << node->value << " neighbors: ";
        for (auto neighbor : node->neighbors)
        {
            std::cout << neighbor->value << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}