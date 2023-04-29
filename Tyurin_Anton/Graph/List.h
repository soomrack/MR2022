#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H

#include <string>
#include <iostream>
#include "GraphNode.h"

template<typename T>
class Node {
public:
    explicit Node(T data) : data(data), next(nullptr) {}

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

    Node<T> *find(T f_data);

    void delete_this(T d_data);

    void remove_first();

    void remove_last();

    unsigned int get_size();

    Node<T> *getHead();

    void popAll();

    List<T> &operator=(const List<T> &other);

    List<T> &operator=(List<T> &&other) noexcept;

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
Node<T> *List<T>::find(T f_data) {
    if (is_empty()) { return nullptr; }
    Node<T> *local = head;
    while (local) {
        if (local->data == f_data) { return local; }
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
List<T> &List<T>::operator=(const List<T> &other) {
    if (this == &other) {
        return *this;
    }
    if (other.is_empty()) {
        head = nullptr;
        tail = nullptr;
        size = 0;
        return *this;
    }
    size = other.size;
    auto* copy = new Node<T>(other.head->data);
    head = copy;
    Node<T>* original = other.head;
    while (original->next != nullptr) {
        copy->next = new Node<T>(original->next->data);
        copy = copy->next;
        original = original->next;
    }
    copy->next = nullptr;
    tail = copy;
}


template<typename T>
List<T> &List<T>::operator=(List<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->head = other.head;
    this->tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}


template<typename T>
void List<T>::delete_this(T d_data) {
    if (is_empty()) return;
    auto *local = head;
    while (local) {
        if (d_data == local->data) {
            if (local == tail){
                remove_last();
                return;
            }
            if (local == head){
                remove_first();
                return;
            }
            local->next = local->next->next;
            delete local->data;
            size--;
        }
        local = local->next;
    }
}

template<typename T>
void List<T>::popAll() {
    if (is_empty()) return;
    head = nullptr;
    tail = nullptr;
    size = 0;
}


template<typename T>
unsigned int List<T>::get_size() {
    return size;
}


template<typename T>
Node<T> *List<T>::getHead() {
    return head;
}

template<typename T>
T Node<T>::getNodeData() {
    return data;
}

template<typename T>
Node<T> *Node<T>::getNext() {
    return next;
}




#endif //HELLO_WORLD_LIST_H
