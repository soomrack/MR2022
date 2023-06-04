#include <iostream>
#include "Graph.h"


int main() {

    Graph A;

    A.addVertex(0);
    A.addVertex(1);
    A.addVertex(2);
    A.addVertex(3);
    A.addVertex(4);
    A.addVertex(5);
    A.printVertices();
    A.delVertex(4);
    A.printVertices();
    A.addVertex(4);
    A.printVertices();

    Vertex* v1 = A.find(2);
    Vertex* v2 = A.find(5);

    A.addEdge(v1, v2, true);
    A.addEdge(0, 3, false);
    A.addEdge(2, 1, false);
    A.addEdge(4, 0, false);
    A.addEdge(5, 3, false);
    A.addEdge(1, 4, false);

    std::cout << std::endl;
    A.printEdges();

    A.delEdge(0, 4);
    std::cout << std::endl;
    A.printEdges();

    A.addEdge(1, 4, true);
    A.addEdge(1, 4, true);
    A.addEdge(4, 1, true);
    A.addEdge(1, 4, false);
    A.addEdge(4, 1, false);
    A.addEdge(4, 2, true);
    A.addEdge(4, 0, true);
    A.addEdge(4, 3, true);
    std::cout << std::endl;
    A.printEdges();


    A.delEdge(5, 4);
    //A.delEdge(1, 4);
    A.delEdge(4, 2);
    //A.delEdge(4, 0);
    //A.delEdge(4, 3);
    A.printEdges();

    A.delVertex(0);
    A.printEdges();

/*
    List<int> B;
    B.push(0);
    B.push(1);
    B.push(2);
    B.push(3);
    B.push(4);
    B.push(5);
    B.push(21, 2);
    B.print();
    B.pop();
    B.print();

    ListIterator<int> iter(&B, B[2]);
    iter.find(21);
    iter.pushNext(19);
    B.print();

    B.pop(4);
    B.print();

    iter.find(3);
    iter.pushNext(15);
    B.print();*/

    return 0;
}