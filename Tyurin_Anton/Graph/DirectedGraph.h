#ifndef UNTITLED_DIRECTEDGRAPH_H
#define UNTITLED_DIRECTEDGRAPH_H

#include "GraphNode.h"
#include "Edge.h"

class Graph {
    List<GraphNode*> node_list;

    //deleteNode(int *data);

    //deleteEdge(Edge *loc, Edge *dest);

public:
    void addNode(int data);

    static int noDestination(GraphNode *dest);

    static void addEdge(GraphNode *loc, GraphNode *dest);

    void addEdge(int loc_data, int dest_data);

    GraphNode *findFromList(unsigned int data);

    GraphNode *findGraphNode(unsigned int findData);
};

#endif //UNTITLED_DIRECTEDGRAPH_H
