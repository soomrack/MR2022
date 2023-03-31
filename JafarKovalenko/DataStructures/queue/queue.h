#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>

template<class T>
class Queue
{

 private:
   
  class Node
  {
     
    friend class Queue;

   private:
    
    Node* prev;
    T data;

    Node() = delete;
    explicit Node(T data);
    ~Node() = default;

  };

  Node* head;
  Node* tail;
  size_t queue_size;

 public:  
  
  explicit Queue();
  ~Queue();
  Queue(const Queue& other);
  Queue& operator=(const Queue& other);

  void push(T data);
  T pop();
  T top() const;
  size_t size() const;
  bool empty() const;

};

template<class T>
Queue<T>::Node::Node(T data) : data(data), prev(nullptr) {};

template<class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), queue_size(0) {};

template<class T>
Queue<T>::~Queue()
{
  while (!empty())
    pop();
}

template<class T>
Queue<T>::Queue(const Queue& other)
  : Queue()
{
  for (Node* it = other.tail; it != nullptr; it = it->prev)
    push(it->data);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T> &other)
{
  if (this != &other)
  {
    while (!empty())
      pop();

    Queue tmp(other);
    tail = tmp.tail;
    queue_size = tmp.queue_size;

    tmp.queue_size = 0;
    tmp.tail = nullptr;
  }
  return *this;
}

template<class T>
void Queue<T>::push(T data)
{
  auto node = new Node(data);
  ++queue_size;
  if (tail == nullptr)
  {
    head = node;
    tail = node;
    return;
  }

  head->prev = node;
  head = node;
}

template<class T>
T Queue<T>::pop()
{
  if (tail == nullptr) return 0;
  T result = tail->data;
  Node* ptr = tail->prev;
  delete tail;
  --queue_size;
  tail = ptr;
  return result;
}

template<class T>
T Queue<T>::top() const
{
  return tail ? tail->data : 0;
}

template<class T>
size_t Queue<T>::size() const
{
  return queue_size;
}

template<class T>
bool Queue<T>::empty() const
{
  return !queue_size;
}

#endif  // QUEUE_H

