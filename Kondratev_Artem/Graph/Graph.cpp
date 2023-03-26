//
// Created by user on 3/26/23.
//

#include "Graph.h"


Graph::Graph() {
    size = 0;
}


void Graph::createVertex(int data) {
    auto* vertex = new Vertex(data);
    list.push(vertex);
    size++;
}


bool Graph::createEdge(Vertex* from_vertex, Vertex* to_vertex, bool is_bidirectional) {
    if (!from_vertex || !to_vertex) {
        return false;
    }

    auto* edge = new Edge(from_vertex, to_vertex, is_bidirectional);
    from_vertex->appendEdge(edge);
    to_vertex->appendEdge(edge);
    return true;
}


bool Graph::createEdge(int from_data, int to_data, bool is_bidirectional) {
    Vertex* from_vertex = GraphIterator(this).find(from_data);
    Vertex* to_vertex = GraphIterator(this).find(to_data);

    if (!from_vertex || !to_vertex) {
        return false;
    }

    return createEdge(from_vertex, to_vertex, is_bidirectional);
}


uint64_t Graph::getSize() const {
    return size;
}


void Graph::getVertices() {
    auto* node = list.getHead();
    while (node != list.getTail()) {
        std::cout << node->getNodeObject()->get() << ", ";
        node = node->getNext();
    }
    std::cout << node->getNodeObject()->get() << std::endl;
}


void Graph::getEdges() {
    GraphIterator iterator(this, list.getHead()->getNodeObject());

    while (iterator.getVertex()) {
        auto* vertex = iterator.getVertex();
        std::cout << vertex->get() << " : " << std::endl;

        ListIterator<Edge*> edge_iterator(&vertex->edge_list, vertex->edge_list.getHead());
        for (int i = 0; i < vertex->edge_list.getSize(); i++) {
            std::cout << "    " << edge_iterator.get()->getStart()->get();
            (edge_iterator.get()->getIsBidirectional()) ? std::cout << " <--> " : std::cout << "  --> ";
            std::cout << edge_iterator.get()->getEnd()->get() << std::endl;
            edge_iterator.shiftToTail();
        }
        iterator.shiftToTail();
    }
}


Vertex* Graph::find(int data) {
    return GraphIterator(this).find(data);
}


void Graph::deleteVertex(int data) {
    GraphIterator iterator(this);

    if (iterator.find(data) == nullptr) {
        return;
    }

    iterator.deleteVertex();
}


void Graph::deleteEdge(Vertex* vertex1, Vertex* vertex2) {
    if (!vertex1 || !vertex2) {
        return;
    }

    vertex1->deleteEdge(vertex2);
    vertex2->deleteEdge(vertex1);
}


void Graph::deleteEdge(int data1, int data2) {
    Vertex* vertex1 = GraphIterator(this).find(data1);
    Vertex* vertex2 = GraphIterator(this).find(data2);

    deleteEdge(vertex1, vertex2);
}
