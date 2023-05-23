#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <cstddef>

template<class T>
class PriorityQueue
{

private:

    class Node
    {

        friend class PriorityQueue;

    private:

        Node* prev;
        T data;
        uint32_t priority;

        explicit Node(T data, uint32_t priority) : data(data), priority(priority), prev(nullptr) {}
        ~Node() = default;

    };

    Node* head;
    Node* tail;
    size_t queue_size{};

public:

    explicit PriorityQueue() : head(nullptr), tail(nullptr), queue_size(0) {}
    ~PriorityQueue() { while (!isEmpty()) pop(); }
    PriorityQueue(const PriorityQueue& other) = delete;
    PriorityQueue& operator=(const PriorityQueue& other) = delete;

    void push(T data, uint32_t priority);
    T pop();
    T top() const;
    size_t size() const;
    bool isEmpty() const;

};

template<class T>
void PriorityQueue<T>::push(T data, uint32_t priority)
{
    auto pushed = new Node(data, priority);
    ++queue_size;
    if (tail == nullptr)
    {
        head = pushed;
        tail = pushed;
        return;
    }

    Node* node = head;
    while (node->priority < pushed->priority)
        node = node->next;

    node->prev = pushed;
    if (node == head)
        head = pushed;
}

template<class T>
T PriorityQueue<T>::pop()
{
    if (tail == nullptr) return 0;
    T result = tail->data;
    Node* ptr = tail->prev;
    delete tail;
    --queue_size;
    tail = ptr;
    return result;
}

template<class T>
T PriorityQueue<T>::top() const
{
    return tail ? tail->data : 0;
}

template<class T>
size_t PriorityQueue<T>::size() const
{
    return queue_size;
}

template<class T>
bool PriorityQueue<T>::isEmpty() const
{
    return !queue_size;
}

#endif // PRIORITY_QUEUE_H
