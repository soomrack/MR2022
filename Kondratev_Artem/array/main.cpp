#include "Array.h"


void test() {
}


int main() {
    Array<int> A(3);
    A.setData(0, 5);
    A.setData(1, 8);
    A.setData(2, 3);
    A.print();
    A.quickSort();
    std::cout << "\n\n";
    A.print();
}