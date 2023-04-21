#ifndef UNTITLED_GRAPHNODE_H
#define UNTITLED_GRAPHNODE_H

#include "Edge.h"
#include "List.h"

class Edge;

class GraphNode {

public:
    explicit GraphNode(int _data){
        data = _data;
    };

    int data;

    List<Edge *> edge_list;

    int get() const{
        return data;
    };

    bool operator==(const GraphNode& right) {
        if (this->data == right.data) {return 1;}
    return 0;
    }


};

#endif //UNTITLED_GRAPHNODE_H
