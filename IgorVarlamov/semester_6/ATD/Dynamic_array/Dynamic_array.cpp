#include <iostream>
#include "Dynamic_array.h"
#include <ctime>
template <typename T>
void print (dynamic_array<T>& A) {
    for (unsigned int number = 0; number < A.get_size(); number++){
        std::cout << A[number] << "  ";
    }
    std::cout << "\n";
}
int main() {
    try {
        dynamic_array<double> A(10);;
        for (unsigned i = 0; i < A.get_capacity(); i++)
            A.insert(rand() % 10, i);
        print(A);
        std::cout << A.get_size() << std::endl;
        print(A);
        std::cout << std::endl;
        A.resize(12);
        A.insert(3, 9);
        A.insert(8, 2);
        A.insert(9, 2);
        print(A);
        A.resize(10);
        print(A);
    }
    catch (ARRAY_EXCEPTION &e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}