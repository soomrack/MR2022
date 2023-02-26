//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_PRIORITYQUEUE_H
#define HELLO_WORLD_PRIORITYQUEUE_H


#include <cstdint>
#include <iostream>
#include "../List/List.h"


template<typename T>
class PriorityQueue;


template<typename T>
class Object {
    friend class PriorityQueue<T>;
private:
    T object;
    uint64_t priority;
public:
    Object(T object, uint64_t _priority);
};


template<typename T>
Object<T>::Object(T _object, uint64_t _priority) {
    object = _object;
    priority = _priority;
}


template<typename T>
class PriorityQueue {
private:
    uint64_t size;
    List<Object<T>> list;
public:
    PriorityQueue();
    PriorityQueue(const PriorityQueue<T>& other);
    PriorityQueue(PriorityQueue<T>&& other) noexcept;

    PriorityQueue<T> &operator=(const PriorityQueue<T>& other);
    PriorityQueue<T> &operator=(PriorityQueue<T>&& other) noexcept;

    void append(T object, uint64_t priority);
    T pop();
    uint64_t len();
};


template<typename T>
PriorityQueue<T>::PriorityQueue() {
    list = List<Object<T>>();
    size = 0;
}


template<typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& other) {
    size = other.size;
    list = other.list;
}


template<typename T>
PriorityQueue<T>::PriorityQueue(PriorityQueue<T>&& other) noexcept {
    size = other.size;
    list = other.list;
    other.size = 0;
    other.list = nullptr;
}


template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(const PriorityQueue<T> &other) {
    if (this != &other) {
        size = other.size;
        list = other.list;
    }
    return *this;
}


template<typename T>
PriorityQueue<T> &PriorityQueue<T>::operator=(PriorityQueue<T> &&other) noexcept {
    if (this != &other) {
        size = other.size;
        list = other.list;
        other.size = 0;
        other.list = 0;
    }
    return *this;
}


template<typename T>
void PriorityQueue<T>::append(T object, uint64_t priority) {
    Object<T> new_object(object, priority);
    list.append(new_object);
    size++;
}


template<typename T>
T PriorityQueue<T>::pop() {
    if (size == 0) {
        throw Exception("error: bad access");
    }
    uint64_t index = 0;
    Object<T> object = list[0]->getData();
    uint64_t max_priority = object.priority;
    for (uint64_t idx = 1; idx < size; idx++) {
        object = list[idx]->getData();
        if (object.priority < max_priority) {
            index = idx;
            max_priority = object.priority;
        }
    }
    return list.pop(index).object;
}


template<typename T>
uint64_t PriorityQueue<T>::len() {
    return size;
}


#endif //HELLO_WORLD_PRIORITYQUEUE_H
