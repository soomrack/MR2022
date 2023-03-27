//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_PRIORITYQUEUE_H
#define HELLO_WORLD_PRIORITYQUEUE_H


#include <cstdint>
#include <iostream>


class Exception : std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message) { message = std::move(_message); };


    std::string getMessage() const { return message; };
};


template<typename T>
class PriorityQueue;


template<typename T>
class Node {
    friend class PriorityQueue<T>;


private:
    T data;
    uint64_t priority;
    Node<T>* next;
    Node<T>* prev;
public:
    Node(T _object, uint64_t _priority);
};


template<typename T>
class PriorityQueue {
private:
    uint64_t size;
    Node<T>* head;
    Node<T>* tail;

public:
    PriorityQueue();

    bool isEmpty();
    void push(T object, uint64_t priority);
    T pop();
    void print();
    uint64_t getSize();
};


template<typename T>
Node<T>::Node(T _object, uint64_t _priority) {
    data = _object;
    priority = _priority;
    next = nullptr;
    prev = nullptr;
}


template<typename T>
PriorityQueue<T>::PriorityQueue() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}


template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return size == 0;
}


template<typename T>
void PriorityQueue<T>::push(T object, uint64_t priority) {
    auto* new_node = new Node<T>(object, priority);

    if (isEmpty()) {
        head = new_node;
        tail = new_node;
        size++;
        return;
    }

    Node<T>* node = head;

    while (node) {
        if (node->priority < new_node->priority) {
            new_node->next = node;
            if (head == node) {
                head = new_node;
                node->prev = head;
            }
            else {
                node->prev->next = new_node;
                new_node->prev = node->prev;
                node->prev = new_node;
            }
            size++;
            return;
        }
        if (node->next != nullptr) {
            node = node->next;
            continue;
        }
        break;
    }

    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
    size++;
}


template<typename T>
T PriorityQueue<T>::pop() {
    if (isEmpty()) {
        throw Exception("error: queue is empty");
    }
    size--;
    T data = head->data;
    head = head->next;
    return data;
}


template<typename T>
void PriorityQueue<T>::print() {
    if (isEmpty()) {
        return;
    }
    std::cout << "[";
    Node<T>* node = head;
    while (node != tail) {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << tail->data << "]" << std::endl;
}


template<typename T>
uint64_t PriorityQueue<T>::getSize() {
    return size;
}


#endif //HELLO_WORLD_PRIORITYQUEUE_H
