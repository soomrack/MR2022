#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <unordered_map>


namespace graph {
    template<class T> class Node;
    template<class T> class Graph;

    template<typename T>
    using storage_map = std::unordered_map<T, Node<T>*>;

    template<class T>
    class Node {
        friend Graph<T>;

    private:
        T value;
        storage_map<T> neighbours;

    public:
        explicit Node(const T& value): value(value) {}

    };

    template<class T>
    class Graph {
    private:
        storage_map<T> vertices;
    public:
        void add_node(const T& value);
        void add_edge(const T& from, const T& to, bool add_reverse = false);

        bool contains(const T& value) { return vertices.contains(value); }

        Node<T>* get_node(const T& value) { return vertices[value]; }
    };

    template<typename T>
    void Graph<T>::add_node(const T &value) {
        vertices[value] = new Node<T>(value);
    }

    template<typename T>
    void Graph<T>::add_edge(const T &from, const T &to, bool add_reverse) {
        if (!vertices.contains(from)) vertices[from] = new Node<T>(from);
        if (!vertices.contains(to))  vertices[to] = new Node<T>(to);
        vertices[from]->neighbours[to] = vertices[to];
        if (!add_reverse) return;
        vertices[to]->neighbours[from] = vertices[from];
    }
}


#endif //MR2022_GRAPH_H