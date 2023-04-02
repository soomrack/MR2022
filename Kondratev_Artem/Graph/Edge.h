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
    bool is_bidirectional;

public:
    Edge(Vertex* _start, Vertex* _end, bool _is_bidirectional);

    Vertex* getStart();
    Vertex* getEnd();
    bool getIsBidirectional() const;
};


#endif //HELLO_WORLD_EDGE_H
