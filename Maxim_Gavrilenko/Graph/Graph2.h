#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H

#include <iostream>
#include <vector>
#include <C:\Users\El1x3r7714\ClionProjects\MR2022\Maxim_Gavrilenko\Linked_list\dual_linked_list.h>

// Класс узла (Node)
class node
{
public:
    int value;                    // Значение узла
    LinkedList<node *> neighbors; // Список смежных узлов
    node(int val) : value(val){};
    void addNeighbor(node *neighbor);
    void removeNeighbor(node *neighbor);
    void clearNeighbor();
};

void node::addNeighbor(node *neighbor)
{
    neighbors.push_tail(neighbor);
}

void node::removeNeighbor(node *neighbor)
{
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        if (*it == neighbor)
        {
            neighbors.remove(it);
            break;
        }
    }
}

void node::clearNeighbor()
{
    for (auto neighbor : neighbors)
    {
        neighbor->removeNeighbor(this);
    }
    neighbors.clear();
}

class Graph
{
public:
    LinkedList<node *> nodes; // Список узлов графа
    // Метод добавления узла в граф
    node *add_node(int value)
    {
        node *Node = new node(value);
        nodes.push_tail(Node);
        return Node;
    }
    // Метод добавления ребра между двумя узлами
    void add_edge(node *node1, node *node2)
    {
        node1->neighbors.push_tail(node2);
        node2->neighbors.push_tail(node1);
    }

    // Удаление ребра из графа
    void removeEdge(node *node1, node *node2)
    {
        node1->neighbors.remove(node2); // Удаление вершины w из списка s
        node2->neighbors.remove(node1); // Удаление вершины s из списка w
    }

    void removeNode(node *node)
    {
        // Remove node from list of neighbors of all its neighbors
        node->clearNeighbor();

        // Remove node from the list of nodes
        for (auto it = nodes.begin(); it != nodes.end(); ++it)
        {
            if (*it == node)
            {
                nodes.remove(it);
                break;
            }
        }

        // Delete node from memory
        delete node;
    }
};

#endif MR2022_GRAPH_H