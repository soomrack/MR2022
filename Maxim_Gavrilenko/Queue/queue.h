
#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H
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
#endif //MR2022_QUEUE_H
