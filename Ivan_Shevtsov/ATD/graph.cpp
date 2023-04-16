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

    int deleted_edges_counter = 0;
    if (delete_only_one_flag) {
        if (edges.find_and_delete(tmpEdge)){
            return 1;
        } else { return 0; }
    }else {
        while (edges.find_and_delete(tmpEdge)){
            deleted_edges_counter++;
        }
    }

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
    nodes.push(newNode);
}

void Graph::add_edge(Node *source, Node *target, int weight) {
    source->add_edge(target, weight);
}

int Graph::del_node(double data, bool delete_only_one_flag) {
    /**
    * @return number of remotes nodes in graph
    */

    int deleted_nodes_counter = 0;
    auto* tmpNode = new Node(data);
    if (delete_only_one_flag){
        if (!nodes.find_and_delete(tmpNode)) {return 0;}
        deleted_nodes_counter++;
        for (auto &&node: nodes){  // Q: вот этот момент чую как то неправильно делаю, навероне можно без вложенного цикла
                                            // можно попробовать заменить на пустую ноду, но тогда постоянное добавление и удаление будут засорять память
            for (auto it = node->edges.begin(); it != node->edges.end(); ++it){

                if (it.current_node->data->target->data == data){
                    auto tmp = it.current_node->p_next;
                    del_edge(node, it.current_node->data->target, it.current_node->data->weight);
                    it.current_node = tmp;
                }
            }
        }
    } else {
        while (nodes.find_and_delete(tmpNode)){
            if (!nodes.find_and_delete(tmpNode)) {return 0;}
            deleted_nodes_counter++;
            for (auto &&node: nodes){  // Q: это вообще ужас! три уровня вложенности, но я не понимаю как иначе
                for (auto it = node->edges.begin(); it != node->edges.end(); ++it){
                    if (it.current_node->data->target->data == data){
                        auto tmp = it.current_node->p_next;
                        del_edge(node, it.current_node->data->target, it.current_node->data->weight);
                        it.current_node = tmp;
                    }
                }
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



