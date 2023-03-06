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
        std::cout << "Empty";
    }
    int element = array[first];
    std::cout << "Remove: " << element << std::endl;
    first = (first + 1) % capacity;
    count--;
    return element;
}


void Queue::push(int item) {
    if (full()){
        std::cout << "Owerflow";
    }

    std::cout << "Insert: " << item << std::endl;
    last = (last + 1);
    array[last] = item;
    count++;
}


int Queue::upper() {
    if (empty()){
        std::cout << "Empty";
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
        std::cout << "Empty" << std::endl;
    }
    else {
        std::cout << "Not empty" << std::endl;
    }

    if (queue.full()) {
        std::cout << "Full" << std::endl;
    }
    else {
        std::cout << "Not full" << std::endl;
    }
}