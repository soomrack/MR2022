//
// Created by user on 3/26/23.
//

#include "Vertex.h"


Vertex::Vertex(int _data) {
    data = _data;
}


void Vertex::appendEdge(Edge* edge) {
    edge_list.push(edge);
}


int Vertex::get() const {
    return data;
}


uint64_t Vertex::getEdgesNumber() {
    return edge_list.getSize();
}


void Vertex::deleteEdge(Vertex* other) {
    if (getEdgesNumber() == 0) {
        return;
    }

    ListIterator<Edge*> list_iterator(&edge_list, edge_list.getHead());
    while (true) {
        if (list_iterator.get()->getStart() == other || list_iterator.get()->getEnd() == other) {
            list_iterator.popThis();
            return;
        }
        list_iterator.shiftToTail();
    }
}
