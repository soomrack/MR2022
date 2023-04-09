
#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include <string>
#include "DirectedGraph.cpp"

template <typename T>
class Node {
public:
    Node(T data) : data(data), next(nullptr){}

    Node *next;
    T data;
};
template <typename T>
class List {
    friend class Node<T>;
protected:
    Node<T> *head; // head
    Node<T> *tail;  // tail
    unsigned int size;
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    bool is_empty();
    void push_tail(T data);
    void print();
    void push_head(T data);
    T find(unsigned int id);
    void pop(unsigned int id);
    Node<T> loop(unsigned int id, auto *local);
    Node<T> *operator[](const int index);
    void remove_first();
    void remove_last();
    unsigned int get_size();
};

#endif //UNTITLED_LIST_H
