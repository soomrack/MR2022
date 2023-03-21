
#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H
#include <iostream>
#include <C:\Users\El1x3r7714\ClionProjects\MR2022\Maxim_Gavrilenko\Linked_list\dual_linked_list.h>

template <typename T>
class Graph {
private:
    unsigned int V; // Количество вершин
    LinkedList<T> *adj; // Указатель на массив, содержащий списки смежности
public:
    Graph(unsigned int V) {
        this->V = V;
        adj = new LinkedList<T>[this->V];
    }

    // Добавление ребра в граф
    void addEdge(unsigned int v, int w) {
        adj[v].push_tail(w); // Добавление вершины w в список v
        adj[w].push_tail(v); // Добавление вершины v в список w
    }

    // Удаление ребра из графа
    void removeEdge(unsigned int s, unsigned int w) {
        adj[s].remove(w); // Удаление вершины w из списка s
        adj[w].remove(s); // Удаление вершины s из списка w
    }

    // Добавление вершины в граф
    void addVertex(unsigned int v) {
        if (v < V) {
            return; // Вершина уже существует
        }
        V++;
        LinkedList<T> *newAdj = new LinkedList<T>[V];
        for (int i = 0; i < V - 1; i++) {
            newAdj[i] = adj[i];
        }
        newAdj[V - 1] = LinkedList<T>();
        adj = newAdj;
    }

    // Удаление вершины из графа
    void removeVertex(unsigned int v) {
        if (v >= V) {
            return; // Вершина не существует
        }
        V--;
        LinkedList<T> *newAdj = new LinkedList<T>[V];
        for (int i = 0, j = 0; i < V + 1; i++) {
            if (i != v) {
                newAdj[j++] = adj[i];
            }
        }
        adj = newAdj;
    }
};

#endif //MR2022_GRAPH_H
