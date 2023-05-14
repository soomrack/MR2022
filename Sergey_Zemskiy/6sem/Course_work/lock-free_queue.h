

#ifndef QUEUE3_QUEUE3_H
#define QUEUE3_QUEUE3_H

#include <iostream>
#include <cstring>
#include <type_traits>


template<typename T, const unsigned int CAPACITY>
class Queue {
private:
    long front;
    long rear;
    std::aligned_storage_t<sizeof(T), alignof(T)> queue[CAPACITY];
    long temp_front;
    T output_val;

public:
    bool empty ;

public:
    Queue() : front(0), rear(0), empty(true) {} ;
    Queue(const Queue &other) ;
    ~Queue() = default;

public:
    Queue& operator=(const Queue &other);

private: // private for impossibility user's "breaking" structure of class
    const T& operator[](unsigned int pos) const {return *std::launder(reinterpret_cast<const T*>(&queue[pos]));}

public:
    bool push(const T& new_val);
    T pop();
};


template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>::Queue(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        ::new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*> (&queue[index]))
        T(*std::launder(reinterpret_cast<const T*>(&other.queue[index])));
    }
    front = other.front;
    rear = other.rear;
    empty = other.empty;
}

template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>& Queue<T, CAPACITY>::operator=(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        ::new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*> (&queue[index]))
        T(*std::launder(reinterpret_cast<const T*>(&other.queue[index])));
    }
    front = other.front;
    rear = other.rear;
    empty = other.empty;
    return *this;
}

template<typename T, const unsigned int CAPACITY>
bool Queue<T, CAPACITY>::push(const T &new_val) {
    if (front == (rear + 1)% CAPACITY)  return false;
    ::new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*>
    (&queue[(front == rear) && empty? rear: (rear + 1) % CAPACITY])) T(new_val);
    rear = ((front == rear) && empty) ? rear: (rear + 1) % CAPACITY;
    empty = false;
    return true;
}

template<typename T, const unsigned int CAPACITY>
T Queue<T, CAPACITY>::pop() {
    if (empty) return T();
    temp_front = front;
    if (front == rear) empty = true;
    else front = (front + 1) % CAPACITY;
    ::new(&output_val) T(*std::launder(reinterpret_cast<const T*>(&queue[temp_front])));
    memset(&queue[temp_front], 0, sizeof(T));
    return output_val;
}

#endif //QUEUE3_QUEUE3_H
