#include <iostream>
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
    std::cout << "\n";
    for (unsigned int i = 0; i < top; i++){

        std::cout << stackvalues[i] << "  ";
    }
}

template <typename Q>
void Stack<Q>::size_output() {
    std::cout << "\n";
    for (unsigned int i = 0; i < stacksize; i++){

        std::cout << stackvalues[i] << "  ";
    }
}

void StackTestProgram() {
    int position = 1;
    Stack <double>A(10);
    Stack <double>B(10);
    A.StackPush(1);
    A.StackPush(2);
    A.StackPush(3);
    A.StackPush(4);
    A.StackPush(5);
    A.size_output();
    A.StackPop();
    A.size_output();
    A.StackPush(9.6);
    A.top_output();
    std::cout << "\nStack size: " << A.StackSize();
    std::cout << "\nStack top element: " << A.StackPeek();
    B = A;
    B.top_output();
    std::cout << "\nElement from the " << position << " position: " << B.StackGet(position);
}

int main() {
    StackTestProgram();
    return 0;
}