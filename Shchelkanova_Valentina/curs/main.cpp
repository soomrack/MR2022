#include "graph.h"

int main() {
    Graph myGraph;

    myGraph.addVertex(1);
    myGraph.addVertex(2);
    myGraph.addVertex(3);
    myGraph.addVertex(4);

    myGraph.addEdge(1, 2, 10);
    myGraph.addEdge(2, 3, 20);
    myGraph.addEdge(3, 4, 30);
    myGraph.addEdge(4, 1, 40);

    myGraph.display();

    myGraph.removeVertex(3);
    myGraph.removeEdge(4, 1);

    myGraph.display();

    myGraph.fillWithRandom();

    myGraph.display();

    return 0;
}