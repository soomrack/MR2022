#include "DirectedGraph.h"
#include "List.h"

void Graph::addNode(int data) {
    auto *newNode = new GraphNode(data);
    newNode->data = data;
    this->node_list.push_tail(newNode);
}

bool Graph::noDestination(GraphNode *dest) {
    return dest == nullptr;
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

    if (this->node_list.get_size() == 1) {this->node_list.delete_this(nodeDelete); return; }

    auto nodeForStep = this->node_list.getHead();
    auto theNeededNode = nodeForStep->getNodeData();
    auto nodeForEdgeStep = theNeededNode->edge_list.getHead();

    while (nodeForStep) {
        while (nodeForEdgeStep) {
            if ((data == nodeForEdgeStep->getNodeData()->getDest()->get()) ||
                (data == nodeForEdgeStep->getNodeData()->getLoc()->get())) {
                theNeededNode->edge_list.delete_this(nodeForEdgeStep->getNodeData());
            }
            nodeForEdgeStep = nodeForEdgeStep->next;
        }
        nodeForStep = nodeForStep->next;
    }

    this->node_list.delete_this(nodeDelete);
}

