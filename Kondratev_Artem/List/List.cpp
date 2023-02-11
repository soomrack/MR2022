//
// Created by user on 11.02.23.
//

#include "List.h"


template<typename T>
List<T>::List() {
    size = 0;
    first = nullptr;
    last = nullptr;
}


template<typename T>
bool List<T>::isFirstEmpty() {
    return first == nullptr;
}


template<typename T>
Node<T> *List<T>::operator[](const uint64_t index) {
    if(isFirstEmpty() || index >= size) {
        return nullptr;
    }
    Node<T>* p = first;
    for (int idx = 0; idx < index; idx++) {
        p = p->next;
        if (p == nullptr) {
            return p;
        }
    }
    return p;
}


template<typename T>
void List<T>::append(T object) {
    size++;
    auto* p = new Node<T>(object);
    if(isFirstEmpty()) {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
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
    auto* p = new Node<T>(object);
    if (index == 0) {
        p->next = first;
        first = p;
    }
    else {
        p->next = this->operator[](index);
        this->operator[](index - 1)->next = p;
    }
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
    Node<T>* printer = first;
    while (printer) {
        std::cout << printer->data;
        if (printer != last) {
            std::cout << ", ";
        }
        printer = printer->next;
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


template
class List<double>;

template
class List<int>;
