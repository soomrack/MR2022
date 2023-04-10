#ifndef UNTITLED_EDGE_H
#define UNTITLED_EDGE_H


#include "GraphNode.h"


class GraphNode;

class Edge{
    GraphNode* loc;
    GraphNode* dest;
public:
    Edge(GraphNode* loc_, GraphNode* dest_){
        loc = loc_;
        dest = dest_;
    };
};



#endif //UNTITLED_EDGE_H
