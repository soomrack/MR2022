
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
    unsigned int max_size;
    unsigned int size;
    int top;        // индекс верхнего элемента стека
    T* data;   // массив для хранения элементов стека
public:
    stack(unsigned int max);
    bool is_empty();
    bool is_full();
    unsigned int get_size();
    void push(int x);
    T pop();
    T peek();
    T& operator[](unsigned int idx) {return data[idx];};
};

template <typename T>
stack<T>::stack(unsigned int max) {
    max_size = max;
    data = new T[max_size];
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
    return top == max_size - 1;
}

template <typename T>
void stack<T>::push(int x) {
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

#endif //MR2022_stack_H
