//
// use try/catch for work with it
//

#ifndef ATD_STACK_H
#define ATD_STACK_H
#include "dynamic_array.h"
#include <iostream>

const int START_DEPTH = 50;

template <typename T>
class stack {
public:
    stack();
    stack(int depth);
    stack(stack& other);

    void push(T data);
    void pop();
    void clear();
    T top();
    //int is_filled_size(){ return filled_size;}
    void print();

    bool operator==(stack& other);
    bool operator!=(stack& other);

    ~stack();
private:
    int stack_size;
    T* sp;
    int filled_size;
    T* bp;


};

//-----------------------------------------//
// don`t build with it in cpp file #TODO
// i find, linking templates is magic, will write stack here and guess how list linked


template<typename T>
void stack<T>::clear() {
    while(filled_size)
        pop();
}

template<typename T>
void stack<T>::pop() {
    if (filled_size == 0)
        throw std::runtime_error("stack is already clear");
    filled_size--;
    sp -= sizeof(T);
}

template<typename T>
void stack<T>::print() {
    for (int idx = 0; idx < filled_size; idx++)
    {
        std::cout << *sp << std::endl;
        this->sp -= sizeof(T);
    }
    this->sp = bp + filled_size * sizeof(T);
}

template<typename T>
stack<T>::stack(stack &other) {
    // #TODO сделать сравнения по типу данных

    this->stack_size = other.stack_size;
    this->filled_size = other.filled_size;
    if (other.sp == nullptr)
        this->sp = nullptr;
    this->bp = new T[stack_size];

    for (int idx = 0; idx < filled_size; idx++)
    {
        this->sp = this->bp + idx * sizeof(T);
        *this->sp = *(other.bp + idx * sizeof(T));
    }
}


template<typename T>
bool stack<T>::operator==(stack &other) {
    if (this->filled_size != other.filled_size or this->stack_size != other.stack_size)
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
    if (sp == nullptr)
        throw std::runtime_error("stack is empty, can`t return top");
    return (*sp);
}

template<typename T>
stack<T>::~stack() {
    delete[] bp;
}

template<typename T>
stack<T>::stack() {
    filled_size = 0;
    stack_size = START_DEPTH;
    bp = new T[stack_size];
    sp = bp;
}

template<typename T>
stack<T>::stack(int depth) {
    filled_size = 0;
    stack_size = depth;
    bp = new T[depth];
}

template <typename T>
void stack<T>::push(T data) {
    if (filled_size == stack_size)
        throw std::runtime_error("stack overflow");
    else{
        sp = bp + filled_size * sizeof (T);
        *sp = data;
        filled_size++;
    }
    //std::cout << "push " << bp[filled_size] << " sp: " << *sp << std::endl; //del #TODO ????
}

#endif //ATD_STACK_H
