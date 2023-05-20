#include <iostream>
#include <stdexcept>

template<typename T>
struct QueueNode {
        T data;
        int priority;
        QueueNode(T _data, int _priority) : data(_data), priority(_priority) {}
    };

template<typename T>
class PriorityQueue {
private:
    QueueNode* data;
    int size;
    int capacity;

    void siftUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (data[index].priority > data[parent].priority) {
            std::swap(data[index], data[parent]);
            siftUp(parent);
        }
    }

    void siftDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;
        if (leftChild < size && data[leftChild].priority > data[largest].priority) {
            largest = leftChild;
        }
        if (rightChild < size && data[rightChild].priority > data[largest].priority) {
            largest = rightChild;
        }
        if (largest != index) {
            std::swap(data[index], data[largest]);
            siftDown(largest);
        }
    }

public:
    PriorityQueue(int capacity = 100) {
        this->size = 0;
        this->capacity = capacity;
        this->data = new QueueNode[capacity];
    }

    ~PriorityQueue() {
        delete[] data;
    }

    void push(T element, int priority) {
        if (size == capacity) {
            throw std::overflow_error("Priority queue is full");
        }
        data[size] = QueueNode(element, priority);
        siftUp(size);
        size++;
    }

    void pop() {
        if (size == 0) {
            throw std::range_error("Priority queue is empty");
        }
        std::swap(data[0], data[size - 1]);
        size--;
        siftDown(0);
    }

    T top() const {
        if (size == 0) {
            throw std::range_error("Priority queue is empty");
        }
        return data[0].data;
    }

    bool empty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

};