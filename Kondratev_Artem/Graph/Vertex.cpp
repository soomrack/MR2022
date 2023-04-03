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


Edge* Vertex::findEdge(Vertex* other) {
    if (edge_list.isEmpty()) {
        return nullptr;
    }

    ListIterator<Edge*> list_iterator(&edge_list, edge_list.getHead());
    while(list_iterator.getIterator()) {  //  delete true
        if (list_iterator.get()->getStart() == other || list_iterator.get()->getEnd() == other) {
            return list_iterator.get();
        }
        list_iterator.shiftToTail();
    }
    return nullptr;
}


void Vertex::delEdge(Vertex* other) {
    Edge* edge = findEdge(other);

    if (edge == nullptr) {
        return;
    }

    ListIterator<Edge*> iter(&edge_list, edge);
    iter.popThis();


    /*
    if (edge_list.isEmpty()) {
        return;
    }

    ListIterator<Edge*> list_iterator(&edge_list, edge_list.getHead());
    while(list_iterator.getIterator()) {  //  delete true
        if (list_iterator.get()->getStart() == other || list_iterator.get()->getEnd() == other) {
            list_iterator.popThis();
            return;
        }
        list_iterator.shiftToTail();
    }*/
}
