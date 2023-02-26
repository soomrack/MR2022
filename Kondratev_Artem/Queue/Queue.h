//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_QUEUE_H
#define HELLO_WORLD_QUEUE_H


#include <cstdint>
#include <iostream>
#include "../List/List.h"


template<typename T>
class Queue {
private:
    uint64_t size;
    List<T> list;
public:
    Queue();
    ~Queue() = default;
    Queue(const Queue<T>& other);
    Queue(Queue<T>&& other) noexcept;

    Queue<T> &operator=(const Queue<T>& other);
    Queue<T> &operator=(Queue<T>&& other) noexcept;

    void append(T object);
    T pop();
    uint64_t len();
};


template<typename T>
Queue<T>::Queue() {
    list = List<T>();
    size = 0;
}


template<typename T>
Queue<T>::Queue(const Queue<T>& other) {
    size = other.size;
    list = other.list;
}


template<typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept {
    size = other.size;
    list = other.list;
    other.size = 0;
    other.list = nullptr;
}


template<typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
    if (this != &other) {
        size = other.size;
        list = other.list;
    }
    return *this;
}


template<typename T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept {
    if (this != &other) {
        size = other.size;
        list = other.list;
        other.size = 0;
        other.list = 0;
    }
    return *this;
}


template<typename T>
void Queue<T>::append(T object) {
    list.append(object);
    size++;
}


template<typename T>
T Queue<T>::pop() {
    if (size == 0) {
        throw Exception("error: bad access");
    }
    size--;
    return list.pop(0);
}


template<typename T>
uint64_t Queue<T>::len() {
    return size;
}


#endif //HELLO_WORLD_QUEUE_H
