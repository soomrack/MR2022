#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include "QueueExceptions.h"

template<class T>
class QueueArray {
private:
    unsigned int size;
    T *array;
    int tail;
    int head;
    int items;

public:
    QueueArray(unsigned int size = 100);

    ~QueueArray() { delete array; }

    void push(T element);

    T pop();

    bool isEmpty();
};

template<class T>
QueueArray<T>::QueueArray(unsigned int size): size(size), tail(0), head(0), items(0) {
    if (size == 0) throw QueueException(WRONGSIZE);
    array = new T[size];
}

template<class T>
void QueueArray<T>::push(T element) {
    if (tail == head && items == size) throw QueueException(OVERFLOW);

    array[tail] = element;
    tail = (tail + 1) % size;
    items++;
}

template<class T>
T QueueArray<T>::pop() {
    T item;
    if (head == tail && items == 0) throw QueueException(UNDERFLOW);

    item = array[head];
    head = (head + 1) % size;
    items--;
    return item;
}

template<class T>
bool QueueArray<T>::isEmpty() {
    return items == 0;
}

#endif
