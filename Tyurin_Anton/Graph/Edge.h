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

    GraphNode *getDest() {
        return this->dest;
    }

    GraphNode *getLoc() {
        return this->loc;
    }

    bool operator==(const Edge* right) const{
        if ((this->dest == right->dest) && (this->loc == right->loc)) {return true;}
        return false;
    }
};



#endif //UNTITLED_EDGE_H
