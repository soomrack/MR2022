//
// Created by user on 3/26/23.
//

#include "GraphIterator.h"


GraphIterator::GraphIterator(Graph* _graph, Vertex* _vertex) {
    graph = _graph;
    vertex = _vertex;
}


Vertex* GraphIterator::find(int data) {
    auto* node = graph->list.getHead();
    while(node) {
        if (node->getNodeObject()->get() == data) {
            vertex = node->getNodeObject();
            return vertex;
        }
        node = node->getNext();
    }
    vertex = nullptr;
    return nullptr;
}


int GraphIterator::get() {
    return vertex->get();
}


Vertex* GraphIterator::getVertex() {
    return vertex;
}


void GraphIterator::deleteVertex() {
    ListIterator<Vertex*> list_iterator(&graph->list);
    list_iterator.find(vertex);
    list_iterator.popThis();
}


Vertex* GraphIterator::getHead() {
    return graph->list.getHead()->getNodeObject();
}


Vertex* GraphIterator::getTail() {
    return graph->list.getTail()->getNodeObject();
}


void GraphIterator::setHead() {
    vertex = graph->list.getTail()->getNodeObject();
}


void GraphIterator::setTail() {
    vertex = graph->list.getTail()->getNodeObject();
}


void GraphIterator::shiftToHead() {
    if (!vertex) {
        return;
    }

    auto* node = graph->list.getHead();

    while (node) {
        if (node->getNodeObject() == vertex) {
            break;
        }
        node = node->getNext();
    }

    vertex = node->getPrev()->getNodeObject();
}


void GraphIterator::shiftToTail() {
    if (!vertex) {
        return;
    }

    auto* node = graph->list.getHead();

    while (node) {
        if (node->getNodeObject() == vertex) {
            break;
        }
        node = node->getNext();
    }

    if (node->getNext()) {
        vertex = node->getNext()->getNodeObject();
        return;
    }
    vertex = nullptr;
}
