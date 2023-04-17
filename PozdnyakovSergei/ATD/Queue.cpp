#include <iostream>


class Queue {
    int *array;
    int capacity;
    int first;
    int last;
    int count;

public:
    Queue(int size);
    ~Queue();

    int pop();
    void push(int item);
    int upper();
    int size();
    bool is_empty();
    bool is_full();
};


class Queue_exceptions: public std::domain_error {
public:
    Queue_exceptions (const char* const error) : std::domain_error(error) {
    }
};


Queue_exceptions IS_EMPTY ("Error: queue is empty, you can't pop anything");
Queue_exceptions IS_FULL ("Error: queue if full, you can't push anything");


Queue::Queue(int size) {
    array = new int [size];
    capacity = size;
    first = 0;
    last = -1;
    count = 0;
}


Queue::~Queue() {
    delete[] array;
}


int Queue::pop() {
    if (is_empty()) {
        throw IS_EMPTY;
    }
    int element = array[first];
    first++;
    count--;
    return element;
}


void Queue::push(int item) {
    if (is_full()){
        throw IS_FULL;
    }
    last = (last + 1);
    array[last] = item;
    count++;
}


int Queue::upper() {
    if (is_empty()){
        throw IS_EMPTY;
    }
    return array[first];
}


int Queue::size() {
    return count;
}


bool Queue::is_empty() {
    return (size() == 0);
}


bool Queue::is_full() {
    return (size() == capacity);
}


int main() {
    Queue queue(4);

    queue.push(1);
    queue.push(2);

    queue.pop();
    queue.pop();

    if (queue.is_empty()) {
        throw IS_EMPTY;
    }

    if (queue.is_full()) {
        throw IS_FULL;
    }
}