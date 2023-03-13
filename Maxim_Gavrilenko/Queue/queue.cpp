#include <iostream>
template <typename T>
class Queue {
private:
    T *arr;
    int top;
    int tail;
    unsigned int maxSize;
    unsigned int size;

public:

    Queue(int);

    ~Queue();

    bool isFull();

    bool isEmpty();

    void push(T num);

    T pop();

    T get_top();

    T get_tail();

    int current_size();

    void dequeue();

    void clean();

    void print();
};

template <typename T>
Queue<T>::Queue(int num) {
    arr = new T[num];
    top = -1;
    tail = -1;
    size = 0;
    maxSize = num;
}

template <typename T>
Queue<T>::~Queue() {
    delete[] arr;
}

template <typename T>
bool Queue<T>::isFull() {
    return tail == maxSize - 1;
}

template <typename T>
bool Queue<T>::isEmpty() {
    return top == -1 || top > tail;
}

template <typename T>
void Queue<T>::push(T num) {
    if (isFull()) throw std::domain_error("Queue is Full");
    arr[++tail] = num;
    size++;
    if (top == -1) top = 0;
}

template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    size--;
    return arr[top++];
}

template <typename T>
T Queue<T>::get_top() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    return arr[top];
}

template <typename T>
T Queue<T>::get_tail() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    return arr[tail];
}

template <typename T>
int Queue<T>::current_size() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    return size;
}

template <typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    while (!isEmpty()) {
        std:: cout << pop() << " ";
    }
}

template <typename T>
void Queue<T>::clean() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Queue<T>::print() {
    if (isEmpty()) throw std::domain_error("Queue is Empty");
    for(unsigned int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}

int main() {
    Queue<int> q(5);
    try {
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);
        std::cout << "Front element: " << q.get_top() << std::endl;
        std::cout << "Rear element: " << q.get_tail() << std:: endl;
        std::cout << "Current_size:" << q.current_size() << std:: endl;
        std::cout << "Print: "; q.print(); std:: cout << std:: endl;
        std::cout << std::endl;
        std::cout << "dequeue: "; q.dequeue(); std::cout << std:: endl;
    }
    catch (std::domain_error& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    return 0;
}
