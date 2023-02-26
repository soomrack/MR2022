#include "Queue.h"


int main() {
    Queue<int> A;
    A.append(5);
    A.append(6);
    int b = A.pop();
    std::cout << b << std::endl;
    b = A.pop();
    std::cout << b;


    return 0;
}