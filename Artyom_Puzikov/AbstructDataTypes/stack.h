#ifndef ABSTRUCTDATATYPES_STACK_H
#define ABSTRUCTDATATYPES_STACK_H

#include <iostream>

template<class T>
class StackArray
{
private:
  unsigned int capacity;
  T *array;
  int top;

public:

  ~StackArray()
  { delete array; }

  StackArray(int size = 100);

  void push(T element);

  T pop();

  bool isEmpty();
};

template<class T>
StackArray<T>::StackArray(int size) : capacity(size), top(-1)
{
  if (size == 0)
  {
    std::cerr << "Invalid parameter\n";
  }

  array = new T[capacity];
}

template<class T>
void StackArray<T>::push(T element)
{
  if (top == capacity - 1)
  {
    std::cerr << "Overflow\n";
  }

  array[++top] = element;
}

template<class T>
T StackArray<T>::pop()
{
  if (top == -1)
  {
    std::cerr << "Empty\n";
  }

  T temp = array[top];
  --top;
  return temp;
}

template<class T>
bool StackArray<T>::isEmpty()
{
  return top == -1;
}

#endif