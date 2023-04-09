#include "DirectedGraph.h"

int main(){
    Graph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(22);
    graph.addEdge(0, 1);
    graph.addEdge(22, 1);
    return 0;
}