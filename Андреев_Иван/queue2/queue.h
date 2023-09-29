#ifndef MR2022_QUEUE
#define MR2022_QUEUE

#include <iostream>

class queue_error : public std::domain_error {
public:
    queue_error(const char* const message) : std::domain_error(message) {}
};

queue_error empty("queue is empty");
queue_error full("queue is full");

class queue {
private:
    int* data;
    int capacity;
    int head;
    int tail;
    int current_size;
public:
    queue(int capacity);
    ~queue();
    void push(int x);
    int pop();
    void print();
    bool is_empty();
    bool is_full();
    unsigned int get_size();
};

queue::queue(int capacity) {
    this->capacity = capacity;
    data = new int[capacity];
    head = 0;
    tail = 0;
    current_size = 0;
}

queue::~queue() {
    delete[] data;
    std::cout << "Destructor\n";
}

bool queue::is_empty() {
    return current_size == 0;
}

bool queue::is_full() {
    return current_size == capacity;
}

void queue::push(int x) {
    if (is_full()) {
        throw full;
    }

    data[tail] = x;
    tail = (tail + 1) % capacity;
    current_size++;
}

int queue::pop() {
    if (is_empty()) {
        throw empty;
    }

    int value = data[head];
    head = (head + 1) % capacity;
    current_size--;
    return value;
}

unsigned int queue::get_size() {
    return current_size;
}

void queue::print() {
    if (is_empty()) {
        std::cout << "Queue is empty\n";
        return;
    }

    for (int i = 0; i < current_size; i++) {
        std::cout << data[(head + i) % capacity] << "\n";
    }
}

#endif // MR2022_QUEUE
