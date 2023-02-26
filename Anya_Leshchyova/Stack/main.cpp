#include <iostream>
#include <cstdlib>
using namespace std;


#define SIZE 10


class Stack {
    int *arr;
    int sp;  //stack point
    int capacity; // размер стека

public:
    Stack();  // конструктор по умолчанию
    Stack(int size = SIZE);         // конструктор
    ~Stack();                       // деструктор

    void push(int); // вставить элемент
    int pop();  // извлечь элемент
    int peek();  // извлечь самый верхни элемент

    int size();  // размер стека
    inline bool isEmpty();  // заполнен ли стек?
    inline bool isFull(); //  пуст ли стек?
    void print(); // вывести стек
    void search(int); //  найти элемент

    unsigned int getsize();

};

class Stack_Exception {
public:
    int kod_mistake;

    Stack_Exception();
    Stack_Exception(int kod_mistake);
    void set_mistake (int kod_mistake);
};


//Объявление исключений
Stack_Exception Overflow=(1);
Stack_Exception Underflow=(2);

Stack_Exception:: Stack_Exception(){
    kod_mistake = 999;
}


Stack_Exception:: Stack_Exception(int kod){
    kod_mistake = kod;
}


void Stack_Exception::set_mistake (int error){
    switch (error) {
        case 1:
            std::cout << "\n"<< "       Overflow --> Program Terminated \n"<< "\n";
            break;
        case 2:
            std::cout<< "\n" << "       Underflow --> Program Terminated\n"<< "\n";
            break;
        default:
            std::cout << "       Unknown error \n";
    }
}


// Конструкторы
Stack::Stack(){
    capacity = 0;
    arr = NULL;
    sp = 0;
}


Stack::Stack(int size) {
    arr = new int[size];
    capacity = size;
    sp = -1;
}


// Деструктор
Stack::~Stack() {
    delete[] arr;
}

unsigned int Stack::getsize() {
    return (capacity);
}
// Добавления элемента в stack
void Stack::push(int x) {
    if (isFull()) { // Проверка на переполнения стека
        try{ throw Overflow;}
        catch (Stack_Exception error){ error.set_mistake(1);}
        exit(EXIT_FAILURE);
    }
    cout << "Inserting " << x << endl;
    arr[++sp] = x;
}


// Извлечения верхнего элемента из stack
int Stack::pop() {
    if (isEmpty()) {
        try{ throw Underflow;}
        catch (Stack_Exception error){ error.set_mistake(2);}
        exit(EXIT_FAILURE);
    }
    cout << "Removing " << peek() << endl;
    return arr[sp--];
}

// Возврат верхнего элемента stack
int Stack::peek() {
    if (!isEmpty()) {
        return arr[sp];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

// Возврата размера stack
int Stack::size() {
    return sp + 1;
}

// Вспомогательная функция для проверки, пуст stack или нет
inline bool Stack::isEmpty() {
    return sp == -1;
}

// Вспомогательная функция для проверки, заполнен ли stack или нет
inline bool Stack::isFull() {
    return sp == capacity - 1;
}

void Stack::print() {
    cout << "Stack =  ";
    for (int number = 0; number <= sp; number++){
        cout << arr[number]<< " ";
    }
    cout <<  " \n";
}

void Stack::search(int x) {
    for (int number = 0; number <= sp; number++){
        if (x == arr[number]) {
            cout << x << " Is located " << number + 1 << "\n";
            return;
        }
    }
    cout <<x<< " Not found \n";
}



int main()
{
    Stack pt(7);
    for ( int i = 0; i < pt.getsize(); i++) {
        pt.push(i);
    }


    pt.print();
    pt.search(3);
    pt.search(39);

    pt.pop();
    pt.pop();
    pt.pop();
    pt.pop();

    cout << "The sp element is " << pt.peek() << endl;
    cout << "The stack size is " << pt.size() << endl;
    return 0;
}