//
// Created by user on 3/26/23.
//

#include "Edge.h"


Edge::Edge(Vertex* _start, Vertex* _end, bool _is_directed) {
    start = _start;
    end = _end;
    is_directed = _is_directed;
}


Vertex* Edge::getStart() {
    return start;
}


Vertex* Edge::getEnd() {
    return end;
}


bool Edge::getIsDirected() const {
    return is_directed;
}
