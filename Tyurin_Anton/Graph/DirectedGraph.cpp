#include "DirectedGraph.h"
#include "List.h"

void Graph::addNode(int data) {
    auto *newHead = new GraphNode(data);
    newHead->data = data;
    this->node_list.push_tail(newHead);
}

int Graph::noDestination(GraphNode *dest) {
    if (dest == nullptr) { return 0; }
    return 1;
}

void Graph::addEdge(GraphNode *loc, GraphNode *dest) {
    if (noDestination(dest)) { return; }
    Edge *newEdge = new Edge(loc, dest);
    loc->edge_list.push_tail(newEdge);
    dest->edge_list.push_tail(newEdge);
}


GraphNode *Graph::findGraphNode(unsigned int findData) {
    Node<GraphNode *> *node = this->node_list.getHead();
    while (node) {
        if (node->getNodeData()->get() == findData) {
            return node->getNodeData();
        }
        node = node->getNext();
    }
    return nullptr;
}


void Graph::addEdge(int loc_data, int dest_data) {
    GraphNode *loc = this->findGraphNode(loc_data);
    GraphNode *dest = this->findGraphNode(dest_data);
    addEdge(loc, dest);
}

/*
int GraphNode::find(GraphNode* f_node){
    GraphNode* searchNode = this->edge_list.getHead();
    while(searchNode){
        if (f_node->data == searchNode->data){return searchNode->data}
        searchNode = searchNode->next;
    }
}
*/

void Graph::deleteNode(int data) {
    GraphNode *nodeDelete = this->findGraphNode(data);
    //nodeDelete->edge_list.popAll();
    auto edgeToDelete = this->node_list.getHead()->getNodeData();
    for (unsigned int idx = 0; idx < this->node_list.get_size(); idx++){
        if (data == edgeToDelete->edge_list.){
            // удалить все loc и dest равные data(для этого написать int find(GraphNode*)
        }
        edgeToDelete = edgeToDelete->next;
    }
    this->node_list.pop(nodeDelete);
}

