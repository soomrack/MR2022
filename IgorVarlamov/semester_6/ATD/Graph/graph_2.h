

#ifndef MR2022_GRAPH_2_H
#define MR2022_GRAPH_2_H
#include <iostream>
#include "../Dynamic_array/Dynamic_array.h"

template <typename T>
class GraphNode
{
public:
    T data; // данные, хранимые в узле
    dynamic_array<T> neighbors; // список смежности для узла

    explicit GraphNode(T data) :data(data) {};
};

// класс для представления графа через списки смежности
template <typename T>
class Graph
{
private:
    // поиск узла по его данным
    GraphNode<T> *get_node(double data);
    dynamic_array<GraphNode<T> *> nodes; // список узлов графа
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
    nodes.append(node);
}


template <typename T>
void Graph<T>::add_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    if (node1 == node2) return; // Случай ребра на одну вершину
    node1->neighbors.append(data2);
    node2->neighbors.append(data1);
}


template <typename T>
void Graph<T>::remove_edge(T data1, T data2)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    node1->neighbors.remove(node1->neighbors.search(data2)); // Удаление вершины w из списка s
    node2->neighbors.remove(node2->neighbors.search(data1));
}



template <typename T>
GraphNode<T>* Graph<T>::get_node(double data)
{
    for (auto i = 0; i < nodes.get_size(); i++){
        if (nodes[i]->data == data)
        {
            return nodes[i];
        }
    }
    return nullptr;
}

template <typename T>
void Graph<T>::remove_node(T data) {
    // Находим удаляемый узел по данным
    GraphNode<T> *node = get_node(data);
    if (node == nullptr) {
        std::cout << "Узел не найден" << std::endl;
        return;
    }
    //! Альтернативное решение
    /*
    Если добавить в Dynamic array итерацию begin - end, то вместо кода ниже можно использовать:
    for (auto neighbor : node->neighbors) 
    { remove_edge(data, neighbor); } for (auto neighbor : node->neighbors) { remove_edge(data, neighbor); }
    */
    // Удаляем ребра, связанные с данным узлом
    for (int neighborIndex = 0; neighborIndex < node->neighbors.get_size(); neighborIndex++) {
    remove_edge(data, node->neighbors[neighborIndex]);
    }
    // Удаляем узел из списка узлов графа
    for (size_t i = 0; i < nodes.get_size(); i++) {
        if (nodes[i]->data == data) {
            nodes.remove(i);
            delete node;
            return;
        }
    }
    std::cout << "Узел не найден" << std::endl;
}



template <typename T>
void Graph<T>::print()
{
    for (int i = 0; i < nodes.get_size(); i++)
    {
        GraphNode<T> *node = nodes[i];
        std::cout << "Adjacency list for node " << node->data << ": ";
        for (int j = 0; j < node->neighbors.get_size(); j++)
        {
            std::cout << node->neighbors[j] << " ";
        }
        std::cout << std::endl;
    }
}

#endif //MR2022_GRAPH_2_H
