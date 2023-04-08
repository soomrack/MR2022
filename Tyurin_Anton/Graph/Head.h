
#ifndef UNTITLED_HEAD_H
#define UNTITLED_HEAD_H


#include "Edge.h"
#include "List.h"


class Edge;


class Head{
    int data;
    List<Edge*> edge_list;

public:
    explicit Head(int _data);
};


Head::Head(int _data) {
    data = _data;
}


#endif //UNTITLED_HEAD_H
