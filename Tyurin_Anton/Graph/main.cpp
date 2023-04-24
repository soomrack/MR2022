#include "DirectedGraph.h"

int main() {
    Graph graph;

    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(22);

    graph.addEdge(0, 1);
    graph.addEdge(0, 22);

    graph.deleteNode(0);
    //graph.deleteNode(1);
    graph.deleteNode(22);
    if (graph.node_list.is_empty()){std::cout << "no Nodes";}
    //if (graph.findGraphNode(1)->edge_list.is_empty()) { std::cout << "no Location " << std::endl;}
    //std::cout << "Destinstion " << graph.findGraphNode(1)->edge_list.getHead()->getNodeData()->getDest()->get();
    return 0;
}