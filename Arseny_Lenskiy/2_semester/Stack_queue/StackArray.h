#ifndef STACKARRAY_H
#define STACKARRAY_H

#include "StackExceptions.h"

template<class T>
class StackArray {
private:
    unsigned int size;
    T *array;
    int top;

public:

    ~StackArray() { delete array; }

    StackArray(int size = 100);

    void push(T element);

    T pop();

    bool isEmpty();
};

template<class T>
StackArray<T>::StackArray(int size) : size(size), top(-1) {
    if (size == 0) throw StackException(WRONGSIZE);

    array = new T[size];
}

template<class T>
void StackArray<T>::push(T element) {
    if (top == size - 1) throw StackException(OVERFLOW);

    array[++top] = element;
}

template<class T>
T StackArray<T>::pop() {
    if (top == -1) throw StackException(UNDERFLOW);

    T temp = array[top];
    --top;
    return temp;
}

template<class T>
bool StackArray<T>::isEmpty() {
    return top == -1;
}

#endif
