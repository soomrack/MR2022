//
// Created by user on 3/26/23.
//

#include "Graph.h"


Graph::Graph() {
    size = 0;
    edges_counter = 0;
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
    edges_counter++;
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


uint64_t Graph::getEdgesNumber() const {
    return edges_counter;
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


void Graph::deleteEdge(Vertex* from_vertex, Vertex* to_vertex) {
    if (edges_counter == 0 || from_vertex->getEdgesNumber() == 0 || to_vertex->getEdgesNumber() == 0) {
        return;
    }

    ListIterator<Edge*> list_iterator(&from_vertex->edge_list, from_vertex->edge_list.getHead());
    while (true) {
        if (list_iterator.get()->getStart() == to_vertex || list_iterator.get()->getEnd() == to_vertex) {
            list_iterator.popThis();
            from_vertex->edges_number--;
            to_vertex->edges_number--;
            edges_counter--;
            return;
        }
        list_iterator.shiftToTail();
    }
}


void Graph::deleteEdge(int from_data, int to_data) {
    Vertex* from_vertex = GraphIterator(this).find(from_data);
    Vertex* to_vertex = GraphIterator(this).find(to_data);

    if (!from_vertex || !to_vertex) {
        return;
    }

    deleteEdge(from_vertex, to_vertex);
}
