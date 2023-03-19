#ifndef PROGRAMMING_QUEUE_H
#define PROGRAMMING_QUEUE_H

#include "list.h"


template<class T>

class Queue {
private:
    List<T> list;

public:
    Queue();

    void enqueue(const T& element);
    T dequeue();
};


template<typename T>
Queue<T>::Queue() : list() {}


template<typename T>
void Queue<T>::enqueue(const T &element) {
    list.push_back(element);
}


template<typename T>
T Queue<T>::dequeue() {
    return list.pop_front();
}


#endif //PROGRAMMING_QUEUE_H
