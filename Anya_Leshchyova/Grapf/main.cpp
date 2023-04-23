
#include <iostream>
#include <vector>
#include <algorithm>


class Node {
public:
    double data;
    std::vector<double> neighbors; // список смежности
    Node(double data) :data(data){};
};



class Graph {
private:
    Node* get_node(int data);
    std::vector<Node*> nodes;

public:
    void add_node(double data);
    void add_edge(double data_1, double data_2);
    void del_edge(double data_1, double data_2);
    void del_node(double data);
    void print();
};



void Graph::add_node(double  data) {
    auto *node = new Node(data);
    nodes.push_back(node);
}



void Graph::add_edge(double data1, double data2) {
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    if (node1 == node2) return;
    node1->neighbors.push_back(data2);
    node2->neighbors.push_back(data1);
}



void Graph::del_edge(double data1, double data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    node1->neighbors.erase(std::remove(node1->neighbors.begin(),
                                       node1->neighbors.end(), data2), node1->neighbors.end()); // Удаление вершины w из списка s
    node2->neighbors.erase(std::remove(node2->neighbors.begin(),
                                       node2->neighbors.end(), data1), node2->neighbors.end()); // Удаление вершины s из списка w
}



Node* Graph::get_node(int data) {
    for (int number = 0; number < nodes.size(); number++) {
        if (nodes[number]->data == data) {
            return nodes[number];
        }
    }
    return nullptr;
}



void Graph::del_node(double data) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if ((*it)->data == data) {
            Node *nodeToRemove = *it;
            nodes.erase(it);
            for (auto neighbor : nodeToRemove->neighbors) {
                Node *neighborNode = get_node(neighbor);
                neighborNode->neighbors.erase(std::remove(neighborNode->neighbors.begin(), neighborNode->neighbors.end(), data), neighborNode->neighbors.end());
            }
            delete nodeToRemove;
            return;
        }
    }
}



void Graph::print() {
    for (int index = 0; index < nodes.size(); index++) {
        Node *node = nodes[index];
        std::cout << node->data << ": ";
        for (int number = 0; number < node->neighbors.size(); number++) {
            std::cout <<"{ "<< node->neighbors[number] <<" }"<< " ";
        }
        std::cout << std::endl;
    }
}



int main()
{
    Graph grph;
    grph.add_node(1.00);
    grph.add_node(3.00);
    grph.add_node(5.00);
    grph.add_node(7.00);
    grph.print();
    grph.add_edge(5.00, 1.00);
    grph.add_edge(5.00, 3.00);
    grph.add_edge(1.00, 7.00);
    grph.print();
    grph.del_edge(1.00,7.00);
    grph.del_node(7.00);
    grph.print();
    return 0;
}
