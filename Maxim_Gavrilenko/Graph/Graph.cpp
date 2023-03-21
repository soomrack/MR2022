#include "Graph.h"
#include "iostream"
int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 3);
    graph.addEdge(2,3);
    graph.addEdge(1,2);
    std::cout << "DFS traversal starting from vertex 0:" << std::endl;


    return 0;

}