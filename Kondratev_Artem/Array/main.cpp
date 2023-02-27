#include "Array.h"
#include <vector>

int main() {
    Array<int> A(5, 3);
    A.print();
    A.append(4);
    A.print();
}
