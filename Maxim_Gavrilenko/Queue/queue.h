
#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H

class QUEUE_ERROR: public std:: domain_error {
public:
   explicit QUEUE_ERROR(const char *const str) : std::domain_error(str) {};
};
QUEUE_ERROR OVERFLOWED("Out of range");
QUEUE_ERROR EMPTY("Queue is empty");
QUEUE_ERROR BADALLOC("Memory has not been allocated");

template <typename T>
class queue {
private:
    T *data;
    int top;
    int tail;
    size_t capacity;
    size_t size;

public:
    explicit queue(size_t);
    queue(const queue&);
    queue(queue&&) noexcept;

    queue& operator=(const queue&);
    queue& operator=(queue&&) noexcept;
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
queue<T>::queue(size_t num) {
    capacity = num;
    data = new T[capacity];
    if (!data) throw BADALLOC;
    top = -1;
    tail = -1;
    size = 0;

}

template <typename T>
queue<T>::~queue() {
    delete[] data;
}

template <typename T>
bool queue<T>::is_full() {
    return tail == capacity - 1;
}

template <typename T>
bool queue<T>::is_empty() {
    return top == -1 || top > tail;
}

template <typename T>
void queue<T>::push(T num) {
    if (is_full()) throw OVERFLOWED;
    data[++tail] = num;
    size++;
    if (top == -1) top = 0;
}

template <typename T>
T queue<T>::pop() {
    if (is_empty()) throw EMPTY;
    size--;
    return data[top++];
}

template <typename T>
T queue<T>::get_top() {
    if (is_empty()) throw EMPTY;
    return data[top];
}

template <typename T>
T queue<T>::get_tail() {
    if (is_empty()) throw EMPTY;
    return data[tail];
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
    memcpy(temp.data,A.data,sizeof(T) * size);
    memcpy(A.data,data,sizeof(T) * A.size);
    memcpy(data,temp.data, sizeof(T) * size);
}

template<typename T>
T& queue<T>::operator[](unsigned int idx)
{
    if (idx > size) throw OVERFLOWED;
    return data[idx];
}

template<typename T>
queue<T>::queue(const queue<T> &q) : top(q.top), tail(q.tail), size(q.size), capacity(q.capacity) {
    data = new T[capacity];
    if (!data) throw BADALLOC;
    memcpy(data,q.data,sizeof(capacity));
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T> &q) {
    if (this == &q) return *this;
    top = q.top;
    tail = q.tail;
    size = q.size;
    capacity = q.capacity;
    data = new T[capacity];
    if (!data) throw BADALLOC;
    memcpy(data,q.data,sizeof(capacity));
}

template<typename T>
queue<T>::queue(queue<T> &&q) noexcept :top(q.top) ,tail(q.tail), size(q.size), capacity(q.capacity) {
    data = q.data;
    q.top = -1;
    q.tail = -1;
    q.size = NULL;
    q.capacity =NULL;
    q.data = nullptr;
}

template<typename T>
queue<T>& queue<T>::operator=(queue<T> &&q) noexcept {
    if (this == &q) return *this;
    top = q.top;
    tail = q.tail;
    size = q.size;
    capacity = q.capacity;
    data = q.data;
    q.top = -1;
    q.tail = -1;
    q.size = NULL;
    q.capacity =NULL;
    q.data = nullptr;
}

#endif //MR2022_QUEUE_H
