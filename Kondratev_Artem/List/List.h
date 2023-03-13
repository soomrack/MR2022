//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H


#include <cstdint>
#include <iostream>


class Exception: std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message) {message = std::move(_message);};

    std::string getMessage() const {return message;};
};


template<typename T>
class List;


template<typename T>
class Node {
    friend class List<T>;
private:
    T data;
    Node<T>* next;
public:
    explicit Node(T _data, Node<T>* _next=nullptr) {data = _data; next = _next;};
    T* get() {return data;};
};


template<typename T>
class List {
private:
    uint64_t size;
    Node<T>* first;//head
    Node<T>* last;//tail
public:
    List();
    ~List() = default;
    List(const List<T>& other);
    List(List<T>&& other) noexcept ;

    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other) noexcept ;
    Node<T>* operator[](uint64_t index);
    List<T> operator+(List<T> other);

    bool isEmpty();
    void push(T data);
    void push(T data, uint64_t index);
    T pop();
    T pop(uint64_t index);
    void print();
    uint64_t getSize();
    T getData(uint64_t index);
    void clear();
};
//итератор

template<typename T>
List<T>::List() {
    size = 0;
    first = nullptr;
    last = nullptr;
}


template<typename T>
List<T>::List(const List<T> &other) {
    size = other.size;
    auto* copy = new Node<T>(other.first->data);
    first = copy;
    Node<T>* original = other.first;
    while(original->next != nullptr) {
        copy->next = new Node<T>(original->next->data);
        copy = copy->next;
        original = original->next;
    }
    copy->next = nullptr;
    last = copy;
}


template<typename T>
List<T>::List(List<T> &&other) noexcept {
    this->first = other.first;
    this->last = other.last;
    size = other.size;
    other.first = nullptr;
    other.last = nullptr;
    other.size = 0;
}


template<typename T>
List<T> &List<T>::operator=(const List<T> &other) {
    if (this == &other) {
        return *this;
    }
    if (other.isEmpty()) {
        first = nullptr;
        last = nullptr;
        size = 0;
        return *this;
    }
    size = other.size;
    auto* copy = new Node<T>(other.first->data);
    first = copy;
    Node<T>* original = other.first;
    while(original->next != nullptr) {
        copy->next = new Node<T>(original->next->data);
        copy = copy->next;
        original = original->next;
    }
    copy->next = nullptr;
    last = copy;
}


template<typename T>
List<T> &List<T>::operator=(List<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->first = other.first;
    this->last = other.last;
    size = other.size;
    other.first = nullptr;
    other.last = nullptr;
    other.size = 0;
}


template<typename T>
Node<T> *List<T>::operator[](const uint64_t index) {
    if(isEmpty() || index >= size) {
        throw Exception("error: bad index");
    }
    Node<T>* node = first;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}


template<typename T>
List<T> List<T>::operator+(List<T> other) {
    List<T> result;
    result.first = this->first;
    result.last = other.last;
    result.size = this->size + other.size;
    this->last->next = other.first;
    return result;
}


template<typename T>
bool List<T>::isEmpty() {
    return size == 0;
}


template<typename T>
void List<T>::push(T data) {
    auto* node = new Node<T>(data);
    if(isEmpty()) {
        size++;
        first = node;
        last = node;
        return;
    }
    size++;
    last->next = node;
    last = node;
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
        node->next = first;
        first = node;
        return;
    }
    node->next = this->operator[](index);
    this->operator[](index - 1)->next = node;
}


template<typename T>
T List<T>::pop() {
    if (isEmpty()) {
        throw Exception("error: List is empty");
    }
    if (size == 1) {
        T data = last->data;
        first = nullptr;
        last = nullptr;
        size--;
        return data;
    }
    Node<T>* node = first;
    for (uint64_t i = 0; i < size - 2; i++) {
        node = node->next;
    }
    node->next = nullptr;
    last = node;
    size--;
    return last->data;
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
        T data = first->data;
        first = first->next;
        size--;
        return data;
    }
    Node<T>* node = first;
    for (uint64_t i = 0; i < index - 1; i++) {
        node = node->next;
    }
    node->next = node->next->next;
    size--;
    return this->operator[](index)->data;
}


template<typename T>
void List<T>::print() {
    if(isEmpty()) {
        return;
    }
    std::cout << "[";
    Node<T>* node = first;
    while (node != last) {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << last->data << "]" << std::endl;
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
void List<T>::clear() {
    size = 0;
    first = nullptr;
    last = nullptr;
}


#endif //HELLO_WORLD_LIST_H
