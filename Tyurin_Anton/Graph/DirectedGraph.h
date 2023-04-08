#ifndef UNTITLED_DIRECTEDGRAPH_H
#define UNTITLED_DIRECTEDGRAPH_H

#include "List.h"
#include "Head.h"
#include "Edge.h"

class Edge;
class Head;

class Graph {
    List<Head *> node_list;

    //deleteNode(int *data);

    //deleteEdge(Edge *loc, Edge *dest);

    //findNode(int *data);

public:
    void addNode(int data);

    int noDestination(Head *dest);

    void addEdge(Head *loc, Head *dest);

    void addEdge(int loc_data, int dest_data);

    Head *findFromList(int data);
};

#endif //UNTITLED_DIRECTEDGRAPH_H
