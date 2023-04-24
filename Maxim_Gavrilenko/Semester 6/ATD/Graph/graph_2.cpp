#include "Graph_2.h"
int main()
{
    Graph<double> graph;
    graph.add_node(3);
    graph.add_node(7);
    graph.add_node(2);
    graph.add_node(10);
    graph.add_edge(10, 3);
    graph.add_edge(2, 7);
    graph.add_edge(3, 7);
    graph.remove_edge(10,3);
    graph.remove_node(10);
    graph.print();
    return 0;
}