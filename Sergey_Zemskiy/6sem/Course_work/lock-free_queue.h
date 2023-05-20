

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
    Queue() : head(-1), tail(0) {};
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
}

template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>& Queue<T, CAPACITY>::operator=(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        ::new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*> (&queue[index]))
        T(*std::launder(reinterpret_cast<const T*>(&other.queue[index])));
    }
    head = other.head;
    tail = other.tail;
    return *this;
}

template<typename T, const unsigned int CAPACITY>
bool Queue<T, CAPACITY>::push(const T &new_val) {
    if (head == tail)  return false;
    new(static_cast<std::aligned_storage_t<sizeof(T), alignof(T)>*> (&queue[tail])) T(new_val);
    long prev_tail = tail;
    tail = (tail + 1) % CAPACITY;
    if (head == -1) head = prev_tail;
    //если после проверки условия произойдёт метод "pop", может произойти ошибка
    return true;
}

template<typename T, const unsigned int CAPACITY>
T Queue<T, CAPACITY>::pop() {
    if (head == -1) return T();
    T output_val;
    new(&output_val) T(*std::launder(reinterpret_cast<const T*>(&queue[head])));
    memset(&queue[head], 0, sizeof(T));
    head = (head + 1) % CAPACITY;
    if (head == tail) head = -1;
    //если после проверки условия произойдёт метод "pop", может произойти ошибка
    return output_val;
}

#endif //QUEUE3_QUEUE3_H
