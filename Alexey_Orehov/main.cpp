#include <iostream>
#include "dynamic_array.h"
#include "stack.h"
#include "list.h"
#include "tree.h"

void test_dynamic_array() {
    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DynamicArray<int> A = {A_data, 10};

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
    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    List<int> A(A_data, 10);
    A.push_back(3);
    A.push_front(10);
    A.push_front(5);

    A.head() = 100;
    A.tail() = 200;
}

void test_tree() {
    int data[15] = {50, 55, 6, 1, 51, 52, -10, 9, -8, 7, 10, 13, 15, -1, -2};
    Tree<int> tree;

    for (auto& element : data) {
        tree.insert(element);
    }

    tree.remove(50);
    tree.remove(51);
    tree.remove(6);
    tree.remove(52);
    tree.remove(13);

    for (auto& element : data) {
        if (tree.find(element)) std::cout << "Found element " << element << std::endl;
        else std::cout << "Element " << element << " not found" << std::endl;
    }
}



int main() {
    test_dynamic_array();

    return 0;
}
