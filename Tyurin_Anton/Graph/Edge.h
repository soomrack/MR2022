#ifndef UNTITLED_EDGE_H
#define UNTITLED_EDGE_H

#include "Head.h"
class Head;

class Edge{
    Head* loc;
    Head* dest;
public:
    Edge(Head* loc_, Head* dest_);
};

Edge::Edge(Head* loc_, Head* dest_){
    loc = loc_;
    dest = dest_;
}
#endif //UNTITLED_EDGE_H
