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

    void push_back(const List<T>& list);
    void push_front(const List<T>& list);

    void push_back(T* array, unsigned long long array_len);
    void push_front(T* array, unsigned long long array_len);

    T pop_back();
    T pop_front();

    T& head() { return _head->element; }
    T& tail() { return _tail->element; }

    unsigned long long size() { return size; }
    bool empty() { return (bool)_size; }
};


template<typename T>
List<T>::List() : _head(nullptr), _tail(nullptr), _size(0) {}


template<typename T>
List<T>::List(const List<T>& list) : _head(nullptr), _tail(nullptr), _size(0) {
    Node<T>* node_ptr = list._head;
    for (int idx = 0; idx < list._size; idx++) {
        this->push_back(node_ptr->element);
        node_ptr = node_ptr->next;
    }
}


template<typename T>
List<T>::List(List<T> &&list) noexcept : _head(list._head), _tail(list._tail), _size(list._size) {
    list._head = nullptr;
    list._tail = nullptr;
    list._size = 0;
}


template<typename T>
List<T>::List(T *array, unsigned long long array_length) : _size(0) {
    for (unsigned long long idx = 0; idx < array_length; idx++) this->push_back(array[idx]);
}


template<typename T>
void List<T>::push_back(const T &element) {
    auto new_element = new Node<T>(_tail, nullptr, element);
    if (_size == 0) _head = new_element;
    else _tail->next = new_element;
    _tail = new_element;
    _size++;
}


template<typename T>
void List<T>::push_front(const T &element) {
    auto new_element = new Node<T>(nullptr, _head, element);
    if (_size == 0) _tail = new_element;
    else _head->prev = new_element;
    _head = new_element;
    _size++;
}


template<typename T>
void List<T>::push_back(const List<T> &list) {
    List<T> new_list = list;
    new_list._head->prev = _tail;
    _tail->next = new_list._head;
    _tail = new_list._tail;
}


template<typename T>
void List<T>::push_front(const List<T> &list) {
    List<T> new_list = list;
    new_list._tail->next = _tail;
    _tail->prev = new_list._tail;
    _head = new_list._head;
}


template<typename T>
void List<T>::push_back(T *array, unsigned long long array_len) {
    List<T> new_list(array, array_len);
    new_list._head->prev = _tail;
    _tail->next = new_list._head;
    _tail = new_list._tail;
}


template<typename T>
void List<T>::push_front(T *array, unsigned long long array_len) {
    List<T> new_list(array, array_len);
    new_list._tail->next = _tail;
    _tail->prev = new_list._tail;
    _head = new_list._head;
}


template<typename T>
T List<T>::pop_back() {
    T element = _tail->element;
    _tail->prev->next = nullptr;
    _tail = _tail->prev;
    return element;
}


template<typename T>
T List<T>::pop_front() {
    T element = _head->element;
    _head->next->prev = nullptr;
    _head = _head->next;
    return element;
}


#endif //PROGRAMMING_LIST_H
