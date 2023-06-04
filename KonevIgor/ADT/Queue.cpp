#include <iostream>
#include <stdexcept>
#include <string>

class Queue_exception: public std::logic_error
{
public:
    explicit Queue_exception(const std::string& message):
            std::logic_error(message)
    {}
};

const int BASE_SIZE = 100;

template <typename T>
class Queue {
public:
    Queue();
    explicit Queue(unsigned long int);
    Queue(const Queue&);
    ~Queue();

    Queue& operator=(const Queue&);
    // TODO: конструктор перемещения и оператор перемещающего присваивания
    bool operator==(const Queue&);
    bool operator!=(const Queue& other) {return !(this == other);}

    void pop();
    void push(T);
    bool is_empty();
    bool is_full() {return (tail_pointer == size);}

    T get_head_elem();
    T get_tail_elem() {return this->data[this->tail_pointer - 1];}
    unsigned long int get_size() {return this->size;}
    unsigned long int get_taken_space()
        {return (tail_pointer - head_pointer + 1);}
    void print();

private:

    T* data;
    unsigned long int tail_pointer;
    unsigned long int head_pointer;
    unsigned long int size;

};

template<typename T>
Queue<T>::Queue():
        size(BASE_SIZE),
        tail_pointer(0),
        head_pointer(0)
{
    data = new T[size];
}

template<typename T>
Queue<T>::Queue(const unsigned long int size):
        size(size),
        tail_pointer(0),
        head_pointer(0)
{
    data = new T[size];
}

template<typename T>
Queue<T>::Queue(const Queue& other):
        size(other.size),
        head_pointer(other.head_pointer),
        tail_pointer(other.tail_pointer)
{
    this->data = new T[size];
    for (size_t idx = 0; idx < size; idx++) {
        this->data[idx] = other.data[idx];
    }

}

template<typename T>
Queue<T> &Queue<T>::operator=(const Queue& other) {
    if (this == &other) {
        return *this;
    }
    Queue temp(other);
    std::swap(this->size, temp.size);
    std::swap(this->head_pointer, temp.head_pointer);
    std::swap(this->tail_pointer, temp.tail_pointer);
    std::swap(this->data, temp.data);
    return *this;
}

template<typename T>
void Queue<T>::push(const T elem) {
    if (is_full()) throw Queue_exception("Queue overflow");
    this->data[(this->tail_pointer)++] = elem;
    if (!head_pointer) head_pointer = tail_pointer;
}

template<typename T>
void Queue<T>::pop() {
    if (is_empty()) throw Queue_exception("Queue is empty");
    this->data[(this->head_pointer) - 1] = 0;
    head_pointer++;
}

template<typename T>
Queue<T>::~Queue() {
    delete[] this->data;
}

template<typename T>
bool Queue<T>::operator==(const Queue& other) {
    if (this == &other) {
        return true;
    }
    if (this->size != other.size) {
        return false;
    }
    if ((this->head_pointer != other.head_pointer)
    || (this->tail_pointer != other.tail_pointer)) {
        return false;
    }
    for (size_t idx = 0; idx < this->sp; idx++) {
        if (std::abs(this->data[idx] - other.data[idx]) > 0.000001) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Queue<T>::is_empty() {
    if (head_pointer)
        return int(head_pointer - tail_pointer) > 0;
    else return true;
}

template<typename T>
T Queue<T>::get_head_elem() {
    if (is_empty()) throw Queue_exception("Queue is empty");
    return (this->data[this->head_pointer - 1]);
}

template<typename T>
void Queue<T>::print() {
    if (is_empty()) throw Queue_exception("Queue is empty");
    for (size_t idx = (head_pointer - 1); idx < this->tail_pointer; idx++) {
        std::cout << this->data[idx] << '\t';
    }
    std::cout << std::endl;
}

int main() {
    Queue<double> test;
    Queue<double> test2(100);
    for (int i = 0; i < 10; i++) {
        test2.push(i);
        std::cout << test2.get_tail_elem() << std::endl;
        std::cout << test2.get_taken_space() << std:: endl;
        test2.print();
    }
    for (int i = 0; i < 10; i++) {
        std::cout << test2.get_head_elem() << std::endl;
        test2.pop();
        if (i == 9) continue;
        test2.print();
    }
    std::cout << test.is_empty() << std::endl;
    std::cout << test.get_size() << std::endl;
    Queue<double> test3 = test;
    test3.print();
    return 0;
}