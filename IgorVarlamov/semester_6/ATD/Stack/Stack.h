
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
    size_t capacitance;                                             // вместимость стека
    size_t size;                                                    // текущий размер стэка
    int top;                                                        // индекс верхнего элемента стека
    T* data;                                                        // массив для хранения элементов стека
public:
    stack();                                                        // пустой конструктор
    stack(const stack&);                                            // конструктор копирования
    explicit stack(stack&&) noexcept;                               // конструктор переноса
    explicit stack(size_t);                                         // конструктор с заданной емкостью стека
    ~stack();                                                       // деструктор
    
    bool is_empty();                                                // проверяет, пуст ли стек
    bool is_full();                                                 // проверяет, заполнен ли стек

    unsigned int get_size();                                        // возвращает текущий размер стека
    void push(T);                                                   // добавляет элемент в стек
    T pop();                                                        // удаляет элемент из стека и возвращает его значение
    T peek();                                                       // возвращает значение верхнего элемента стека, не удаляя его
    
    T& operator[](unsigned int idx) {return data[idx];};
};

template <typename T>
stack<T>::stack() {
    capacitance = 0;
    size = 0;
    top = -1;
    data = nullptr;
}

template <typename T>
stack<T>::stack(size_t capacitance) {
    capacitance = capacitance;
    data = new T[capacitance];
    if (!data) throw BADALLOC;
    size = 0;
    top = -1;                                                       // инициализация вершины пустым значением
}

template <typename T>
stack<T>::stack(const stack<T> & stack) : capacitance(stack.capacitance), size(stack.size), top(stack.top) {
    data = new T[capacitance];
    if (!data) throw BADALLOC;
    memcpy(data, stack.data, capacitance);
}


template <typename T>
stack<T>::stack(stack<T> && stack) noexcept : capacitance(stack.capacitance), size(stack.size),
                                          top(stack.top), data(stack.data) {
    stack.capacitance = NULL;
    stack.size = NULL;
    stack.top = -1;
    stack.data = nullptr;
}


template <typename T>
stack<T>::~stack() {
    delete data;
    data = nullptr;
}

template <typename T> 
bool stack<T>::is_empty() {
    return top == -1;
}

template<typename T>
unsigned int stack<T>::get_size() {
    return size;}

template <typename T>
bool stack<T>::is_full(){
    return top == capacitance - 1;
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
#endif //MR2022_stack_H
