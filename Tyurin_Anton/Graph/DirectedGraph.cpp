#include "DirectedGraph.h"
#include "List.h"

void Graph::addNode(int data) {
    Head *newHead = new Head(data);
    newHead->data = data;
    this->node_list.push_tail(newHead);
}

int Graph::noDestination(Head *dest) {
    if (dest == nullptr) { return 0; }
    return 1;
}

void Graph::addEdge(Head *loc, Head *dest) {
    if (noDestination(dest)) { return; }
    Edge *newEdge = new Edge(loc, dest);
    loc->edge_list.push_tail(newEdge);
    dest->edge_list.push_tail(newEdge);
}


Head *Graph::findGraphNode(unsigned int findData) {
    Node<Head *> *node = this->node_list.getHead();
    while (node) {
        if (node->getNodeData()->get() == findData) {
            return node->getNodeData();
        }
        node = node->getNext();
    }
    return nullptr;
}


void Graph::addEdge(int loc_data, int dest_data) {
    Head *loc = this->findGraphNode(loc_data);
    Head *dest = this->findGraphNode(dest_data);
    addEdge(loc, dest);
}

