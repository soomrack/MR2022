#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H

#include "dynamic_array.h"
#include <set>


namespace Graph {

    template<class T>
    class Node {
    private:
        T value;
        DynamicArray<Node<T>*> neighbors;

    public:
        Node();
        explicit Node(const T& val);
        Node(const Node& node);

    };

    template<class T>
    struct Edge {
        Node<T>* orgn;
        Node<T>* dest;
    };

    template<class T>
    class Graph {
    private:
        DynamicArray<Node<T>*> vertices;
    public:
        Graph(DynamicArray<Edge<T>> edges);

    };

    template<typename T>
    Node<T>::Node(): value(0), neighbors(DynamicArray<Node<T>*>()) {}

    template<typename T>
    Node<T>::Node(const T &val): value(val), neighbors(DynamicArray<Node<T>*>()) {}

    template<typename T>
    Node<T>::Node(const Node<T> &node): value(node.value), neighbors(node.neighbors) {}


    template<typename T>
    Graph<T>::Graph(DynamicArray<Edge<T>> edges) {
        std::set<Node<T>*> counter;
        for (int idx = 0; idx < edges.length(); idx++){
            counter.insert(edges[idx].orgn);
            counter.insert(edges[idx].dest);
        }
        vertices.resize(counter.size());
        for (auto& el: counter) {
            vertices.push_back(el);
        }
    }

}



#endif //MR2022_GRAPH_H
