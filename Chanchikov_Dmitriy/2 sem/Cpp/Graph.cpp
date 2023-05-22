#include <iostream>
#include "Dynamic Array.h"

class GraphNode
{
public:
    double data;
    Dynamic_array neighbors;  // список смежности для узла

    explicit GraphNode(double data) : data(data) {}
};

class Graph
{
private:
    GraphNode *get_node(double data);
    Dynamic_array nodes;  // список узлов графа

public:
    void add_node(double data);
    void add_edge(double data1, double data2);
    void remove_node(double data);
    void remove_edge(double data1, double data2);
    void print();
};

GraphNode *Graph::get_node(double data){
    for (int i = 0; i < nodes.length(); i++){
        auto *node = reinterpret_cast<GraphNode*>(&nodes.data[i]);
        if (node->data == data){
            return node;
        }
    }
    return nullptr;
}

void Graph::add_node(double data){
    GraphNode *node = new GraphNode(data);  // GraphNode
    nodes.push_back(node->data);
}

void Graph::add_edge(double data1, double data2){
    GraphNode *node1 = get_node(data1);
    GraphNode *node2 = get_node(data2);
    if (node1 && node2){
        if (node1 == node2){
            return;
        }
        node1->neighbors.push_back(data2);
        node2->neighbors.push_back(data1);
    }
}

void Graph::remove_edge(double data1, double data2)
{
    GraphNode *node1 = get_node(data1);
    GraphNode *node2 = get_node(data2);
    node1->neighbors.remove(*node1->neighbors.data);
    node2->neighbors.remove(*node2->neighbors.data);
}

void Graph::remove_node(double data){
    GraphNode *node = get_node(data);
    if (node == nullptr){
        std::cout << "Узел не найден" << std::endl;
        return;
    }
    for (int neighborIndex = 0; neighborIndex < node->neighbors.length(); neighborIndex++){
        remove_edge(data, node->neighbors.data[neighborIndex]);
    }
    for (int i = 0; i < nodes.length(); i++){
        if (nodes.data[i] == data){
            nodes.remove(i);
            delete node;
            return;
        }
    }
    std::cout << "Узел не найден" << std::endl;
}

void Graph::print()
{
    for (int i = 0; i < nodes.length(); i++){
        const GraphNode* node = get_node(nodes.data[i]);
        std::cout << "Список смежности для вершины " << node->data << ": ";
        const Dynamic_array &neighbors = node->neighbors;
        for (int j = 0; j < node->neighbors.length(); j++){
            std::cout << node->neighbors.data[j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Graph graph;
    graph.add_node(1);
    graph.add_node(2);
    graph.add_node(3);
    graph.add_node(4);

    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.add_edge(4, 1);

    graph.print();

    return 0;
}