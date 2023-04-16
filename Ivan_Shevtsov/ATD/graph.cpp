//
// Created by ivan on 03/04/23.
//

#include "graph.h"

using namespace graph_names;


Edge::Edge(Node *source, Node *target, int weight): source(source), target(target)
        , weight(weight){}

Edge::~Edge() {
    source = nullptr;
    target = nullptr;
    weight = 0;
}

bool Edge::operator==(const Edge &other) const {
    return (weight == other.weight and target == other.target and source == other.source);
}

Node::Node(double data): data(data){}

Node::Node(double data, Node *source, int weight) {
    this->data = data;
    Edge *newEdge = new Edge(source, this, weight);
    edges.push(newEdge);
}

Node::~Node() {
    data = 0;
    edges.clear();  // Q: вот тут же не нужно удалять каждую связь, для них же вызовется деструктор сам?
}

void Node::add_edge(Node *target, int weight) {
    Edge *newEdge = new Edge(this, target, weight);
    edges.push(newEdge);
}

int Node::del_edge(Node *target, int weight, bool delete_only_one_flag) {
    /**
     * @return number of remotes edges
     */
    Edge* tmpEdge = new Edge(this, target, weight);
    auto* tmpNode  = new list_names::Node<Edge*>(tmpEdge);

    int deleted_edges_counter = 0;
    if (delete_only_one_flag) {
        if (edges.find_and_delete(tmpNode)){
            return 1;
        } else { return 0; }
    }else {
        while (edges.find_and_delete(tmpNode)){
            deleted_edges_counter++;
        }
    }

    delete tmpNode;
    delete tmpEdge;
    return deleted_edges_counter;
}


Graph::Graph(Node *root) {
    nodes.push(root);  // todo: push all the nodes in root edges
}

Graph::Graph(double data) {
    Node* newNode = new Node(data);
    nodes.push(newNode);
}

void Graph::add_node(Node* newNode) {
    nodes.push(newNode); // todo: push all the nodes in root edges
}

void Graph::add_edge(Node *source, Node *target, int weight) {
    source->add_edge(target, weight); // todo: push all the nodes in root edges
}

int Graph::del_node(double data, bool delete_all_with_data_flag) {
    /**
    * @return number of remotes nodes in graph
    */

    int deleted_nodes_counter = 0;
    auto it = nodes.begin();

    // checks the head node of the list, if it is, then delete it and calls pop()
    if (it.current_node->data->data == data){
        nodes.pop();
        delete it.current_node->data;
        deleted_nodes_counter++;
        if (!delete_all_with_data_flag) {return deleted_nodes_counter;}
    }

    // checks the other nodes of the list, if it is, then delete it and calls delete_after(node)
    if (delete_all_with_data_flag) {
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            if (it.current_node->p_next->data->data == data) {
                nodes.delete_after(it.current_node);

                deleted_nodes_counter++;
            }
        }
    } else {
        for (it = nodes.begin(); it != nodes.end(); ++it) {
            if (it.current_node->p_next->data->data == data) {
                auto tmpEdge = it.current_node->data;
                nodes.delete_after(it.current_node);
                delete it.current_node->data;
                break;
            }
        }
    }
    return deleted_nodes_counter;
}

int Graph::del_edge(Node *source, Node *target, int weight, bool delete_only_one_flag) {
    return source->del_edge(target, weight, delete_only_one_flag);
}

void Graph::clear() {
    nodes.clear();
}

void Graph::show() {
    unsigned idx = 0;
    for (auto nodes_iterator = nodes.begin(); nodes_iterator != nodes.end(); ++nodes_iterator){
        std::cout << idx << ". Data: " << nodes_iterator.current_node->data->data << "\n" << "EDGES TO NODE:\n";

        // I understand that the loop in the loop is not good ( O(n^2) ),
        // but I think in the output you can allow such a luxury

        if (nodes_iterator.current_node->data->edges.is_empty()) {
            std::cout << "\tEMPTY\n";
            idx++;
            continue;
        }
        for (auto edges_iterator = nodes_iterator.current_node->data->edges.begin();
                edges_iterator != nodes_iterator.current_node->data->edges.end(); ++edges_iterator){
            std::cout << "\tdata: " << edges_iterator.current_node->data->target->data;
            std::cout << " weight: " << edges_iterator.current_node->data->weight << "\n";
            idx++;
        }
    }
    std::cout << "END OF GRAPH\n";
}



