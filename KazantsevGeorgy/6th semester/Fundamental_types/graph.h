#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template <typename T>
class GraphNode
{
public:
    T data;
    vector<T> neighbors;
    explicit GraphNode(T data) : data(data) {};
};


template <typename T>
class Graph
{
private:
    GraphNode<T> *get_node(T data);
    vector<GraphNode<T> *> nodes;
public:
    void add_node(T data);
    void add_edge(T data1, T data2);
    void remove_edge(T data1, T data2);
    void remove_node(T data);
    void print();
};


template <typename T>
void Graph<T>::add_node(T data)
{
    auto *node = new GraphNode<T>(data);
    nodes.push_back(node);
}

template <typename T>
GraphNode<T>* Graph<T>::get_node(T data)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->data == data) {return nodes[i]; }
    }
    return nullptr;
}

template <typename T>
void Graph<T>::add_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    if (node1 == node2) return;
    node1->neighbors.push_back(data2);
    node2->neighbors.push_back(data1);
}


template <typename T>
void Graph<T>::remove_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    node1->neighbors.erase(std::remove(node1->neighbors.begin(), node1->neighbors.end(), data2), node1->neighbors.end());
    node2->neighbors.erase(std::remove(node2->neighbors.begin(), node2->neighbors.end(), data1), node2->neighbors.end());
}



template <typename T>
void Graph<T>::remove_node(T data)
{
    for (auto node_i = nodes.begin(); node_i != nodes.end(); node_i++)
    {
        if ((*node_i)->data == data)
        {
            GraphNode<T> *removingNode = *node_i;
            nodes.erase(node_i);
            for (auto neighbor : removingNode->neighbors)
            {
                GraphNode<T> *neighborNode = get_node(neighbor);
                neighborNode->neighbors.erase(std::remove(neighborNode->neighbors.begin(), neighborNode->neighbors.end(), data), neighborNode->neighbors.end());
            }
            delete removingNode;
            return;
        }
    }
}


template <typename T>
void Graph<T>::print()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        GraphNode<T> *node = nodes[i];
        cout << "adjacency list for " << node->data << " node: ";
        for (int j = 0; j < node->neighbors.size(); j++)
        {
            cout << node->neighbors[j] << "\t";
        }
        cout << endl;
    }
}
/*
int main()
{
    Graph<double> graph;
    graph.add_node(1.3);
    graph.add_node(2.6);
    graph.add_node(3.9);
    graph.add_node(4.12);
    graph.add_edge(1.3, 2.6);
    graph.add_edge(1.3, 3.9);
    graph.add_edge(3.9, 4.12);
    graph.remove_node(4.12);
    graph.print();
    return 0;
}
*/
