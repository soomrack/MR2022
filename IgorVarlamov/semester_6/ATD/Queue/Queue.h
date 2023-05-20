
#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H

class QUEUE_ERROR: public std::domain_error {
public:
   explicit QUEUE_ERROR(const char *const str) : std::domain_error(str) {};
};
QUEUE_ERROR OVERFLOWED("Out of range");
QUEUE_ERROR EMPTY("Queue is empty");
QUEUE_ERROR BADALLOC("Memory has not been allocated");

template <typename T>
class Queue {
private:
    T *data;                                        // массив для хранения элементов очереди
    int top;                                        // индекс первого элемента очереди
    int tail;                                       // индекс последнего элемента очереди                  
    size_t capacitance;                             // вместимость очереди
    size_t size;                                    // массив для хранения элементов очереди

public:
    Queue();                                        // пустой конструктор
    explicit Queue(size_t);                         // конструктор с заданной емкостью стека
    Queue(const Queue&);                            // конструктор копирования
    Queue(Queue&&) noexcept;                        // конструктор переноса        
    ~Queue();                                       // деструктор

    bool is_full();                                 // проверяет, заполнена ли очередь
    bool is_empty();                                // проверяет, пуста ли очередь
    
    void push(T num);                               // добавляет элемент в конец очереди
    T pop();                                        // удаляет первый элемент из очереди и возвращает его значение
    T get_top();                                    // возвращает значение первого элемента очереди, не удаляя его

    unsigned int get_size();                        // возвращает текущий размер очереди
    void clear();                                   // очищает очередь

    T& operator[](unsigned );
};


template <typename T>
Queue<T>::Queue() {
    capacitance = 0;
    data = nullptr;
    top = -1;
    tail = -1;
    size = 0;
}


template <typename T>
Queue<T>::Queue(size_t num) {
    capacitance = num;
    data = new T[capacitance];
    if (!data) throw BADALLOC;
    top = -1;
    tail = -1;
    size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T> &q) : top(q.top), tail(q.tail), size(q.size), capacitance(q.capacitance) {
    data = new T[capacitance];
    if (!data) throw BADALLOC;
    memcpy(data,q.data,sizeof(capacitance));
}


template<typename T>
Queue<T>::Queue(Queue<T> &&q) noexcept :top(q.top) ,tail(q.tail), size(q.size), capacitance(q.capacitance) {
    data = q.data;
    q.top = -1;
    q.tail = -1;
    q.size = 0;
    q.capacitance = 0;
    q.data = nullptr;
}

template <typename T>
Queue<T>::~Queue() {
    delete[] data;
}

template <typename T>                   // 
bool Queue<T>::is_full() {
    return tail == capacitance - 1;
}

template <typename T>
bool Queue<T>::is_empty() {
    return top == -1 || top > tail;
}

template <typename T>//
void Queue<T>::push(T num) {
    if (is_full()) throw OVERFLOWED;
    data[++tail] = num;
    size++;
    if (top == -1) {
        top = 0;
    }
}

template <typename T>//
T Queue<T>::pop() {
    if (is_empty()) throw EMPTY;
    size--;
    T element = data[top++];
    if (size == 0) 
    {
        top = -1;
        tail = -1;
    }
    return element;
}

template <typename T>
T Queue<T>::get_top() {
    if (is_empty()) throw EMPTY;
    return data[top];
}

template <typename T>
unsigned int Queue<T>::get_size()
{
    return size;
}


template <typename T>
void Queue<T>::clear() {
    if (is_empty()) throw EMPTY;
    while (!is_empty()) {
        pop();
    }
    top = -1;
    tail = -1;
}

template<typename T>
T& Queue<T>::operator[](unsigned int idx)
{
    if (idx > size) throw OVERFLOWED;
    return data[idx];
}

#endif //MR2022_QUEUE_H
