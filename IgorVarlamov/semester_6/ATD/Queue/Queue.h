
#ifndef MR2022_QUEUE_H
#define MR2022_QUEUE_H

class QUEUE_ERROR : public std::domain_error
{
public:
    explicit QUEUE_ERROR(const char *const str) : std::domain_error(str){};
};
QUEUE_ERROR OVERFLOWED("Out of range");
QUEUE_ERROR EMPTY("Queue is empty");
QUEUE_ERROR BADALLOC("Memory has not been allocated");

template <typename T>
class Queue
{
private:
    T *data; // массив для хранения элементов очереди
    int head;
    int tail;
    size_t capacitance; // вместимость очереди
    size_t size;        // массив для хранения элементов очереди

public:
    Queue();                  // пустой конструктор
    explicit Queue(size_t);   // конструктор с заданной емкостью стека
    Queue(const Queue &);     // конструктор копирования
    Queue(Queue &&) noexcept; // конструктор переноса
    ~Queue();                 // деструктор

    bool is_full();  // проверяет, заполнена ли очередь
    bool is_empty(); // проверяет, пуста ли очередь

    void enqueue(T num);
    void dequeue();
    T front(); // возвращает значение первого элемента очереди, не удаляя его
    T rear();

    unsigned int get_size(); // возвращает текущий размер очереди
    void clear();            // очищает очередь

    T &operator[](unsigned);
};

template <typename T>
Queue<T>::Queue()
{
    capacitance = 0;
    data = nullptr;
    head = -1;
    tail = -1;
    size = 0;
}

template <typename T>
Queue<T>::Queue(size_t num)
{
    capacitance = num;
    data = new T[capacitance];
    if (!data)
        throw BADALLOC;
    head = -1;
    tail = -1;
    size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &q) : head(q.head), tail(q.tail), size(q.size), capacitance(q.capacitance)
{
    data = new T[capacitance];
    if (!data)
        throw BADALLOC;
    memcpy(data, q.data, sizeof(capacitance));
}

template <typename T>
Queue<T>::Queue(Queue<T> &&q) noexcept : head(q.head), tail(q.tail), size(q.size), capacitance(q.capacitance)
{
    data = q.data;
    q.head = -1;
    q.tail = -1;
    q.size = 0;
    q.capacitance = 0;
    q.data = nullptr;
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] data;
}

template <typename T> //
bool Queue<T>::is_full()
{
    return size == capacitance;
}

template <typename T>
bool Queue<T>::is_empty()
{
    return size == 0;
}

template <typename T> //
void Queue<T>::enqueue(T num)
{
    if (is_full())
        throw OVERFLOWED;
    if (is_empty())
        head = 0;
    size++;
    tail = (tail + 1) % capacitance;
    data[tail] = num;
    
}

template <typename T>
void Queue<T>::dequeue() 
{
if (is_empty()) throw EMPTY;
    // Освобождаем память, занятую удаляемым элементом
    T deletedItem = data[head];
    data[head] = NULL;
    // Перемещаем указатель на начало очереди на следующий элемент
    if (head == tail) {
        // Очередь содержала только один элемент
        head = tail = -1;
    } else {
        head = (head + 1) % capacitance;
    }
    size--;
    std::cout << "Deleted item: " << deletedItem << std::endl;
}



template <typename T>
T Queue<T>::front()
{
    if (is_empty())
        throw EMPTY;
    return data[head];
}

template <typename T>
T Queue<T>::rear()
{
    if (is_empty())
        throw EMPTY;
    return data[tail];
}

template <typename T>
unsigned int Queue<T>::get_size()
{
    return size;
}

// template <typename T>
// void Queue<T>::clear()
// {
//     if (is_empty())
//         throw EMPTY;
//     while (!is_empty())
//     {
//         pop();
//     }
// }

template <typename T>
T &Queue<T>::operator[](unsigned int idx)
{
    if (idx > size)
        throw OVERFLOWED;
    return data[idx];
}

#endif // MR2022_QUEUE_H
