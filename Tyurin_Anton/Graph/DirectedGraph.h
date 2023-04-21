#ifndef UNTITLED_DIRECTEDGRAPH_H
#define UNTITLED_DIRECTEDGRAPH_H

#include "GraphNode.h"
#include "Edge.h"

class Graph {

public:
    void addNode(int data);

    static int noDestination(GraphNode *dest);

    static void addEdge(GraphNode *loc, GraphNode *dest);

    void addEdge(int loc_data, int dest_data);

    GraphNode *findGraphNode(unsigned int findData);

    void deleteNode(int data);

    //void deleteEdge(GraphNode *loc, GraphNode *dest);

    //void deleteEdge(int loc_data, int dest_data);

    List<GraphNode *> node_list;
};

#endif //UNTITLED_DIRECTEDGRAPH_H
