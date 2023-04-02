#include "ExceptError.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "except.h"

AtypesException STACKOVERFLOW("Trying to push into full stack!");



template <typename Q>
class Stack{
    Q *stackvalues;
    unsigned int top;
    unsigned int stacksize;
public:
    Stack();
    Stack(unsigned int size);
    ~Stack();
    template <typename R>Stack& operator=(const Stack<R> &stack);

    void StackPush(double new_value);
    void StackZering();
    void StackPop();
    double StackGet(int position);
    double StackPeek();
    int StackSize();
    bool IsEmpty();
    bool IsFull();
    void top_output();
    void size_output();

};

template <typename Q>
Stack<Q>::Stack() {
    stacksize = 10;
    stackvalues = new Q[stacksize];
    top = 0;
}

template <typename Q>
Stack<Q>::Stack(unsigned int size) {
    stackvalues = new double[size];
    stacksize = size;
    top = 0;
}

template <typename Q>
Stack<Q>::~Stack() {
    delete[] stackvalues;
}

template <typename Q>
void Stack<Q>::StackPush(double new_value) {
    if (IsFull()) {
        throw STACKOVERFLOW;
    }
    else { stackvalues[top++] = new_value; }
}

template <typename Q>
void Stack<Q>::StackZering() {
    for (unsigned int i = 0; i < stacksize; i++) {
        stackvalues[i] = 0;
    }
}

template <typename Q>
void Stack<Q>::StackPop() {
    unsigned int k = top;
    if (top == 0) throw ;
    else
    {
        stackvalues[--k] = 0;
        top--;

    }
}

template <typename Q>
double Stack<Q>::StackGet(int position) {
    return stackvalues[--position];
}

template <typename Q>
double Stack<Q>::StackPeek() {
    unsigned int k = top;
    return stackvalues[--k];
}

template <typename Q>
int Stack<Q>::StackSize() {
    return top;
}

template <typename Q>
bool Stack<Q>::IsEmpty() {
    return top == -1;
}

template <typename Q>
bool Stack<Q>::IsFull() {
    return top == stacksize - 1;
}

template <class Q> template <typename R>
Stack<Q>& Stack<Q>::operator=(const Stack<R> &stack) {
    if (this != &stack){
        if (!stackvalues)
            delete[] stackvalues;

        stacksize = stack.stacksize;
        top= stack.top;

        this->stackvalues = new double[stacksize];
        for (unsigned int i = 0; i < top; i++){
            stackvalues[i] = stack.stackvalues[i];
        }
    }
    return *this;
}

template <typename Q>
void Stack<Q>::top_output() {
    cout << "\n";
    for (unsigned int i = 0; i < top; i++){

        cout << stackvalues[i] << "  ";
    }
}

template <typename Q>
void Stack<Q>::size_output() {
    cout << "\n";
    for (unsigned int i = 0; i < stacksize; i++){

        cout << stackvalues[i] << "  ";
    }
}