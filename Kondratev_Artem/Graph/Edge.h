//
// Created by user on 3/26/23.
//

#ifndef HELLO_WORLD_EDGE_H
#define HELLO_WORLD_EDGE_H


#include "Vertex.h"


class Vertex;


class Edge {
private:
    Vertex* start;
    Vertex* end;
    bool is_directed;

public:
    Edge(Vertex* _start, Vertex* _end, bool _is_directed);

    Vertex* getStart();
    Vertex* getEnd();
    bool getIsDirected() const;
};


#endif //HELLO_WORLD_EDGE_H
