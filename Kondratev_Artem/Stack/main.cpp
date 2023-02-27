#include "Stack.h"


int main() {
    Stack<int> A;
    A.append(5);
    int b = A.pop();
    std::cout << b;


    return 0;
}