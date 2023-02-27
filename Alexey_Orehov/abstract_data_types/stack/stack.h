#ifndef PROGRAMMING_STACK_H
#define PROGRAMMING_STACK_H

#include <iostream>

template <class T>
class Stack {
private:
    T* data;
    unsigned long long stack_pointer;
    unsigned long long allocated_space;

public:
    explicit Stack(unsigned long long int size);

    void push(const T& element);
    T pop();

    ~Stack() { delete[] data; }
};


template<typename T>
Stack<T>::Stack(unsigned long long size) {
    data = new T[size];
    allocated_space = size;
    stack_pointer = 0;
}


template<typename T>
void Stack<T>::push(const T &element) {

}


template<typename T>
T Stack<T>::pop() {
    return data[--stack_pointer];
}

#endif //PROGRAMMING_STACK_H
