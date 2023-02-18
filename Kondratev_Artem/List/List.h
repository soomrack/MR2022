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
    explicit Exception(std::string _message);

    std::string getMessage() const;
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
    explicit Node(T object);
    ~Node() = default;
};


template<typename T>
class List {
private:
    uint64_t size;
    Node<T>* first;
    Node<T>* last;
public:
    List();
    List(uint64_t _size, T array[]);
    ~List() = default;
    List(const List<T>& other);
    List(List<T>&& other) noexcept ;

    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other) noexcept ;
    Node<T>* operator[](uint64_t index);
    List<T> operator+(List<T> other);

    bool isFirstEmpty();
    void append(T object);
    void append(T object, uint64_t index);
    void pop();
    void pop(uint64_t index);
    uint64_t len();
    void print();
    uint64_t getSize();
    T getData(uint64_t index);
    void clear();
};


Exception::Exception(std::string _message) {
    message = std::move(_message);
}


std::string Exception::getMessage() const {
    return message;
}


template<typename T>
Node<T>::Node(T object) {
    data = object;
}


template<typename T>
List<T>::List() {
    size = 0;
    first = nullptr;
    last = nullptr;
}


template<typename T>
List<T>::List(uint64_t _size, T array[]) {
    size = _size;
    auto* node = new Node<T>(array[0]);
    first = node;
    for (uint64_t idx = 0; idx < size - 1; idx++) {
        node->next = new Node<T>(array[idx+1]);
        node = node->next;
    }
    node->next = nullptr;
    last = node;
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
bool List<T>::isFirstEmpty() {
    return first == nullptr;
}


template<typename T>
List<T> &List<T>::operator=(const List<T> &other) {
    if (this == &other) {
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
    if(isFirstEmpty() || index >= size) {
        return nullptr;
    }
    Node<T>* node = first;
    for (int idx = 0; idx < index; idx++) {
        node = node->next;
        if (node == nullptr) {
            return node;
        }
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
void List<T>::append(T object) {
    size++;
    auto* node = new Node<T>(object);
    if(isFirstEmpty()) {
        first = node;
        last = node;
        return;
    }
    last->next = node;
    last = node;
}


template<typename T>
void List<T>::append(T object, uint64_t index) {
    if (index > size) {
        throw Exception("error: bad index");
    }
    if (isFirstEmpty() || index == size) {
        append(object);
        return;
    }
    size++;
    auto* node = new Node<T>(object);
    if (index == 0) {
        node->next = first;
        first = node;
        return;
    }
    node->next = this->operator[](index);
    this->operator[](index - 1)->next = node;
}


template<typename T>
void List<T>::pop() {
    if (isFirstEmpty()) {
        return;
    }
    if (size == 1) {
        first = nullptr;
        last = nullptr;
    }
    else {
        Node<T>* node = first;
        for (uint64_t idx = 0; idx < size - 2; idx++) {
            node = node->next;
        }
        node->next = nullptr;
        last = node;
    }
    size--;
}


template<typename T>
void List<T>::pop(uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    if (index == size - 1) {
        pop();
        return;
    }
    Node<T>* node = first;
    for (uint64_t idx = 0; idx < index - 1; idx++) {
        node = node->next;
    }
    node->next = node->next->next;
    size--;
}


template<typename T>
uint64_t List<T>::len() {
    return size;
}


template<typename T>
void List<T>::print() {
    if(isFirstEmpty()) {
        return;
    }
    std::cout << "[";
    Node<T>* node = first;
    while (node) {
        std::cout << node->data;
        if (node != last) {
            std::cout << ", ";
        }
        node = node->next;
    }
    std::cout << "]" << std::endl;
}


template<typename T>
uint64_t List<T>::getSize() {
    return size;
}


template<typename T>
T List<T>::getData(uint64_t index) {
    if (index >= size) {
        throw Exception("");
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
