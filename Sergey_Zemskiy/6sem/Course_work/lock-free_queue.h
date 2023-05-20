

#ifndef QUEUE3_QUEUE3_H
#define QUEUE3_QUEUE3_H

#include <iostream>
#include <cstring>
#include <type_traits>


template<typename T, const unsigned int CAPACITY>
class Queue {
private:
    long head;
    long tail;
    std::aligned_storage_t<sizeof(T), alignof(T)> queue[CAPACITY];

public:
    bool empty;

public:
    Queue() : head(0), tail(0), empty(true) {};
    Queue(const Queue &other);
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
    head = other.head;
    tail = other.tail;
    empty = other.empty;
}

template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>& Queue<T, CAPACITY>::operator=(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        ::new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*> (&queue[index]))
        T(*std::launder(reinterpret_cast<const T*>(&other.queue[index])));
    }
    head = other.head;
    tail = other.tail;
    empty = other.empty;
    return *this;
}

template<typename T, const unsigned int CAPACITY>
bool Queue<T, CAPACITY>::push(const T &new_val) {
    if (head == (tail + 1)% CAPACITY)  return false;
    new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*>
    (&queue[empty? tail: (tail + 1) % CAPACITY])) T(new_val);
    tail = empty ? tail: (tail + 1) % CAPACITY;
    empty = false;
    return true;
}

template<typename T, const unsigned int CAPACITY>
T Queue<T, CAPACITY>::pop() {
    if (empty) return T();
    long temp_head = head;
    if (head == tail) empty = true;
    else head = (head + 1) % CAPACITY;
    T output_val;
    new(&output_val) T(*std::launder(reinterpret_cast<const T*>(&queue[temp_head])));
    memset(&queue[temp_head], 0, sizeof(T));
    return output_val;
}

#endif //QUEUE3_QUEUE3_H
