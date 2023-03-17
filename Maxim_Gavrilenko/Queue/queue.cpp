#include <iostream>
template <typename T>
class queue {
private:
    T *arr;
    int top;
    int tail;
    unsigned int maxSize;
    unsigned int size;

public:

    queue(int);

    ~queue();

    bool isFull();

    bool isEmpty();

    void push(T num);

    T pop();

    T get_top();

    T get_tail();

    void swap(queue<T>&);
    
    int current_size();

    void clear();

    void print();
};

template <typename T>
queue<T>::queue(int num) {
    arr = new T[num];
    top = -1;
    tail = -1;
    size = 0;
    maxSize = num;
}

template <typename T>
queue<T>::~queue() {
    delete[] arr;
}

template <typename T>
bool queue<T>::isFull() {
    return tail == maxSize - 1;
}

template <typename T>
bool queue<T>::isEmpty() {
    return top == -1 || top > tail;
}

template <typename T>
void queue<T>::push(T num) {
    if (isFull()) return;
    arr[++tail] = num;
    size++;
    if (top == -1) top = 0;
}

template <typename T>
T queue<T>::pop() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    size--;
    return arr[top++];
}

template <typename T>
T queue<T>::get_top() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    return arr[top];
}

template <typename T>
T queue<T>::get_tail() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    return arr[tail];
}

template <typename T>
int queue<T>::current_size() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    return size;
}


template <typename T>
void queue<T>::clear() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void queue<T>::print() {
    if (isEmpty()) throw std::domain_error("queue is Empty");
    for(unsigned int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}

template <typename T>
void queue<T>::swap(queue<T> & A) {
    if (A.size != size) throw std::domain_error("queue size is not equal");
    queue<T> temp(size);
    memcpy(temp.arr,A.arr,sizeof(T) * size);
    memcpy(A.arr,arr,sizeof(T) * A.size);
    memcpy(arr,temp.arr, sizeof(T) * size);
}
int main() {
    queue<int> q(5);
    queue<int> z(5);
    try {
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);
        z.push(30);
        z.push(20);
        z.push(1000);
        z.push(21);
        z.push(52);
        std::cout << "Front element: " << q.get_top() << std::endl;
        std::cout << "Rear element: " << q.get_tail() << std::endl;
        std::cout << "Current_size:" << q.current_size() << std::endl;
        std::cout << "Print q: ";
        q.print();
        std::cout << "Print z: ";
        z.print();
        q.swap(z);
        std::cout<<std::endl;
        std::cout << "Print q:";
        q.print();
        std::cout<<std::endl;
        std::cout << "Print z:";
        z.print();
        std::cout << std::endl;
        std::cout << std::endl;
        q.clear();
    }
    catch (std::domain_error& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    return 0;
}
