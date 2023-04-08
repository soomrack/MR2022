//
// use try/catch for work with it
//

#ifndef ATD_STACK_H
#define ATD_STACK_H
#include "dynamic_array.h"
#include <iostream>

namespace stack_names {
    class stack_exceptions: public std::domain_error{
    public:
        stack_exceptions(const char* massage): std::domain_error(massage){}
    };

/*    stack_exceptions STACK_FILLED_WARNING("[WARNING] stack is filled. Last element was added.");
    stack_exceptions ALREADY_CLEAR("stack is already clear");
    stack_exceptions STACK_EMPTY("stack is empty, can`t return return top");
    stack_exceptions STACK_OVERFLOW("stack overflow");*/

    const int START_SIZE = 50;

    template<typename T>
    class stack {
    private:
        int stack_size;
        T *sp;
        int filled_size;
        T *bp;
    public:
        stack();
        stack(int size);
        stack(stack &other);
        ~stack();

        void push(T data);
        void pop();

        void clear();
        T top();
        inline int is_filled_size() { return filled_size; }
        void print();

        bool operator==(stack &other);
        bool operator!=(stack &other);
    };
}
using namespace stack_names;

template<typename T>
void stack<T>::clear() {
    while(filled_size)
        pop();
}

template<typename T>
void stack<T>::pop() {
    if (filled_size == 0) {
        stack_exceptions ALREADY_CLEAR("stack is already clear");
        throw ALREADY_CLEAR;}  // THIS}
    filled_size--;
    sp -= sizeof(T);
}

template<typename T>
void stack<T>::print() {
    if (filled_size == 0) {
        stack_exceptions EMPTY("stack is empty");
        throw EMPTY;}  // THIS

    T* running_pointer = sp;
    for (int idx = 0; idx < filled_size; idx++){
        std::cout << *running_pointer << std::endl;
        running_pointer -= sizeof (T);
    }
}

template<typename T>
stack<T>::stack(stack &other) {
    stack_size = other.stack_size;
    filled_size = other.filled_size;
    if (other.sp == nullptr)
        { sp = nullptr; }
    bp = new T[stack_size];

    for (int idx = 0; idx < filled_size; idx++)
    {
        sp = bp + idx * sizeof(T);
        *sp = *(other.bp + idx * sizeof(T));
    }
}


template<typename T>
bool stack<T>::operator==(stack &other) {
    if (filled_size != other.filled_size or stack_size != other.stack_size)
        return false;
    else
    {
        for (int idx = 0; idx < filled_size; idx++)
        {
            if (*this->sp != *other.sp) {
                this->sp = this->bp + filled_size * sizeof(T);
                other.sp = other.bp + filled_size * sizeof(T);
                return false; }
            else{
                this->sp -= sizeof(T);
                other.sp -= sizeof(T);
            }
        }
        this->sp = this->bp + filled_size * sizeof(T);
        other.sp = other.bp + filled_size * sizeof(T);
        return true;
    }
}

template<typename T>
bool stack<T>::operator!=(stack &other) {
    return !(this == other);
}

template<typename T>
T stack<T>::top() {
    if (sp == nullptr) {
        stack_exceptions STACK_EMPTY ("stack is empty, can`t return return top");
        throw STACK_EMPTY;
    } // THIS
    return (*sp);
}

template<typename T>
stack<T>::~stack() {
    delete[] bp;
    sp = nullptr;
    filled_size = 0;
    stack_size = 0;
}

template<typename T>
stack<T>::stack() {
    filled_size = 0;
    stack_size = START_SIZE;
    bp = new T[stack_size];
    sp = nullptr;
}

template<typename T>
stack<T>::stack(int size):stack() {
    stack_size = size;
    bp = new T[size];
}

template <typename T>
void stack<T>::push(T data) {
    if (filled_size == stack_size) {
        stack_exceptions STACK_OVERFLOW("stack overflow");
        throw STACK_OVERFLOW; } // THIS}
    if (filled_size == stack_size - 1) {
        stack_exceptions STACK_FILLED_WARNING("[WARNING] stack is filled. Last element was added.");
        throw STACK_FILLED_WARNING;  }// THIS}
    if (sp == nullptr){

    }
    sp = bp + filled_size * sizeof (T);
    *sp = data;
    filled_size++;
}

#endif //ATD_STACK_H
