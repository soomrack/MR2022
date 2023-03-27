//
// Created by user on 3/26/23.
//

#include "Graph.h"


Graph::Graph() {
    size = 0;
}


void Graph::addVertex(int data) {
    auto* vertex = new Vertex(data);
    list.push(vertex);
    size++;
}


bool Graph::addEdge(Vertex* from_vertex, Vertex* to_vertex, bool is_directed) {
    if (!from_vertex || !to_vertex) {
        return false;
    }

    auto* edge = new Edge(from_vertex, to_vertex, is_directed);
    from_vertex->appendEdge(edge);
    to_vertex->appendEdge(edge);
    return true;
}


bool Graph::addEdge(int from_data, int to_data, bool is_directed) {
    Vertex* from_vertex = GraphIterator(this).find(from_data);
    Vertex* to_vertex = GraphIterator(this).find(to_data);

    if (!from_vertex || !to_vertex) {
        return false;
    }

    return addEdge(from_vertex, to_vertex, is_directed);
}


uint64_t Graph::getVertexNumber() const {
    return size;
}


void Graph::printVertices() {
    auto* node = list.getHead();
    while (node != list.getTail()) {
        std::cout << node->getNodeObject()->get() << ", ";
        node = node->getNext();
    }
    std::cout << node->getNodeObject()->get() << std::endl;
}


void Graph::printEdges() {
    GraphIterator iterator(this, list.getHead()->getNodeObject());

    while (iterator.getVertex()) {
        auto* vertex = iterator.getVertex();
        std::cout << vertex->get() << " : " << std::endl;

        ListIterator<Edge*> edge_iterator(&vertex->edge_list, vertex->edge_list.getHead());
        for (int i = 0; i < vertex->edge_list.getSize(); i++) {
            std::cout << "    " << edge_iterator.get()->getStart()->get();
            (edge_iterator.get()->getIsDirected()) ? std::cout << " <--> " : std::cout << "  --> ";
            std::cout << edge_iterator.get()->getEnd()->get() << std::endl;
            edge_iterator.end();
        }
        iterator.shiftToTail();
    }
}


Vertex* Graph::find(int data) {
    return GraphIterator(this).find(data);
}


void Graph::delVertex(int data) {
    GraphIterator iterator(this);

    if (iterator.find(data) == nullptr) {
        return;
    }

    iterator.deleteVertex();
}


void Graph::delEdge(Vertex* vertex1, Vertex* vertex2) {
    if (!vertex1 || !vertex2) {
        return;
    }

    vertex1->deleteEdge(vertex2);
    vertex2->deleteEdge(vertex1);
}


void Graph::delEdge(int data1, int data2) {
    Vertex* vertex1 = GraphIterator(this).find(data1);
    Vertex* vertex2 = GraphIterator(this).find(data2);

    delEdge(vertex1, vertex2);
}
