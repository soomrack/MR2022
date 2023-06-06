#ifndef PROGRAMMING_QUEUE_H
#define PROGRAMMING_QUEUE_H

#include "twoLinkedList.h"


template<class T>
class Queue {
private:
    list::List<T> list;

public:
    Queue() = default;
    void enqueue(const T& element) { list.push_back(element); }
    T dequeue() { return list.pop_front(); }
};


#endif //PROGRAMMING_QUEUE_H
