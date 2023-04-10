#ifndef UNTITLED_HEAD_H
#define UNTITLED_HEAD_H

#include "Edge.h"
#include "List.h"

class Edge;

class Head {

public:
    explicit Head(int _data){
        data = _data;
    };

    int data;

    List<Edge *> edge_list;

    int get() const{
        return data;
    };
};

#endif //UNTITLED_HEAD_H
