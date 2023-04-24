#include <iostream>
#include <vector>


template <typename T>
class Node {
public:
    double value;
    std::vector<T> neighbors;
    explicit Node(T value) : value(value) {};
};


template <typename T>
class Graph {
private:

public:
    void add_edge(T valueA, T valueB);
    void add_node(T value);
    void del_edge(T valueA, T valueB);
    void del_node(T value);
    void print();
};


template<typename T>
void Graph<T>::add_edge(T valueA, T valueB) {

}


template<typename T>
void Graph<T>::add_node(T value) {

}


template<typename T>
void Graph<T>::del_edge(T valueA, T valueB) {

}


template<typename T>
void Graph<T>::del_node(T value) {

}


template<typename T>
void Graph<T>::print() {

}


int main() {

}
