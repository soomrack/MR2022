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
    bool empty();
    bool full();
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
    if (empty()) {
        throw IS_EMPTY;
    }
    int element = array[first];
    std::cout << "Remove: " << element << std::endl;
    first = (first + 1);
    count--;
    return element;
}


void Queue::push(int item) {
    if (full()){
        throw IS_FULL;
    }

    std::cout << "Insert: " << item << std::endl;
    last = (last + 1);
    array[last] = item;
    count++;
}


int Queue::upper() {
    if (empty()){
        throw IS_EMPTY;
    }
    return array[first];
}


int Queue::size() {
    return count;
}


bool Queue::empty() {
    return (size() == 0);
}


bool Queue::full() {
    return (size() == capacity);
}


int main() {
    Queue queue(10);

    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);

    std::cout <<"First " << queue.upper() << std::endl;
    std::cout << "Size " << queue.size() << std::endl;

    queue.pop();
    queue.pop();

    std::cout << "First: " << queue.upper() << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;

    queue.push(10);
    queue.push(20);

    std::cout << "First: " << queue.upper() << std::endl;
    std::cout << "Size: " << queue.size() << std::endl;

    if (queue.empty()) {
        throw IS_EMPTY;
    }

    if (queue.full()) {
        throw IS_FULL;
    }

}