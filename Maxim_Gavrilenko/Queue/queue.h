
#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H

class QUEUE_ERROR: public std:: domain_error {
public:
    QUEUE_ERROR(const char *const str) : std::domain_error(str) {};
};
QUEUE_ERROR OVERFLOWED("Out of range");
QUEUE_ERROR EMPTY("Queue is empty");
QUEUE_ERROR BADALLOC("Memory has not been allocated");

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

    bool is_full();
    bool is_empty();
    void push(T num);
    T pop();
    T get_top();
    T get_tail();
    void swap(queue<T>&);
    unsigned int get_size();
    void clear();

    T& operator[](unsigned );
};


template <typename T>
queue<T>::queue(int num) {
    arr = new T[num];
    if (!arr) throw BADALLOC;
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
bool queue<T>::is_full() {
    return tail == maxSize - 1;
}

template <typename T>
bool queue<T>::is_empty() {
    return top == -1 || top > tail;
}

template <typename T>
void queue<T>::push(T num) {
    if (is_full()) throw OVERFLOWED;
    arr[++tail] = num;
    size++;
    if (top == -1) top = 0;
}

template <typename T>
T queue<T>::pop() {
    if (is_empty()) throw EMPTY;
    size--;
    return arr[top++];
}

template <typename T>
T queue<T>::get_top() {
    if (is_empty()) throw EMPTY;
    return arr[top];
}

template <typename T>
T queue<T>::get_tail() {
    if (is_empty()) throw EMPTY;
    return arr[tail];
}

template <typename T>
unsigned int queue<T>::get_size()
{
    if (is_empty()) throw EMPTY;
    return size;
}


template <typename T>
void queue<T>::clear() {
    if (is_empty()) throw EMPTY;
    while (!is_empty()) {
        pop();
    }
}

template <typename T>
void queue<T>::swap(queue<T> & A) {
    if (A.size != size) throw std::domain_error("queue size is not equal");
    queue<T> temp(size);
    memcpy(temp.arr,A.arr,sizeof(T) * size);
    memcpy(A.arr,arr,sizeof(T) * A.size);
    memcpy(arr,temp.arr, sizeof(T) * size);
}

template<typename T>
T& queue<T>::operator[](unsigned int idx)
{
    return arr[idx];
}
#endif //MR2022_QUEUE_H
