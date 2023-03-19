#ifndef MR2022_STACK_H
#define MR2022_STACK_H

#include <cstdint>


class Stack {
private:
    uint8_t size;
	double* data;
    int top;
    
public:
    Stack(unsigned int size);
    ~Stack();

    void push(double item);
    double pop();
    double peek();
    unsigned int getSize();
    bool isEmpty();
    bool isFull();
};


Stack::Stack(unsigned int size) {
  	data = new double[size];
    top = -1;
}


Stack::~Stack() {
  	delete[] data;
}


void Stack::push(double item) {
    if (isFull()) {
        std::cout << "Overflow!";
    }
    else data[++top] = item;
}


double Stack::pop() {
    int item;
    if (isEmpty()) {
        std::cout << "Stack is empty!";
    }
    else {
        item = data[top];
        data[top--] = NULL;
        return item;
    }
}


double Stack::peek() {
    if (!isEmpty()) {
        return data[top];
    }
    else {
        std::cout << "Stack is empty!";
    }
}


unsigned int Stack::getSize() {
    return top + 1;
}
 

bool Stack::isEmpty() {
    return top == -1;
}
 

bool Stack::isFull() {
    return top == size - 1;
}


#endif
