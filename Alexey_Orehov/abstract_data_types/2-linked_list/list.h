#ifndef PROGRAMMING_LIST_H
#define PROGRAMMING_LIST_H

#include <iostream>
#include <vector>
#include <exception>


class ListException : public std::exception {
public:
    explicit ListException(const char* msg) : std::exception() {}
};


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
    Node<T>* list_head;
    Node<T>* list_tail;

    unsigned long long list_size;

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

    T& head() { return list_head->element; }
    T& tail() { return list_tail->element; }

    unsigned long long size() { return size; }
    bool empty() { return (bool)list_size; }
};


template<typename T>
List<T>::List() : list_head(nullptr), list_tail(nullptr), list_size(0) {}


template<typename T>
List<T>::List(const List<T>& list) : list_head(nullptr), list_tail(nullptr), list_size(0) {
    Node<T>* node_ptr = list.list_head;
    for (int idx = 0; idx < list.list_size; idx++) {
        this->push_back(node_ptr->element);
        node_ptr = node_ptr->next;
    }
}


template<typename T>
List<T>::List(List<T> &&list) noexcept : list_head(list.list_head), list_tail(list.list_tail), list_size(list.list_size) {
    list.list_head = nullptr;
    list.list_tail = nullptr;
    list.list_size = 0;
}


template<typename T>
List<T>::List(T *array, unsigned long long array_length) : list_size(0) {
    for (unsigned long long idx = 0; idx < array_length; idx++) this->push_back(array[idx]);
}


template<typename T>
void List<T>::push_back(const T &element) {
    auto new_element = new Node<T>(list_tail, nullptr, element);
    if (list_size == 0) list_head = new_element;
    else list_tail->next = new_element;
    list_tail = new_element;
    list_size++;
}


template<typename T>
void List<T>::push_front(const T &element) {
    auto new_element = new Node<T>(nullptr, list_head, element);
    if (list_size == 0) list_tail = new_element;
    else list_head->prev = new_element;
    list_head = new_element;
    list_size++;
}


template<typename T>
void List<T>::push_back(const List<T> &list) {
    List<T> new_list = list;
    new_list.list_head->prev = list_tail;
    list_tail->next = new_list.list_head;
    list_tail = new_list.list_tail;
}


template<typename T>
void List<T>::push_front(const List<T> &list) {
    List<T> new_list = list;
    new_list.list_tail->next = list_tail;
    list_tail->prev = new_list.list_tail;
    list_head = new_list.list_head;
}


template<typename T>
void List<T>::push_back(T *array, unsigned long long array_len) {
    List<T> new_list(array, array_len);
    new_list.list_head->prev = list_tail;
    list_tail->next = new_list.list_head;
    list_tail = new_list.list_tail;
}


template<typename T>
void List<T>::push_front(T *array, unsigned long long array_len) {
    List<T> new_list(array, array_len);
    new_list.list_tail->next = list_tail;
    list_tail->prev = new_list.list_tail;
    list_head = new_list.list_head;
}


template<typename T>
T List<T>::pop_back() {
    if (list_size == 0) throw ListException("Can't pop from empty list");
    T element = list_tail->element;
    list_tail->prev->next = nullptr;
    list_tail = list_tail->prev;
    return element;
}


template<typename T>
T List<T>::pop_front() {
    if (list_size == 0) throw ListException("Can't pop from empty list");
    T element = list_head->element;
    list_head->next->prev = nullptr;
    list_head = list_head->next;
    return element;
}


#endif //PROGRAMMING_LIST_H
