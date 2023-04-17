#include "DirectedGraph.h"
#include "List.h"

void Graph::addNode(int data) {
    auto *newNode = new GraphNode(data);
    newNode->data = data;
    this->node_list.push_tail(newNode);
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
    auto nodeDelete = this->findGraphNode(data);
    /*
    //if (this->node_list.get_size() == 1) {this->node_list.pop(nodeDelete); return; }
    auto nodeForStep = this->node_list.getHead();

    auto edgeToDelete = nodeForStep->getNodeData();
    auto nodeForEdgeStep = edgeToDelete->edge_list.getHead();
    //for (unsigned int idx = 0; idx < this->node_list.get_size(); idx++) {
        //for (unsigned int idx1 = 0; idx1 < edgeToDelete->edge_list.get_size(); idx1++) {
    while (nodeForStep) {
        while (nodeForEdgeStep) {
            if ((data == nodeForEdgeStep->getNodeData()->getDest()->get()) ||
                (data == nodeForEdgeStep->getNodeData()->getLoc()->get())) {
                // удалить все loc и dest равные data
                edgeToDelete->edge_list.pop(nodeForEdgeStep->getNodeData());
            }
            nodeForEdgeStep = nodeForEdgeStep->next;
        }
        nodeForStep = nodeForStep->next;
    }
     */
    this->node_list.pop(nodeDelete);

}

