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

    bool empty();
    bool full();
};

Stack::Stack(int size) {
    array = new int[size];
    capacity = size;
    stp = -1;
}

Stack::~Stack() {
    delete[] array;
}

void Stack::push(int item) {  // Проверка на заполненность и если не полный то пушится элемент
    if (full()) {
        std::cout << "Stack owerflow";
    }
    std::cout << "Push: " << item << std::endl;
    stp = stp + 1;
    array[stp] = item;
}

int Stack::pop() {  // Проверка на пустоту, если не пустой то вынимается элемент, уменьшается на 1 верхний элемент
    if (empty()) {
        std::cout << "Stack is empty " <<  std::endl;
    }
    std::cout << "Pop " << upper() << std::endl;
    stp = stp - 1;
    return array[stp];
}

int Stack::upper() {  // Для возврата верхнего элемента
    if (!empty()) {
        return array[stp];
    }
    else {
        exit;
    }
}

int Stack::size() { // Для определения размера стека
    return stp + 1;
}

bool Stack::full() {  // Для проверки заполненности стека
    return size() == capacity;
}

bool Stack::empty() {  // Для проверки пустоты стека
    return size() == 0;
}

int main () {
    Stack st(5);

    st.push(1); st.push(44); st.push(7);
    std::cout << "Upper element: " << st.upper() << std::endl;
    std::cout << "Stack size: " << st.size() <<  std::endl;

    st.pop(); st.pop();
    std::cout << "Upper element: " << st.upper() << std::endl;
    std::cout << "Stack size: " << st.size() <<  std::endl;

    st.push(25);
    std::cout << "Upper element: " << st.upper() << std::endl;
    std::cout << "Stack size: " << st.size() <<  std::endl;

    if (st.empty()) {
        std::cout << "Stack is empty" <<  std::endl;
    }
    else {
        std::cout << "Stack isn't empty" <<  std::endl;
    }

    if (st.full()) {
        std::cout << "Stack is full" <<  std::endl;
    }
    else {
        std::cout << "Stack isn't full" <<  std::endl;
    }
}