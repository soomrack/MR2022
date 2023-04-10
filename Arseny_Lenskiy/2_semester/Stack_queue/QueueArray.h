#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include "QueueExceptions.h"

template<class T>
class QueueArray {
public:
    QueueArray(int size = 100) :
            size(size),
            tail(0),
            head(0),
            items(0) {
        if (size <= 0) {
            throw WrongQueueSize();
        }
        array = new T[size];
    }

    virtual ~QueueArray() {
        delete array;
    }

    void push(const T &e);      // Добавление элемента в очередь
    T pop();                    // Удаление элемента из очереди
    bool isEmpty();             // Проверка очереди на пустоту

private:
    int size;
    T *array;
    int tail;
    int head;
    int items;
};

template<class T>
void QueueArray<T>::push(const T &e) {
    if (tail == head && items == size) {
        throw QueueOverflow();
    } else {
        array[tail] = e;
        tail = (tail + 1) % size;
        items++;
    }
}

template<class T>
T QueueArray<T>::pop() {
    T item;
    if (head == tail && items == 0) {
        throw QueueUnderflow();
    } else {
        item = array[head];
        head = (head + 1) % size;
        items--;
    }
    return item;
}

template<class T>
bool QueueArray<T>::isEmpty() {
    return items == 0;
}

#endif