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
    explicit Stack(unsigned long long int size) {
        data = new T[size];
        allocated_space = size;
        stack_pointer = 0;
    }

    void push(const T& element);
    T pop();

    ~Stack() { delete[] data; }
};


template<typename T>
void Stack<T>::push(const T &element) {
    if (stack_pointer != allocated_space) data[stack_pointer++] = element;
    else {
        std::cerr << "unable to push" << std::endl;
        exit(2);
    }
}


template<typename T>
T Stack<T>::pop() {
    if (stack_pointer != 0) return data[--stack_pointer];
    else {
        std::cerr << "Unable to pop" << std::endl;
        exit(3);
    }
}

#endif //PROGRAMMING_STACK_H
