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
    bool flag = flag;
    explicit GraphNode(T data) :data(data) {};
};

template <typename T>
class Edge {
public:
    GraphNode<T>* start;
    GraphNode<T>* end;
    std::string label;
    Edge(GraphNode<T>* s, GraphNode<T>* e, std::string l) : start(s), end(e), label(l) {};
};

// класс для представления графа через списки смежности
template <typename T>
class Graph
{
private:
    // поиск узла по его данным
    GraphNode<T> *get_node(T data);
    Graph<T> *get_node_by_index(index)
    std::vector<GraphNode<T> *> nodes; // список узлов графа
    std::vector<Edge<T>> edges;
public:
    // добавление узла в граф
    void add_node(T data, bool accepting);
    // добавление ребра между вершинами с данными data1 и data2
    void add_edge(T data1, T data2, std::string label);
    // Удаление ребра из графа
    void remove_edge(T data1, T data2);
    // удаление узла с данными data
    void remove_node(T data);
    // вывод списка смежности для каждого узла
    void print_adjacency_list();
};


template <typename T>
void Graph<T>::add_node(T data, bool accepting)
{
        GraphNode<T>* node = get_node(data);
    if (!node) {
        GraphNode<T>* newNode = new GraphNode<T>(data, accepting);
        nodes.push_back(newNode);
    }
}


template <typename T>
void Graph<T>::add_edge(T data1, T data2, std::string label)
{
    auto *node1 = get_node(data1);
    auto *node2 = get_node(data2);
    Edge<T> edge(node1, node2, label);
    edges.push_back(edge);
    node1->neighbors.push_back(node2->data);
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
GraphNode<T>* Graph<T>::get_node(T data)
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
class FiniteStateMachine {
    private:
        Graph<T> graph;
        GraphNode<T>* current_state;
    public:
        void add_state(T data, bool accepting);
        void add_transition(T start_state, T end_state, std::string label);
        bool process_input(std::string input);
        void reset();
};

template <typename T>
void FiniteStateMachine<T>::add_state(T data, bool accepting) {
    graph.add_node(data, accepting);
}

template <typename T>
void FiniteStateMachine<T>::add_transition(T start_state, T end_state, std::string label) {
    graph.add_edge(start_state, end_state, label);
}

template <typename T>
bool FiniteStateMachine<T>::process_input(std::string input) {
    current_state = graph.get_node_by_index(0); // устанавливаем начальное состояние
    for (char c : input) {
        bool found = false;
        for (T neighbor : current_state->neighbors) {
            Edge edge = graph.get_edge(current_state->data, neighbor);
            if (edge.label[0] == c) { // нашли переход по символу c
                current_state = neighbor;
                found = true;
                break;
            }
        }
        if (!found) return false; // нет перехода по символу c
    }
    return current_state->flag; // текущее состояние - принимающее?
}

template <typename T>
void FiniteStateMachine<T>::reset() {
    current_state = graph.get_node_by_index(0);
}

#endif //MR2022_GRAPH_2_H
