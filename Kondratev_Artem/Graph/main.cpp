#include <iostream>
#include "Graph.h"


int main() {

    Graph A;

    A.createVertex(0);
    A.createVertex(1);
    A.createVertex(2);
    A.createVertex(3);
    A.createVertex(4);
    A.createVertex(5);
    A.getVertices();
    A.deleteVertex(4);
    A.getVertices();
    A.createVertex(4);
    A.getVertices();

    Vertex* v1 = A.find(2);
    Vertex* v2 = A.find(5);

    std::cout << A.createEdge(v1, v2, true) << std::endl;
    std::cout << A.createEdge(0, 3, false) << std::endl;
    std::cout << A.createEdge(2, 1, false) << std::endl;
    std::cout << A.createEdge(4, 0, false) << std::endl;
    std::cout << A.createEdge(5, 3, false) << std::endl;
    std::cout << A.createEdge(1, 4, false) << std::endl;


    std::cout << std::endl;
    A.getEdges();


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