#ifndef ABSTRUCTDATATYPES_QUEUE_H
#define ABSTRUCTDATATYPES_QUEUE_H

#include <iostream>

template<class T>
class QueueArray
{
private:
  unsigned int capacity;
  T *array;
  int tail;
  int head;
  int size;

public:
  QueueArray(unsigned int size = 100);

  ~QueueArray()
  { delete array; }

  void push(T element);

  T pop();

  bool isEmpty();
};

template<class T>
QueueArray<T>::QueueArray(unsigned int size): capacity(size), tail(0), head(0), size(0)
{
  if (size <= 0)
  {
    std::cerr << "Invalid parameter\n";
  }
  array = new T[capacity];
}

template<class T>
void QueueArray<T>::push(T element)
{
  if (size == capacity)
  {
    std::cerr << "Overflowed\n";
  }
  array[tail] = element;
  tail = (tail + 1) % capacity;
  size++;
}

template<class T>
T QueueArray<T>::pop()
{
  T item;
  if (size == 0)
  {
    std::cerr << "Empty\n";
  }
  item = array[head];
  head = (head + 1) % capacity;
  size--;
  return item;
}

template<class T>
bool QueueArray<T>::isEmpty()
{
  return size == 0;
}

#endif