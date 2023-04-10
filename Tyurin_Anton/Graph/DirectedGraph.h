#ifndef UNTITLED_DIRECTEDGRAPH_H
#define UNTITLED_DIRECTEDGRAPH_H

#include "Head.h"
#include "Edge.h"

class Graph {
    List<Head*> node_list;

    //deleteNode(int *data);

    //deleteEdge(Edge *loc, Edge *dest);

    //findNode(int *data);

public:
    void addNode(int data);

    static int noDestination(Head *dest);

    static void addEdge(Head *loc, Head *dest);

    void addEdge(int loc_data, int dest_data);

    Head *findFromList(unsigned int data);

    Head *findGraphNode(unsigned int findData);
};

#endif //UNTITLED_DIRECTEDGRAPH_H
