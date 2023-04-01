#include <string>
#include <iostream>

#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H

class Queue;

class Node {
    friend class Queue;

protected:
    Node *next;
    std::string data;
public:
    Node(std::string data) : data(data), next(nullptr) {}
};

class Queue {
protected:
    Node *head;
    Node *tail;
    unsigned int size;
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    bool is_empty();

    void push(std::string _data);

    void print();

    void pop();

    void remove_first();

    unsigned int get_size();
};

bool Queue::is_empty() {
    return head == nullptr;
}

void Queue::push(std::string data) {
    Node *local = new Node(data);
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

void Queue::print() {
    if (is_empty()) { return; }
    Node *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

void Queue::pop() {
    if (is_empty()) return;
    Node *local = head;
    if (local == tail) { tail = nullptr; }
    head = local->next;
    delete local;
    size--;
}

unsigned int Queue::get_size() {
    return size;
}

#endif //UNTITLED_QUEUE_H
