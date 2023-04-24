
#ifndef QUEUE_LOCK_FREE_QUEUE_LOCK_FREE_H
#define QUEUE_LOCK_FREE_QUEUE_LOCK_FREE_H


#include <iostream>






template<class T, const unsigned int CAPACITY>
class Queue {
private:
    std::aligned_storage_t<sizeof(T), alignof(T)> queue[CAPACITY];
    long front;
    long rear;
    //T queue[CAPACITY];

public:
    Queue() : front(-1), rear(-1), queue() {} ;
    Queue(const Queue &other) ;
    ~Queue() = default;

public:
    Queue& operator=(const Queue &other);
    const T& operator[](std::size_t pos) const
    {
        // Note: std::launder is needed after the change of object model in P0137R1
        return *std::launder(reinterpret_cast<const T*>(&queue[pos]));
    }

public:
    //bool push(const T& new_val);
    template<typename ...Args>
    bool push(Args&&... new_val) {
        if (is_full()) return false;
        if (front == -1) front = 0; //if push first element: front = rear = 0
        rear = (rear + 1) % CAPACITY;
        ::new(&queue[rear]) T(std::forward<Args>(new_val)...);
        //*(new (&queue[rear]) T) = new_val;
        /*T* ptr = new (&queue[rear]) T;
        *ptr = new_val;
        queue[rear] = (new_val);*/
        return true;
    }
    bool print();
    bool pop();
    T first_element();
    bool is_empty(); // isn't necessary function, but comfortable for using
    bool is_full();  // isn't necessary function, but comfortable for using
};


template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>::Queue(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        queue[index] = (other.queue[index] );
    }
    front = other.front;
    rear = other.rear;
}

template<typename T, const unsigned int CAPACITY>
Queue<T, CAPACITY>& Queue<T, CAPACITY>::operator=(const Queue &other) {
    for (int index = 0; index < CAPACITY; index++) {
        queue[index] (other.queue[index]);
    }
    front = other.front;
    rear = other.rear;
    return *this;
}

//template<typename T, unsigned int CAPACITY>


template<typename T, unsigned int CAPACITY>
bool Queue<T, CAPACITY>::print() {
    if (is_empty()) {
        std::cout << "Queue is empty" << std::endl;
        return false;
    }
    for (int index = front; index != rear; index = (index + 1) % CAPACITY) {
        std::cout << queue[index] << " ";
    }
    std::cout << queue[rear] << " " << std::endl;
    return true;
}

template<typename T, unsigned int CAPACITY>
bool Queue<T, CAPACITY>::pop() {
    if (is_empty()) return false;
    T* poin;
    poin = queue[front];
    poin->~T();
    //delete  &queue[front];
    //queue[front] = T() ;
    //std::destroy_at(std::launder(reinterpret_cast<T*>(&queue[front])));
    if (front == rear) { // if pop last element: update queue
        front = rear = -1;
    }
    else front = (front + 1) % CAPACITY;
    return true;
}

template<typename T, const unsigned int CAPACITY>
T Queue<T, CAPACITY>::first_element() {
    if (is_empty()) return T();
    return queue[front];
}

template<typename T, const unsigned int CAPACITY>
bool Queue<T, CAPACITY>::is_empty() {
    return (front == -1);
}

template<typename T, const unsigned int CAPACITY>
bool Queue<T, CAPACITY>::is_full() {
    return ((front == rear + 1) || (front == 0 && rear + 1 == CAPACITY));
}




#endif //QUEUE_LOCK_FREE_QUEUE_LOCK_FREE_H
