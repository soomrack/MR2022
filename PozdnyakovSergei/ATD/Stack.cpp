#include <iostream>
#include <cstdlib>

class Stack{
    int *array;
    int stp;
    int capacity;

public:
    Stack (int size);  // Конструктор
    ~Stack();  // Деструктор
    void push(int);
    int pop();
    int upper();
    int size();

    bool is_empty();
    bool is_full();
};


class Stack_exceptions: public std::domain_error {
public:
    Stack_exceptions(const char* const error) : std::domain_error(error) {
    }
};


Stack_exceptions IS_EMPTY ("Error: Stack is empty, you can't pop anything");
Stack_exceptions IS_FULL ("Error: Stack is full, you can't push anything");


Stack::Stack(int size) {
    array = new int[size];
    capacity = size;
    stp = -1;
}

Stack::~Stack() {
    delete[] array;
}

void Stack::push(int item) {  // Проверка на заполненность и если не полный то пушится элемент
    if (is_full()) {
        throw IS_FULL;
    }
    std::cout << "Push: " << item << std::endl;
    stp = stp + 1;
    array[stp] = item;
}

int Stack::pop() {  // Проверка на пустоту, если не пустой то вынимается элемент, уменьшается на 1 верхний элемент
    if (is_empty()) {
        std::cout << "Stack is empty " <<  std::endl;
    }
    std::cout << "Pop " << upper() << std::endl;
    stp = stp - 1;
    return array[stp];
}

int Stack::upper() {  // Для возврата верхнего элемента
    if (!is_empty()) {
        return array[stp];
    }
    else {
        throw IS_EMPTY;
    }
}

int Stack::size() { // Для определения размера стека
    return stp + 1;
}

bool Stack::is_full() {  // Для проверки заполненности стека
    return size() == capacity;
}

bool Stack::is_empty() {  // Для проверки пустоты стека
    return size() == 0;
}

int main () {
    Stack st(5);
    st.push(1); st.push(44); st.push(7);
    st.pop(); st.pop();
    st.push(25);

    if (st.is_empty()) {
        throw IS_EMPTY;
    }
    if (st.is_full()) {
        throw IS_FULL;
    }
}