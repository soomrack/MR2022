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
