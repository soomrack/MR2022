
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
    stack(const stack&);
    explicit stack(stack&&) noexcept;
    explicit stack(size_t);
    ~stack();
    
    bool is_empty();
    bool is_full();

    unsigned int get_size();
    void push(T);
    T pop();
    T peek();
    
    T& operator[](unsigned int idx) {return data[idx];};
};

template <typename T>
stack<T>::stack(size_t capacity) {
    capacity = capacity;
    data = new T[capacity];
    if (!data) throw BADALLOC;
    size = 0;
    top = -1;   // инициализация вершины пустым значением
}
template <typename T>
bool stack<T>::is_empty() {
    return top == -1;
}

template <typename T>
stack<T>::~stack() {
    while (size)
    {
        pop();
    }
    data = nullptr;
}


template<typename T>
unsigned int stack<T>::get_size() {
    return size;}

template <typename T>
bool stack<T>::is_full(){
    return top == capacity - 1;
}

template <typename T>
void stack<T>::push(T value) {
    if (is_full()) throw FULL;
    top++;
    size++;
    data[top] = value;
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
stack<T>::stack(const stack<T> & stack) : capacity(stack.capacity), size(stack.size), top(stack.top) {
    data = new T[capacity];
    if (!data) throw BADALLOC;
    memcpy(data, stack.data, capacity);
}


template <typename T>
stack<T>::stack(stack<T> && stack) noexcept : capacity(stack.capacity), size(stack.size),
                                          top(stack.top), data(stack.data) {
    stack.capacity = NULL;
    stack.size = NULL;
    stack.top = -1;
    stack.data = nullptr;
}

#endif //MR2022_stack_H
