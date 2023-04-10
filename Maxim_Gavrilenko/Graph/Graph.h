
#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H
#include <iostream>
#include <C:\Users\El1x3r7714\ClionProjects\MR2022\Maxim_Gavrilenko\Linked_list\dual_linked_list.h>
#include <vector>

// Класс узла (Node)
class node
{
public:
    int value;                     // Значение узла
    LinkedList<node *> adjacent_nodes; // Список смежных узлов
    node(int val)
    {
        value = val;
    }

    void removeNeighbor(node* neighbor);
};

void node::removeNeighbor(node* neighbor) {
    neighbor->adjacent_nodes.remove(neighbor);
}


class Graph
{
public:
    LinkedList<node*> nodes;  // Список узлов графа
    // Метод добавления узла в граф
    node* add_node(int value) {
        node* Node = new node(value);
        nodes.push_tail(Node);
        return Node;
    }
    // Метод добавления ребра между двумя узлами
    void add_edge(node* node1, node* node2) {
        node1->adjacent_nodes.push_tail(node2);
        node2->adjacent_nodes.push_tail(node1);
    }

    // Удаление ребра из графа
    void removeEdge(node* node1, node* node2)
    {
        node1->adjacent_nodes.remove(node2); // Удаление вершины w из списка s
        node2->adjacent_nodes.remove(node1); // Удаление вершины s из списка w
    }



   // Удаление ноды
    void remove_node(int v)
    {
        if (v >= V)
        {
            return; // Вершина не существует
        }
        V--;
        auto *newAdj = new LinkedList<T>[V];
        for (int i = 0, j = 0; i < V + 1; i++)
        {
            if (i != v)
            {
                newAdj[j++] = adj[i];
            }
        }
        adj = newAdj;
    }
};

#endif // MR2022_GRAPH_H

