#include <iostream>
#include <string>

using namespace std;
#define SIZE 10
 

template <class T> class Stack {
public:
    Stack();
    void push(T k);  //  Добавление элемента любого типа
    T pop();  // Удаление элемента
    T topElement();  //  Запись верхнего элемента в стек
    bool isFull();  //  Проверка заполненности стека
    bool isEmpty();  //  Прверка пустоты стека 
 
private:
    int top;  //  Взятие верхнего элемента
    T st[SIZE];  //  Инициализация стека заданного размера
};
 
template <class T> Stack<T>::Stack() { top = -1; }  //  Инициализация вершины стека
 
template <class T> void Stack<T>::push(T k)  // Добавление элемента k в стек 
{

    if (isFull()) {  
        cout << "Stack is full\n";
    }
 
    cout << "Inserted element " << k << endl;  //  Вставленный элемент 
 
    top = top + 1;  //  Увеличение вершины на единицу
 
    st[top] = k;  //  Добавление элемента в стек
}
 
template <class T> bool Stack<T>::isEmpty()  //  Проверка пустоты стека
{
    if (top == -1)
        return 1;
    else
        return 0;
}

template <class T> bool Stack<T>::isFull()  //  Проверка заполненности стека
{

    if (top == (SIZE - 1))
        return 1;
    else
 
        return 0;  //  Ограничение размера
}
 
template <class T> T Stack<T>::pop()
{
  
    T popped_element = st[top];  // Инициализация переменной для всплывающей переменной
 
    top--;  //  Уменьшение вершины
 
    return popped_element;  //  Возвращение всплывающей переменной
}
 
template <class T> T Stack<T>::topElement()
{
    
    T top_element = st[top];  //  Инициализация переменной для хранения верхнего элемента
 
    return top_element;  //  Возврат верхнего элемента
}
 
int main()
{
 
    Stack<int> integer_stack;
    Stack<string> string_stack;
 
    integer_stack.push(2);
    integer_stack.push(54);
 
    string_stack.push("Welcome");
    string_stack.push("to");
   
    cout << integer_stack.pop() << " is removed from stack"  //  Удаление элемента из стека целых чисел
         << endl;
 
    cout << string_stack.pop() << " is removed from stack "  //  Удаление элемента из стека строк 
         << endl;
 
    cout << "Top element is " << integer_stack.topElement()  //  Отображение верхнего элемента 
         << endl;
 
    cout << "Top element is " << string_stack.topElement()   //  Отображение верхнего элемента 
         << endl;
         << endl;
 
    return 0;
}