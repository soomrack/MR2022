#ifndef STACK_H
#define STACK_H

#include <cstddef>

template<class T>
class Stack
{

 private:

  class Node
  {

    friend class Stack;

   private:

    T data;
    Node* prev;

    Node() = delete;
    explicit Node(T data);
    ~Node() = default;
  };

  Node* tail;
  size_t stack_size;

 public:
  
  explicit Stack();
  ~Stack();
  Stack(const Stack& other);
  Stack& operator=(const Stack& other);

  void push(T data);
  T pop();
  size_t size() const;
  T top() const;
  bool empty() const;

};


template<class T>
Stack<T>::Node::Node(T data) : data(data), prev(nullptr) {};

template<class T>
Stack<T>::Stack() : tail(nullptr), stack_size(0) {};

template<class T>
Stack<T>::~Stack()
{
  while (!empty())
    pop();
}

template<class T>
Stack<T>::Stack(const Stack& other)
  : Stack()
{
  auto cache = new T[other.stack_size];
  int i = 0;
  for (Node* it = other.tail; it != nullptr; it = it->prev, ++i)
    cache[i] = it->data;
  
  for (i = other.stack_size - 1; i >= 0; --i)
    push(cache[i]);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other)
{
  if (this != &other)
  {
    while (!empty())
      pop();

    Stack tmp(other);
    tail = tmp.tail;
    stack_size = tmp.stack_size;

    tmp.stack_size = 0;
    tmp.tail = nullptr;
  }
  return *this;
}

template<class T>
void Stack<T>::push(T data)
{
  auto node = new Node(data);
  ++stack_size;
  if (tail == nullptr)
  {
    tail = node;
    return;
  }

  node->prev = tail;
  tail = node;
}

template<class T>
T Stack<T>::pop()
{
  if (tail == 0) return 0;
  T result = tail->data;
  Node* ptr = tail->prev;
  delete tail;
  --stack_size;
  tail = ptr;
  return result;
}

template<class T>
T Stack<T>::top() const
{
  return tail ? tail->data : 0;
}

template<class T>
size_t Stack<T>::size() const
{
  return stack_size;
}

template<class T>
bool Stack<T>::empty() const
{
  return !stack_size;
}

#endif  // STACK_H

