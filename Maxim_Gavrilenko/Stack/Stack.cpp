#include <iostream>
#include "Stack.h"

template <typename T>
void print(stack<T> &A)
{
    if (A.is_empty())
        throw EMPTY;
    std::cout << "stack: ";
    for (int i = A.get_size() - 1; i >= 0; i--)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    stack<double> s(10);
    s.push(5);
    s.push(3);
    s.push(7);
    std::cout << s.get_size();
    print(s); // Стек: 7 3 5
    std::cout << "POP METHOD: " << s.pop() << std::endl;
    print(s);                                                   // Стек: 3 5
    std::cout << "Top of the Stack: " << s.peek() << std::endl; // Верхний элемент стека: 3

    return 0;
}
