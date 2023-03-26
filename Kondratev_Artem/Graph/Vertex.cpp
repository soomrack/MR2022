//
// Created by user on 3/26/23.
//

#include "Vertex.h"


Vertex::Vertex(int _data) {
    data = _data;
    edges_number = 0;
}


void Vertex::appendEdge(Edge* edge) {
    edge_list.push(edge);
    edges_number++;
}


int Vertex::get() const {
    return data;
}


uint64_t Vertex::getEdgesNumber() const {
    return edges_number;
}


void Vertex::deleteEdge(Vertex* other) {
    if (getEdgesNumber() == 0) {
        return;
    }

    ListIterator<Edge*> list_iterator(&edge_list, edge_list.getHead());
    while (true) {
        if (list_iterator.get()->getStart() == other || list_iterator.get()->getEnd() == other) {
            list_iterator.popThis();
            edges_number--;
            return;
        }
        list_iterator.shiftToTail();
    }
}
