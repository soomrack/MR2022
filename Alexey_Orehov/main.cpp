#include <iostream>
#include "dynamic_array.h"
#include "stack.h"

int main() {
//    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    dynamic_array<int> A = {A_data, 10};
//
//    A.resize(15);
//    A[10] = 1;
//    std::cout << A[10] << std::endl;
//    A.resize(5);
//    std::cout << A[6] << std::endl;

    Stack<int> A(10);
    for (int i = 0; i < 10; i++) {
        A.push(i);
    }

    return 0;
}
