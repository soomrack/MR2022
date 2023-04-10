#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H

#include <string>
#include <iostream>
#include "GraphNode.h"

template<typename T>
class Node {
public:
    Node(T data) : data(data), next(nullptr) {}

    Node *next;
    T data;

    T getNodeData();

    Node<T> *getNext();
};

template<typename T>
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

    Node<T>* find(T f_data);

    GraphNode* find(unsigned int f_data);

    void pop(unsigned int id);

    Node<T> loop(unsigned int id, auto *local);

    Node<T> *operator[](const int index);

    void remove_first();

    void remove_last();

    unsigned int get_size();

    Node<T> *getHead();
};

#include "List.h"


template<typename T>
bool List<T>::is_empty() {
    return head == nullptr;
}

template<typename T>
void List<T>::push_tail(T data) {
    auto *local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    tail->next = local;
    tail = local;
    size++;
}

template<typename T>
void List<T>::push_head(T data) {
    Node local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    local->next = head;
    head = local;
    size++;
}

template<typename T>
void List<T>::print() {
    if (is_empty()) { return; }
    auto *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
Node<T>* List<T>::find(T f_data) {
    if (is_empty()) { return nullptr; }
    Node<T> *local = head;
    while(local) {
        if (local->data == f_data){ return local;}
        local = local->next;
    }
    return nullptr;
}

template<typename T>
void List<T>::remove_first() {
    if (is_empty()) return;
    auto *local = head;
    head = local->next;
    delete local;
    size--;
}

template<typename T>
void List<T>::remove_last() {
    if (is_empty()) return;
    if (head == tail) {
        remove_first();
        return;
    }
    auto *local = head;
    while (local->next != tail) local = local->next;
    local->next = nullptr;
    delete tail;
    tail = local;
    size--;
}

template<typename T>
void List<T>::pop(unsigned int id) {
    if (is_empty()) return;
    if (id > size) return;
    if (0 == id) {
        remove_first();
        return;
    } else if (id + 1 == size) {
        remove_last();
        return;
    }
    auto *local = head;
    for (int idx = 0; idx < id - 1; idx++) {
        local = local->next;
    }
    local->next = local->next->next;
    size--;
}

template<typename T>
unsigned int List<T>::get_size() {
    return size;
}


template<typename T>
Node<T>* List<T>::getHead() {
    return head;
}

template<typename T>
T Node<T>::getNodeData() {
    return data;
}

template<typename T>
Node<T>* Node<T>::getNext() {
    return next;
}

#endif //HELLO_WORLD_LIST_H
