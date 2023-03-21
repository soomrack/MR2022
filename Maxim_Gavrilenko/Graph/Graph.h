
#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H
#include <iostream>
#include <C:\Users\El1x3r7714\ClionProjects\MR2022\Maxim_Gavrilenko\Linked_list\dual_linked_list.h>



/*class Graph {
private:
    int V; // Количество вершин
    std::list<int> *adj; // Указатель на массив, содержащий списки смежности
public:
    Graph(int V) {
        this->V = V;
        adj = new std::list<int>[V];
    }

    // Добавление ребра в граф
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Добавление вершины w в список v
        adj[w].push_back(v); // Добавление вершины v в список w
    }

    // Удаление ребра из графа
    void removeEdge(int v, int w) {
        adj[v].remove(w); // Удаление вершины w из списка v
        adj[w].remove(v); // Удаление вершины v из списка w
    }

    // Добавление вершины в граф
    void addVertex(int v) {
        if (v < V) {
            return; // Вершина уже существует
        }
        V++;
        std::list<int> *newAdj = new std::list<int>[V];
        for (int i = 0; i < V - 1; i++) {
            newAdj[i] = adj[i];
        }
        newAdj[V - 1] = std::list<int>();
        adj = newAdj;
    }

    // Удаление вершины из графа
    void removeVertex(int v) {
        if (v >= V) {
            return; // Вершина не существует
        }
        V--;
        std::list<int> *newAdj = new std::list<int>[V];
        for (int i = 0, j = 0; i < V + 1; i++) {
            if (i != v) {
                newAdj[j++] = adj[i];
            }
        }
        adj = newAdj;
    }

};*/



class Graph {
private:
    int V; // Количество вершин
    LinkedList *adj; // Указатель на массив, содержащий списки смежности
public:
    Graph(int V) {
        this->V = V;
        adj = new LinkedList[V];
    }

    // Добавление ребра в граф
    void addEdge(int v, int w) {
        adj[v].push_tail(w); // Добавление вершины w в список v
        adj[w].push_tail(v); // Добавление вершины v в список w
    }

    // Удаление ребра из графа
    void removeEdge(int v, int w) {
        adj[v].remove(w); // Удаление вершины w из списка v
        adj[w].remove(v); // Удаление вершины v из списка w
    }

    // Добавление вершины в граф
    void addVertex(int v) {
        if (v < V) {
            return; // Вершина уже существует
        }
        V++;
        LinkedList *newAdj = new LinkedList[V];
        for (int i = 0; i < V - 1; i++) {
            newAdj[i] = adj[i];
        }
        newAdj[V - 1] = LinkedList();
        adj = newAdj;
    }

    // Удаление вершины из графа
    void removeVertex(int v) {
        if (v >= V) {
            return; // Вершина не существует
        }
        V--;
        LinkedList *newAdj = new LinkedList[V];
        for (int i = 0, j = 0; i < V + 1; i++) {
            if (i != v) {
                newAdj[j++] = adj[i];
            }
        }
        adj = newAdj;
    }
};

#endif //MR2022_GRAPH_H
