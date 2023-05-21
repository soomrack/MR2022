#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int *data;
    int capacity;
    int size;

public:
    PriorityQueue(int n);
    ~PriorityQueue();

    void push(int value);
    void pop();
    int top(); // Возвращает значение элемента с наибольшим приоритетом
    bool is_empty();
    bool is_full();
};

PriorityQueue::PriorityQueue(int n) {
    capacity = n;
    data = new int[capacity];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
}

void PriorityQueue::push(int value) {
    if (is_full()) {
        return;
    } else {
        int i = 0;
        while (i < size && data[i] > value) {
            i++;
        }
        for (int j = size; j > i; j--) {
            data[j] = data[j - 1];
        }
        data[i] = value;
        size++;
    }
}

void PriorityQueue::pop() {
    if (is_empty()) {
        return;
    } else {
        for (int i = 0; i < size; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

int PriorityQueue::top() {
    if (is_empty()) {
        return -1;
    } else {
        return data[0];
    }
}

bool PriorityQueue::is_empty() {
    return (size == 0);
}

bool PriorityQueue::is_full() {
    return (size == capacity);
}

int main() {
    PriorityQueue pq(5);

    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(10);
    pq.push(5);
    std::cout << "the highest priority element is " << pq.top() << std::endl;
    pq.pop();
    std::cout << "the highest priority element is " << pq.top() << std::endl;
    return 0;
}
