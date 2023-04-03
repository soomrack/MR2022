//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H


#include <cstdint>
#include <iostream>
#include <utility>
#include "Exception.h"
#include "str.h"


class List;


class ListIterator;


class Node {
    friend class List;
    friend class ListIterator;
private:
    str data;
    Node* next;
public:
    explicit Node(str _data, Node* _next=nullptr);
    str get();
};


class List {
    friend class ListIterator;
private:
    uint64_t size;
    Node* head;
    Node* tail;

public:
    List();
    ~List() = default;

    Node* operator[](uint64_t index);

    bool isEmpty() const;
    void push(str data);
    void push(const str& data, uint64_t index);
    void pushHead(const str& data);
    void pushTail(str data);
    str pop();
    str pop(uint64_t index);
    void print();
    uint64_t getSize() const;
    std::string getData(uint64_t index);
    void clear();
};


class ListIterator {
private:
    List* list;
    Node* iterator;

public:
    explicit ListIterator(List *_list, Node *_iterator);
    void pushNext(str data);
    str popNext();
    void find(str data);
    str get();
};


Node::Node(str _data, Node* _next) {
    data = std::move(_data);
    next = _next;
}


str Node::get() {
    return data;
}


List::List() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}


Node *List::operator[](const uint64_t index) {
    if(isEmpty() || index >= size) {
        throw Exception("error: bad index");
    }
    Node* node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}


bool List::isEmpty() const {
    return size == 0;
}


void List::push(str data) {
    auto* node = new Node(std::move(data));
    if(isEmpty()) {
        size++;
        head = node;
        tail = node;
        return;
    }
    size++;
    tail->next = node;
    tail = node;
}


void List::push(const str& data, uint64_t index) {
    if (index > size) {
        throw Exception("error: bad index");
    }
    if (isEmpty() || index == size) {
        return push(data);
    }
    size++;
    auto* node = new Node(data);
    if (index == 0) {
        node->next = head;
        head = node;
        return;
    }
    node->next = this->operator[](index);
    this->operator[](index - 1)->next = node;
}


void List::pushHead(const str& data) {
    push(data, 0);
}


void List::pushTail(str data) {
    push(std::move(data));
}


str List::pop() {
    if (isEmpty()) {
        throw Exception("error: List is empty");
    }
    if (size == 1) {
        str data = tail->data;
        head = nullptr;
        tail = nullptr;
        size--;
        return data;
    }
    Node* node = head;
    for (uint64_t i = 0; i < size - 2; i++) {
        node = node->next;
    }
    node->next = nullptr;
    tail = node;
    size--;
    return tail->data;
}


str List::pop(uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    if (index == size - 1) {
        return pop();
    }
    if (index == 0) {
        str data = head->data;
        head = head->next;
        size--;
        return data;
    }
    Node* node = head;
    for (uint64_t i = 0; i < index - 1; i++) {
        node = node->next;
    }
    node->next = node->next->next;
    size--;
    return this->operator[](index)->data;
}


void List::print() {
    if(isEmpty()) {
        return;
    }
    std::cout << "[";
    Node* node = head;
    while (node != tail) {
        std::cout << node->data.get() << ", ";
        node = node->next;
    }
    std::cout << tail->data.get() << "]" << std::endl;
}


uint64_t List::getSize() const {
    return size;
}


std::string List::getData(uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    return this->operator[](index)->data.get();
}


void List::clear() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}


ListIterator::ListIterator(List *_list, Node* _iterator) {
    list = _list;
    iterator = _iterator;
}


void ListIterator::pushNext(str data) {
    auto* new_node = new Node(std::move(data), iterator->next);
    iterator->next = new_node;
    if (iterator == list->tail) {
        list->tail = iterator->next;
    }
    list->size++;
}


str ListIterator::popNext() {
    if (!iterator->next) {
        throw Exception("error: bad access");
    }
    list->size--;
    str data = iterator->next->get();
    if (iterator->next == list->tail) {
        list->tail = iterator;
    }
    iterator->next = iterator->next->next;
    return data;
}


void ListIterator::find(str data) {
    Node* node = list->head;
    while(node) {
        if (node->data.get() == data.get()) {
            iterator = node;
            return;
        }
        node = node->next;
    }
    iterator = nullptr;
}


str ListIterator::get() {
    return iterator->get();
}


#endif //HELLO_WORLD_LIST_H
