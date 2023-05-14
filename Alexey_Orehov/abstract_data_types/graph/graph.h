#ifndef MR2022_GRAPH_H
#define MR2022_GRAPH_H

#include "dynamic_array.h"

namespace Graph {

    template<class T>
    class Node {
    private:
        T value;

        DynamicArray<Node<T>*> neighbors;
        DynamicArray<unsigned int> weights;
    public:
        Node();
        Node(const T& val);
        Node(const Node& node);

    };

    template<class T>
    class Graph {
    private:
        DynamicArray<Node<T>> vertices;
    public:
        void add_node(const T& val);

    };

    template<typename T>
    Node<T>::Node(): value(0), neighbors(DynamicArray<Node<T>*>()), weights(DynamicArray<unsigned int>()) {}

    template<typename T>
    Node<T>::Node(const T &val): value(val), neighbors(DynamicArray<Node<T>*>()),
    weights(DynamicArray<unsigned int>()) {}

    template<typename T>
    Node<T>::Node(const Node<T> &node): value(node.value), neighbors(node.neighbors), weights(node.weights) {}

}



#endif //MR2022_GRAPH_H
