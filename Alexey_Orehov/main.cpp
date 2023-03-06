#include <iostream>
#include "dynamic_array.h"
#include "stack.h"
#include "list.h"


void test_dynamic_array() {
    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    dynamic_array<int> A = {A_data, 10};

    A.resize(15);
    A[10] = 1;
    std::cout << A[10] << std::endl;
    A.resize(5);
    std::cout << A[6] << std::endl;
}


void test_stack() {
    Stack<int> A(10);
    for (int i = 0; i < 10; i++) {
        std::cout << "Inserted " << i << " to stack\n";
        A.push(i);
    }
    for (int i = 0; i < 10; i++) {
        std::cout << A.pop() << std::endl;
    }
}


void test_list() {
    List<int> A;
    A.push_back(3);
    A.push_front(10);
    A.push_front(5);

    A.head() = 100;
    A.tail() = 200;

}


int main() {
    test_list();

    return 0;
}
