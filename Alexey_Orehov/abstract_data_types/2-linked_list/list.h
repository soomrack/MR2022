#ifndef PROGRAMMING_LIST_H
#define PROGRAMMING_LIST_H

#include <iostream>
#include <vector>


template<class T>
struct Node {
    Node<T>* prev;
    Node<T>* next;
    T element;
    Node(Node<T>* prev, Node<T>* next, T element) : prev(prev), next(next), element(element) {}
};


template<class T>
class List {
private:
    Node<T>* _head;
    Node<T>* _tail;

    unsigned long long _size;

public:
    List();
    List(T* array, unsigned long long array_length);
    List(const List<T>& list);
    List(List<T>&& list) noexcept;

    ~List() = default;

    void push_back(const T& element);
    void push_front(const T& element);
    T pop_back();
    T pop_front();

    T& head() { return _head->element; }
    T& tail() { return _tail->element; }

    T head(unsigned long long idx);
    T tail(unsigned long long idx);

    unsigned long long size() { return size; }
    bool empty() { return (bool)_size; }
};


template<typename T>
List<T>::List() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}


template<typename T>
List<T>::List(T *array, unsigned long long array_length) {
    for (unsigned long long idx = 0; idx < array_length; idx++) {

    }
}


template<typename T>
void List<T>::push_back(const T &element) {
    auto new_element = new Node<T>(_tail, nullptr, element);
    if (_size == 0) {
        _head = new_element;
    } else {
        _tail->next = new_element;
    }
    _tail = new_element;
    _size++;
}


template<typename T>
void List<T>::push_front(const T &element) {
    auto new_element = new Node<T>(nullptr, _head, element);
    if (_size == 0) {
        _tail = new_element;
    } else {
        _head->prev = new_element;
    }
    _head = new_element;
    _size++;
}


#endif //PROGRAMMING_LIST_H
