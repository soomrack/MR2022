#include <iostream>


#define MAX_SIZE 1000


class Stack {
private:
    int top;        // индекс верхнего элемента стека
    int arr[MAX_SIZE];   // массив для хранения элементов стека
public:
    Stack();
    bool isEmpty();
    bool isFull();

    void push(int x);

    void pop();

    int peek();

    void print();
};

class Stack_Exception: public std::domain_error {
public:
    Stack_Exception(const char* msg) : std::domain_error(msg) {};
};

//Создание объектов
Stack_Exception OVERFLOWED("Overflow");
Stack_Exception UNDERFLOWED("Underflow");

Stack::Stack() {
    top = -1;   // инициализация вершины пустым значением
}

bool Stack::isEmpty() {
    return top == -1;
}

bool Stack::isFull(){
    return top == MAX_SIZE - 1;
}

void Stack::push(int x) {
    if (isFull()) throw OVERFLOWED;
    top++;
    arr[top] = x;
}

void Stack::pop() {
    if (isEmpty()) throw UNDERFLOWED;
    top--;
}

int Stack::peek() {
    if (isEmpty()) throw UNDERFLOWED;
    return arr[top];
}

void Stack::print() {
    if (isEmpty()) throw UNDERFLOWED;
    std::cout << "Stack: ";
    for (int i = top; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }
    std::cout << std:: endl;
}
int main() {
    Stack s;
    try {
        s.push(5);
        s.push(3);
        s.push(7);
    }
    catch (Stack_Exception &e) {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    s.print();  // Стек: 7 3 5
    try {
        s.pop();
        s.print();  // Стек: 3 5
        std::cout << "Top of the Stack: " << s.peek() << std::endl; // Верхний элемент стека: 3
    }
    catch (Stack_Exception& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }



    return 0;
}
