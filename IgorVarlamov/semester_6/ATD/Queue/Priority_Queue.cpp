#include <iostream>
#include <stdexcept>

template <typename T>
struct QueueNode
{
    T data;
    int priority;
    QueueNode(T _data, int _priority) : data(_data), priority(_priority) {}
};

template <typename T>
class PriorityQueue
{
private:
    QueueNode *data;
    int size;
    int capacity;

public:
    PriorityQueue(int);
    ~PriorityQueue();
    void push(T, int);
    T pop();
    T top() const;
    bool empty() const;
    int getSize() const;

    void siftUp(int);
    void siftDown(int);
};

template <typename T>
PriorityQueue<T>::PriorityQueue(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->data = new QueueNode[capacity];
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] data;
}

template <typename T>
void PriorityQueue<T>::push(T element, int priority)
{
    if (size == capacity)
    {
        throw std::overflow_error("Priority queue is full");
    }
    data[size] = QueueNode(element, priority);
    siftUp(size);
    size++;
}

template <typename T>
T PriorityQueue<T>::pop()
{
    if (size == 0)
    {
        throw std::range_error("Priority queue is empty");
    }
    pri
        std::swap(data[0], data[size - 1]);
    size--;
    siftDown(0);
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
    return size == 0;
}
 
template <typename T>
int PriorityQueue<T>::getSize() const
{
    return size;
}

template <typename T>
void PriorityQueue<T>::siftUp(int index)
{
    if (index == 0)
        return; 
    int parent = (index - 1) / 2;
    if (data[index].priority > data[parent].priority)
    {
        std::swap(data[index], data[parent]);
        siftUp(parent);
    }
}

template <typename T>
void PriorityQueue<T>::siftDown(int index)
{
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;
    if (leftChild < size && data[leftChild].priority > data[largest].priority)
    {
        largest = leftChild;
    }
    if (rightChild < size && data[rightChild].priority > data[largest].priority)
    {
        largest = rightChild;
    }
    if (largest != index)
    {
        std::swap(data[index], data[largest]);
        siftDown(largest);
    }
}
