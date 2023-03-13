//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_PRIORITYQUEUE_H
#define HELLO_WORLD_PRIORITYQUEUE_H


#include <cstdint>
#include <iostream>
#include "../List/List.h"


class PriorityQueue;


class Object {
    friend class PriorityQueue;
private:
    void* object;
    uint64_t priority;
public:
    Object(void* object, uint64_t _priority);
};


Object::Object(void* _object, uint64_t _priority) {
    object = _object;
    priority = _priority;
}


class PriorityQueue {
private:
    uint64_t size;
    List list;
public:
    PriorityQueue();

    void append(void* object, uint64_t priority);
    void* pop();
    uint64_t getSize();
};


PriorityQueue::PriorityQueue() {
    list = List();
    size = 0;
}


template<typename T>
void PriorityQueue::append(void* object, uint64_t priority) {
    Object<T> new_object(object, priority);
    list.push(new_object);
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
uint64_t PriorityQueue<T>::getSize() {
    return size;
}


#endif //HELLO_WORLD_PRIORITYQUEUE_H
