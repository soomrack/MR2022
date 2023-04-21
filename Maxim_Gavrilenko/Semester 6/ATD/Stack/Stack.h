
#ifndef MR2022_stack_H
#define MR2022_stack_H

class STACK_ERROR: public std::domain_error
{
public:
    STACK_ERROR(const char* const str): std::domain_error(str){};
};

STACK_ERROR BADALLOC("Memory is not allocate");
STACK_ERROR EMPTY("Stack is empty");
STACK_ERROR FULL("Stack is full");

template <typename T>
class stack {
private:
    size_t capacity;
    size_t size;
    int top;        // индекс верхнего элемента стека
    T* data;   // массив для хранения элементов стека
public:
    stack();
    explicit stack(size_t max);
    stack(const stack&);
    stack(stack&&) noexcept;
    stack& operator=(const stack&);
    stack& operator=(stack&&) noexcept;
    bool is_empty();
    bool is_full();
    unsigned int get_size();
    void push(T x);
    T pop();
    T peek();
    T& operator[](unsigned int idx) {return data[idx];};
};

template <typename T>
stack<T>::stack(size_t max) {
    capacity = max;
    data = new T[capacity];
    if (!data) throw BADALLOC;
    size = 0;
    top = -1;   // инициализация вершины пустым значением
}
template <typename T>
bool stack<T>::is_empty() {
    return top == -1;
}

template<typename T>
unsigned int stack<T>::get_size() {return size;}

template <typename T>
bool stack<T>::is_full(){
    return top == capacity - 1;
}

template <typename T>
void stack<T>::push(T x) {
    if (is_full()) throw FULL;
    top++;
    size++;
    data[top] = x;
}

template <typename T>
T stack<T>::pop() {
    if (is_empty()) throw EMPTY;
    size--;
    return data[top--];
}

template <typename T>
T stack<T>::peek() {
    if (is_empty()) throw EMPTY;
    return data[top];
}

template <typename T>
stack<T>::stack() {
    capacity = 0;
    size = 0;
    top = -1;
    data = nullptr;
}

template <typename T>
stack<T>::stack(const stack<T> & s) : capacity(s.capacity), size(s.size), top(s.top) {
    data = new T[capacity];
    if (!data) throw BADALLOC;
    memcpy(data,s.data,capacity);
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T> & s) {
    if(this == &s) return *this;
    capacity = s.capacity;
    size = s.size;
    top = s.top;
    data = new T[capacity];
    if(!data) throw EMPTY;
    memcpy(data,s.data,capacity);
    return *this;
}

template <typename T>
stack<T>::stack(stack<T> && s) noexcept : capacity(s.capacity), size(s.size),
                                          top(s.top), data(s.data) {
    s.capacity = NULL;
    s.size = NULL;
    s.top = -1;
    s.data = nullptr;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T> && s) noexcept {
    if (this == &s) return *this;
    capacity = s.capacity;
    size = s.size;
    top = s.top;
    data = s.data;
    s.capacity = NULL;
    s.size = NULL;
    s.top = -1;
    s.data = nullptr;
    return *this;
}
#endif //MR2022_stack_H
