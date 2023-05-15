#ifndef UNTITLED_GRAPHNODE_H
#define UNTITLED_GRAPHNODE_H

#include "Edge.h"
#include "List.h"

class Edge;

class GraphNode {

public:
    int data;

    List<Edge *> edge_list;

    explicit GraphNode(int _data){
        data = _data;
    };

    int get() const{
        return data;
    };

    bool operator==(const GraphNode* right) const{
        if (this->data == right->data) {return true;}
    return false;
    }

    Edge *findEdge(GraphNode *floc, GraphNode *fdest);
};

#endif //UNTITLED_GRAPHNODE_H
