#define MAX_SIZE 1000

#ifndef MR2022_stack_H
#define MR2022_stack_H
template <typename T>
class stack {
private:
    int top;        // индекс верхнего элемента стека
    T arr[MAX_SIZE];   // массив для хранения элементов стека
public:
    stack();
    bool isEmpty();
    bool isFull();

    void push(int x);
    void print();
    T pop();
    T peek();
};

template <typename T>
stack<T>::stack() {
    top = -1;   // инициализация вершины пустым значением
}
template <typename T>
bool stack<T>::isEmpty() {
    return top == -1;
}

template <typename T>
bool stack<T>::isFull(){
    return top == MAX_SIZE - 1;
}

template <typename T>
void stack<T>::push(int x) {
    if (isFull()) throw std::out_of_range("Is full");
    top++;
    arr[top] = x;
}

template <typename T>
T stack<T>::pop() {
    if (isEmpty()) throw std::out_of_range("Is empty");
    return arr[top];
    top--;
}

template <typename T>
T stack<T>::peek() {
    if (isEmpty()) throw std::out_of_range("Is empty");
    return arr[top];
}

template <typename T>
void stack<T>::print() {
    if (isEmpty()) throw std::out_of_range("Is empty");
    std::cout << "stack: ";
    for (int i = top; i >= 0; i--) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

#endif //MR2022_stack_H
