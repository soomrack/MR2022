#ifndef PROGRAMMING_LIST_H
#define PROGRAMMING_LIST_H

#include <iostream>
#include <vector>


template<typename T>
struct node {
    T* front;
    T* back;
    T element;
};


template<typename T>
class List {
private:
    node<T>* _head;
    node<T>* _back;

    unsigned long long _size;

public:
    List();
    List(const List<T>& list);
    List(List<T>&& list);

    ~List();

    T head() { return *_head; }
    T back() { return *_back; }

    unsigned long long size() { return size; }
    bool empty() { return (bool)_size; }
};

#endif //PROGRAMMING_LIST_H
