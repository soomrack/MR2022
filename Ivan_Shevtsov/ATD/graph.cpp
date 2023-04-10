//
// Created by ivan on 03/04/23.
//

#include "graph.h"

using namespace graph_names;


Node::Node(double data, Node *link_from_this, int edge_weight, edge_state state) {
    this->data = data;
    Edge *newEdge = new Edge(state, link_from_this, this, edge_weight);
    edges.resize(START_VECTOR_EDGES_SIZE);
    edges.push_back(newEdge);

    // id generator
    node_counter++;
    node_id = node_counter;
}

Node *Node::add_edge(Node *link_from_this, int edge_weight, edge_state state) {
    // relinking check
    for (int idx = 0; idx < edges.size(); idx++){
        if (edges[idx]->from_node == link_from_this){
            graph_exceptions EDGE_ALREADY_EDGE("edge already exists");
            throw EDGE_ALREADY_EDGE;
        } else if (edges[idx]->in_node == link_from_this) {
            edges[idx]->direction = DOUBLE_LINKED;
            //Q: add warning
        }
    }

    if (state == SINGLY_LINKED or state == DOUBLE_LINKED){
        Edge *newEdge = new Edge(state, link_from_this, this, edge_weight);
        link_from_this->push_edge(newEdge);
        edges.push_back(newEdge);
    } else {
        graph_exceptions EDGE_ADD_ERROR("can`t link it");
        throw (EDGE_ADD_ERROR);
    }

    return this;
}

Node *Node::delete_edge(Node *linked_node) {
    for (auto running_edge: edges){
        if (running_edge->from_node == linked_node or running_edge->in_node == linked_node) {
            delete running_edge;
            //nodes.erase(std::find(nodes.begin(), nodes.end(), *running_edge));  // Q: как удалить элемент из вектора по значению?

        }
    }

    return this;
}


Node::Node(){
    data = 0;
    edges.resize(START_VECTOR_EDGES_SIZE);

    node_counter++;
    node_id = node_counter;
}

Node::Node(const Node &other) {
    data = other.data;
    edges = other.edges;

    node_counter++;
    node_id = node_counter;
}

Graph::Graph() {
    nodes.resize(START_VECTOR_NODES_SIZE);

}

Node::~Node() {
    edges.clear();
    data = 0.0;

    node_counter--;
    node_id = 0;
}

Node::Node(double data) {
    this->data = data;
    edges.resize(START_VECTOR_EDGES_SIZE);

    // id generator
    node_counter++;
    node_id = node_counter;
}

Graph::Graph(double data):Graph() {
    Node* newNode = new Node(data);
    nodes.push_back(newNode);
}

void Graph::add_node(double data) {
    Node* newNode = new Node(data);
    nodes.push_back(newNode);

}

void Graph::add_edge(Node *link_from_this, Node *link_in_this, int weight, edge_state state) {
    link_in_this->add_edge(link_in_this, weight,state);
}

void Graph::delete_node(double data) {
    /**removes ALL nodes in which the data field is equal to the requested one
    */

    for (auto running_node: nodes){
        if (running_node->data == data) {
            delete running_node;

            //nodes.erase(std::find(nodes.begin(), nodes.end(), *running_node));  // Q: как удалить элемент из вектора по значению?
        }
    }

}

void Graph::delete_edge(Node *first_node, Node *second_node) {
    first_node->delete_edge(second_node);
}

void Graph::clear() {
    for (auto node: nodes){
        delete node;
    }
    nodes.clear();
}


// TODO: set const sign of the weights
Graph& Graph::dijkstra_algorithm(Node *start_node, Node *target_node) {
    Graph ans(start_node->data);
    if (start_node == target_node){
        return ans;
    }

      //todo: fix it

    auto running_node = start_node;
    bool change_flag = false;

    while (running_node != target_node) {

        // find node with min weight
        Node* node_with_min_weight = nullptr;
        int min_weight = INFINITY;
        for (auto running_edge: running_node->edges) {
            // if single linked edge
            if (min_weight > running_edge->weight and  (running_edge->from_node == running_node)) {
                min_weight = running_edge->weight;
                node_with_min_weight = running_edge->in_node;

            // if double linked edge
            } else if (min_weight > running_edge->weight and (running_edge->direction == DOUBLE_LINKED)){
                min_weight = running_edge->weight;
                if (running_edge->in_node == running_node){
                    node_with_min_weight = running_edge->from_node;
                } else if (running_edge->from_node == running_node){
                    node_with_min_weight = running_edge->in_node;
                } else {// по идее это никогда не должно выполняться #todo delete after test}


                node_with_min_weight = running_edge->in_node;
            }
        }

        if (change_flag){
            change_flag = false;
            //
        }

        if (node_with_min_weight == nullptr){
            auto tmp = min_weight;
            change_flag = true;
            node_with_min_weight.
        }
        Node *new_ans_node = new Node(node_with_min_weight->data);
        ans.add_node(new_ans_node->data);
        ans.add_edge(ans.nodes[ans.nodes.size()], new_ans_node, 0);
        running_node = node_with_min_weight;
    }

    ans.add_node(running_node->data);
    ans.add_edge(ans.nodes[ans.nodes.size()], running_node, 0);

    return ans;
}

Graph::Graph(Node *root):Graph() {
    nodes.push_back(root);
}


Edge::~Edge() {
    direction = NOT_LINKED;
    from_node = nullptr;
    in_node = nullptr;
    weight = 0;
}
