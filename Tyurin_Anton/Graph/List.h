//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H
// create shiftToHead shiftToTail in ListIterator;

#include <cstdint>
#include <iostream>
#include "Head.h"


class Exception : std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message) { message = std::move(_message); };

    std::string getMessage() const { return message; };
};


template<typename T>
class List;


template<typename T>
class ListIterator;


template<typename T>
class Node {
    friend class List<T>;
    friend class ListIterator<T>;

private:
    T data;
    Node<T>* next;
    Node<T>* prev;
public:
    explicit Node(T _data, Node<T>* _next = nullptr, Node<T>* _prev = nullptr);

    T getNodeObject();
    Node<T>* getNext();
    Node<T>* getPrev();
};


template<typename T>
class List {
    friend class ListIterator<T>;

private:
    uint64_t size;
    Node<T>* head;
    Node<T>* tail;

public:
    List();
    ~List() = default;
    List(const List<T> &other);
    List(List<T> &&other) noexcept;

    List<T> &operator=(const List<T> &other);
    List<T> &operator=(List<T> &&other) noexcept;
    Node<T>* operator[](uint64_t index);
    List<T> operator+(List<T> other);

    bool isEmpty();
    void push(T data);
    void push(T data, uint64_t index);
    void pushHead(T data);
    void pushTail(T data);
    T pop();
    T pop(uint64_t index);
    void print();
    uint64_t getSize();
    T getData(uint64_t index);
    Node<T>* getHead();
    Node<T>* getTail();
    void clear();
};


template<typename T>
class ListIterator {
private:
    List<T>* list;
    Node<T>* iterator;

public:
    explicit ListIterator(List<T>* _list, Node<T>* _iterator=nullptr);
    ListIterator(List<T>* _list, T data);
    void pushNext(T data);
    void pushPrev(T data);
    T popNext();
    T popPrev();
    T popThis();
    Node<T>* find(T data);
    Node<T>* getIterator();
    T get();
    void shiftToHead();
    void shiftToTail();
    bool isHead();
    bool isTail();
};


template<typename T>
Node<T>::Node(T _data, Node<T>* _next, Node<T>* _prev) {
    data = _data;
    next = _next;
    prev = _prev;
}


template<typename T>
T Node<T>::getNodeObject() {
    return data;
}


template<typename T>
Node<T>* Node<T>::getNext() {
    return next;
}


template<typename T>
Node<T>* Node<T>::getPrev() {
    return prev;
}


template<typename T>
List<T>::List() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}


template<typename T>
List<T>::List(const List<T> &other) {
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
List<T>::List(List<T> &&other) noexcept {
    this->head = other.head;
    this->tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}


template<typename T>
List<T> &List<T>::operator=(const List<T> &other) {
    if (this == &other) {
        return *this;
    }
    if (other.isEmpty()) {
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
Node<T>* List<T>::operator[](const uint64_t index) {
    if (isEmpty() || index >= size) {
        throw Exception("error: bad index");
    }
    Node<T>* node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}


template<typename T>
List<T> List<T>::operator+(List<T> other) {
    List<T> result;
    result.head = this->head;
    result.tail = other.tail;
    result.size = this->size + other.size;
    this->tail->next = other.head;
    return result;
}


template<typename T>
bool List<T>::isEmpty() {
    return size == 0;
}


template<typename T>
void List<T>::push(T data) {
    auto* node = new Node<T>(data);
    if (isEmpty()) {
        size++;
        head = node;
        tail = node;
        return;
    }
    size++;
    tail->next = node;
    node->prev = tail;
    tail = node;
}


template<typename T>
void List<T>::push(T data, uint64_t index) {
    if (index > size) {
        throw Exception("error: bad index");
    }
    if (isEmpty() || index == size) {
        return push(data);
    }
    size++;
    auto* node = new Node<T>(data);
    if (index == 0) {
        node->next = head;
        head = node;
        return;
    }
    node->next = this->operator[](index);
    node->prev = this->operator[](index - 1);
    this->operator[](index - 1)->next = node;
    node->next->prev = node;
}


template<typename T>
void List<T>::pushHead(T data) {
    push(data, 0);
}


template<typename T>
void List<T>::pushTail(T data) {
    push(data);
}


template<typename T>
T List<T>::pop() {
    if (isEmpty()) {
        throw Exception("error: List is empty");
    }
    if (size == 1) {
        T data = tail->data;
        head = nullptr;
        tail = nullptr;
        size--;
        return data;
    }
    Node<T>* node = head;
    for (uint64_t i = 0; i < size - 2; i++) {
        node = node->next;
    }
    node->next = nullptr;
    tail = node;
    size--;
    return tail->data;
}


template<typename T>
T List<T>::pop(uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    if (index == size - 1) {
        return pop();
    }
    if (index == 0) {
        T data = head->data;
        head = head->next;
        head->prev = nullptr;
        size--;
        return data;
    }
    Node<T>* node = head;
    for (uint64_t i = 0; i < index - 1; i++) {
        node = node->next;
    }
    node->next->next->prev = node;
    node->next = node->next->next;
    size--;
    return this->operator[](index)->data;
}


template<typename T>
void List<T>::print() {
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
uint64_t List<T>::getSize() {
    return size;
}


template<typename T>
T List<T>::getData(uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    return this->operator[](index)->data;
}


template<typename T>
Node<T>* List<T>::getHead() {
    return head;
}


template<typename T>
Node<T>* List<T>::getTail() {
    return tail;
}


template<typename T>
void List<T>::clear() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}


template<typename T>
ListIterator<T>::ListIterator(List<T>* _list, Node<T>* _iterator) {
    list = _list;
    iterator = _iterator;
}


template<typename T>
ListIterator<T>::ListIterator(List<T>* _list, T data) {
    list = _list;
    iterator = find(data);
}


template<typename T>
void ListIterator<T>::pushNext(T data) {
    if (!iterator) {
        return;
    }
    auto* new_node = new Node<T>(data, iterator->next);
    new_node->next = iterator->next;
    new_node->prev = iterator;
    iterator->next->prev = new_node;
    iterator->next = new_node;
    if (iterator == list->tail) {
        list->tail = iterator->next;
    }
    list->size++;
}


template<typename T>
void ListIterator<T>::pushPrev(T data) {
    if (!iterator) {
        return;
    }
    auto* new_node = new Node<T>(data, iterator->next);
    new_node->next = iterator;
    new_node->prev = iterator->prev;
    iterator->prev->next = new_node;
    iterator->prev = new_node;
    if (iterator == list->head) {
        list->head = iterator->prev;
    }
    list->size++;
}


template<typename T>
T ListIterator<T>::popNext() {
    if (!iterator->next  || list->isEmpty()) {
        throw Exception("error: bad access");
    }
    list->size--;
    T data = iterator->next->getNodeObject();
    if (iterator->next == list->tail) {
        list->tail = iterator;
    }
    if(iterator->next->next) {
        iterator->next->next->prev = iterator;
    }
    iterator->next = iterator->next->next;
    return data;
}


template<typename T>
T ListIterator<T>::popPrev() {
    if (!iterator->prev || list->isEmpty()) {
        throw Exception("error: bad access");
    }
    list->size--;
    T data = iterator->prev->getNodeObject();
    if (iterator->prev == list->head) {
        list->head = iterator;
    }
    if (iterator->prev->prev) {
        iterator->prev->prev->next = iterator;
    }
    iterator->prev = iterator->prev->prev;
    return data;
}


template<typename T>
T ListIterator<T>::popThis() {
    if (!iterator || list->isEmpty()) {
        throw Exception("error: bad access");
    }

    T data = iterator->getNodeObject();

    if (list->getSize() == 1) {
        list->clear();
        iterator = nullptr;
        return data;
    }

    if (iterator == list->head) {
        list->head = iterator->next;
    }
    if (iterator == list->tail) {
        list->tail = iterator->prev;
    }

    if (iterator->next) {
        iterator->next->prev = iterator->prev;
    }
    if (iterator->prev) {
        iterator->prev->next = iterator->next;
    }

    iterator = nullptr;
    list->size--;
    return data;
}


template<typename T>
Node<T>* ListIterator<T>::find(T data) {
    Node<T>* node = list->head;
    while (node) {
        if (node->data == data) {
            iterator = node;
            return iterator;
        }
        node = node->next;
    }
    iterator = nullptr;
    return iterator;
}


template<typename T>
Node<T>* ListIterator<T>::getIterator() {
    return iterator;
}


template<typename T>
T ListIterator<T>::get() {
    return iterator->getNodeObject();
}


template<typename T>
void ListIterator<T>::shiftToHead() {
    if (iterator) {
        iterator = iterator->prev;
    }
}


template<typename T>
void ListIterator<T>::shiftToTail() {
    if (iterator) {
        iterator = iterator->next;
    }
}


template<typename T>
bool ListIterator<T>::isHead() {
    return iterator == list->head;
}


template<typename T>
bool ListIterator<T>::isTail() {
    return iterator == list->tail;
}


#endif //HELLO_WORLD_LIST_H
