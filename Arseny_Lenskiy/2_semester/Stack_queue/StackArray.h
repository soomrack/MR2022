#ifndef STACKARRAY_H
#define STACKARRAY_H

#include "StackExceptions.h"

template<class T>
class StackArray {
public:

    ~StackArray() { //Деструктор
        delete array;
    }

    StackArray(int size = 100) : //Конструктор
            size(size),
            top(-1) {
        if (size <= 0) {
            throw WrongStackSize();
        } else {
            array = new T[size];
        }
    }

    void push(const T &e);      // Добавление элемента в стек
    T pop();                    // Удаление верхнего элемента
    bool isEmpty();             // Проверка стека на пустоту

private:
    int size;
    T *array;
    int top;
};

template<class T>
void StackArray<T>::push(const T &e) {
    if (top == size - 1) {
        throw StackOverflow(); // нет места для нового элемента
    } else {
        array[++top] = e;
    } // занесение элемента в стек
}

template<class T>
T StackArray<T>::pop() {
    if (top == -1) {
        throw StackUnderflow();
    } else {
        T temp = array[top];
        --top;
        return temp;
    }
}

template<class T>
bool StackArray<T>::isEmpty() {
    return top == -1;
}

#endif