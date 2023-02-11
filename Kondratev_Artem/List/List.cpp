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


template
class List<double>;

template
class List<int>;
