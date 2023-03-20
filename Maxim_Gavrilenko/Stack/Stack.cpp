#include <iostream>
#include "Stack.h"


int main() {
    stack<double> s;
        s.push(5);
        s.push(3);
        s.push(7);
    s.print();  // Стек: 7 3 5
        std::cout<<s.pop()<<std::endl;
        s.print();  // Стек: 3 5
        std::cout << "Top of the Stack: " << s.peek() << std::endl; // Верхний элемент стека: 3

    return 0;
}
