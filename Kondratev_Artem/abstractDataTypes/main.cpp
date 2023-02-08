#include "array.h"
#include <vector>


int main() {
    array<int> A(3);
    std::cout << A.len();
    A[0] = 5;

}