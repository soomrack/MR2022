#include "Array.h"
#include <vector>


void test() {
}


int main() {
    Array<int> A(4);
    A.print();
    A.setData(3, 3);
    A.print();
    A.append(5);
    A.print();
    A.append(8);
    A.print();
}