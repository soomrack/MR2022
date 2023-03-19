#include <iostream>
#include "dynamic_array.h"
template <typename T>
void print (dynamic_array<T>& A) {
    for (unsigned int number = 0; number < A.lenght(); number++){
        std::cout << A[number] << "  ";
    }
    std::cout << "\n";
}
int main() {
    dynamic_array<double> A(10);
    print(A);
    A.insert(98.06, 0);
    A.insert(7.04, 1);
    A.insert(4.08, 2);
    A.insert(3,1);
    print(A);
    std::cout << A.lenght() << std::endl;
    A.replace(1.90, 3);
    print(A);
    A.search(4.08) ? std::cout << "YES" : std::cout << "NO";
    std:: cout << std::endl;
    A.resize(4);
    print(A);
    A.resize(10);
    print(A);
    return 0;
}