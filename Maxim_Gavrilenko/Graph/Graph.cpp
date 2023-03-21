#include "Graph.h"
int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 3);
    graph.addEdge(2,3);
    graph.addEdge(1,2);
    graph.removeEdge(0,1);
    graph.removeVertex(1);

    return 0;

}