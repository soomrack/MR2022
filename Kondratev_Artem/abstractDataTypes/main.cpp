#include "array.h"
#include <vector>


int main() {
    array<int> A(3);
    std::cout << A.len();
    A.data[0] = 5;
    std::cout << A;
}