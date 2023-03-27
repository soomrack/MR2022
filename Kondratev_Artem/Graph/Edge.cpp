//
// Created by user on 3/26/23.
//

#include "Edge.h"


Edge::Edge(Vertex* _start, Vertex* _end, bool _is_bidirectional) {
    start = _start;
    end = _end;
    is_bidirectional = _is_bidirectional;
}


Vertex* Edge::getStart() {
    return start;
}


Vertex* Edge::getEnd() {
    return end;
}


bool Edge::getIsBidirectional() const {
    return is_bidirectional;
}
