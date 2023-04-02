//
// Created by El1x3r7714 on 28/03/2023.
//

#ifndef MR2022_GRAPH_2_H
#define MR2022_GRAPH_2_H
#include <iostream>
#include <vector>
#include <algorithm>
// класс для представления узла графа
template <typename T>
class GraphNode
{
public:
    T data; // данные, хранимые в узле
    std::vector<T> neighbors; // список смежности для узла

    explicit GraphNode(T data) :data(data) {};
};

// класс для представления графа через списки смежности
template <typename T>
class Graph
{
private:
    // поиск узла по его данным
    GraphNode<T> *get_node(int data);
    std::vector<GraphNode<T> *> nodes; // список узлов графа
public:
    // добавление узла в граф
    void add_node(T data);
    // добавление ребра между вершинами с данными data1 и data2
    void add_edge(T data1, T data2);
    // Удаление ребра из графа
    void remove_edge(T data1, T data2);
    // удаление узла с данными data
    void remove_node(T data);
    // вывод списка смежности для каждого узла
    void print();
};


template <typename T>
void Graph<T>::add_node(T data)
{
    auto *node = new GraphNode<T>(data);
    nodes.push_back(node);
}


template <typename T>
void Graph<T>::add_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    if (node1 == node2) return; // Случай ребра на одну вершину
    node1->neighbors.push_back(data2);
    node2->neighbors.push_back(data1);
}


template <typename T>
void Graph<T>::remove_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    node1->neighbors.erase(std::remove(node1->neighbors.begin(),
                                       node1->neighbors.end(), data2), node1->neighbors.end()); // Удаление вершины w из списка s
    node2->neighbors.erase(std::remove(node2->neighbors.begin(),
                                       node2->neighbors.end(), data1), node2->neighbors.end()); // Удаление вершины s из списка w
}


template <typename T>
GraphNode<T>* Graph<T>::get_node(int data)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->data == data)
        {
            return nodes[i];
        }
    }
    return nullptr;
}


template <typename T>
void Graph<T>::remove_node(T data)
{
    // находим узел по данным и удаляем его из списка узлов
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if ((*it)->data == data)
        {
            GraphNode<T> *nodeToRemove = *it;
            nodes.erase(it);
            // удаляем все ребра, связанные с удаляемым узлом
            for (auto neighbor : nodeToRemove->neighbors)
            {
                GraphNode<T> *neighborNode = get_node(neighbor);
                neighborNode->neighbors.erase(std::remove(neighborNode->neighbors.begin(), neighborNode->neighbors.end(), data), neighborNode->neighbors.end());
            }
            delete nodeToRemove; // освобождаем память, занятую удаляемым узлом
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
        std::cout << "Adjacency list for node " << node->data << ": ";
        for (int j = 0; j < node->neighbors.size(); j++)
        {
            std::cout << node->neighbors[j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif //MR2022_GRAPH_2_H
