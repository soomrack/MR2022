#include "ExceptError.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#define STACK_DEFAULT_SIZE 10;

class Stack{
    double *stackvalues;
    unsigned int top; //вершина стека
    unsigned int stacksize;
public:
    Stack();
    Stack(unsigned int size);
    ~Stack();
    Stack& operator=(const Stack &stack);

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
Stack::Stack() {
    stacksize = STACK_DEFAULT_SIZE;
    stackvalues = new double[stacksize];
    top = 0;
}

Stack::Stack(unsigned int size) {
    stackvalues = new double[size];
    stacksize = size;
    top = 0;
}

Stack::~Stack() {
    delete[] stackvalues;
}

void Stack::StackPush(double new_value) {
    if (IsFull())
    {
        cout << "Overflow";
    }
    else {stackvalues[top++] = new_value;}
}

void Stack::StackZering() {
    for (unsigned int i = 0; i < stacksize; i++) {
        stackvalues[i] = 0;
    }
}
void Stack::StackPop() {
    unsigned int k = top;
    if (top == 0) throw OUTOFRANGE;
    else
    {
        stackvalues[--k] = 0;
        top--;

    }
}

// Счет начинается с первой позиции
double Stack::StackGet(int position) {
    return stackvalues[--position];
}


double Stack::StackPeek() {
    unsigned int k = top;
    return stackvalues[--k];
}

int Stack::StackSize() {
    return top;
}

bool Stack::IsEmpty() {
    return top == -1;
}

bool Stack::IsFull() {
    return top == stacksize - 1;
}

Stack &Stack::operator=(const Stack &stack) {
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

void Stack::top_output() {
    cout << "\n";
    for (unsigned int i = 0; i < top; i++){

        cout << stackvalues[i] << "  ";
    }
}

void Stack::size_output() {
    cout << "\n";
    for (unsigned int i = 0; i < stacksize; i++){

        cout << stackvalues[i] << "  ";
    }
}