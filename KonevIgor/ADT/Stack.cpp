#include <iostream>
#include <stdexcept>
#include <string>

class Stack_exception: public std::logic_error
{
public:
    explicit Stack_exception(const std::string& message):
        std::logic_error(message)
    {}
};

const int BASE_SIZE = 100;

template <typename T>
class Stack {
public:
    Stack();
    explicit Stack(unsigned long int);
    Stack(const Stack&);
    ~Stack();

    Stack& operator=(const Stack&);
    bool operator==(const Stack&);
    bool operator!=(const Stack& other) {return !(this == other);}

    void pop();
    void push(T);
    unsigned long int get_size() const {return this->size;}
    unsigned long int get_free_space() const {return (size - sp);}
    T get_peak() const {return data[sp - 1];}

    void print();

private:

    T* data;
    unsigned long int sp;
    unsigned long int size;

};

template<typename T>
Stack<T>::Stack():
    size(BASE_SIZE),
    sp(0)
{
    data = new T[size];
}

template<typename T>
Stack<T>::Stack(const unsigned long int size):
    size(size),
    sp(0)
{
    data = new T[size];
}

template<typename T>
Stack<T>::Stack(const Stack& other):
    size(other.size),
    sp(other.sp)
{
    this->data = new T[size];
    for (size_t idx = 0; idx < size; idx++) {
        this->data[idx] = other.data[idx];
    }
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack& other) {
    if (this == &other) {
        return *this;
    }
    Stack temp(other);
    std::swap(this->size, temp.size);
    std::swap(this->sp, temp.sp);
    std::swap(this->data, temp.data);
    return *this;
}

template<typename T>
void Stack<T>::push(const T elem) {
    if (sp == size) throw Stack_exception("Stack overflow!");
    this->data[this->sp] = elem;
    sp++;
}

template<typename T>
void Stack<T>::pop() {
    sp ? sp-- : sp = 0;
    // обязательно ли бросать исключение?
    this->data[sp] = 0;
    // или нужно как-то по-другому обнулять
}

template<typename T>
Stack<T>::~Stack() {
    delete[] this->data;
}

template<typename T>
bool Stack<T>::operator==(const Stack& other) {
    if (this == &other) {
        return true;
    }
    if (this->size != other.size) {
        return false;
    }
    if (this->sp != other.sp) {
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
void Stack<T>::print() {
    for (size_t idx = 0; idx < this->sp; idx++) {
        std::cout << this->data[idx] << '\t';
    }
    std::cout << std::endl;
}

int main() {
    Stack<double> test;
    printf("%lu\n", test.get_size());
    for (size_t idx = 0; idx < 10; idx++) {
        test.push((double)idx);
    }
    test.print();
    Stack<double> test2(10);
    while (test2.get_free_space()) {
        test2.push(test2.get_free_space() - 1);
    }
    test2.print();
    Stack<double> test3 = test2;
    test3.pop();
    test3.print();
    test3.push(10);
    test3.print();
    std::cout << test.get_peak() << std::endl;
    test3.push(0);
    return 0;
}