 #include <iostream>
#include "dynamic_array.h"
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
        A.search(4.08) ? std::cout << "YES" : std::cout << "NO";
        std::cout << std::endl;
        A.resize(12);
        std::cout << "Unalloceted capacity: " << A.get_free_capacity() << std::endl;
        print(A);
        A.insert(3, 9);
        A.insert(8, 2);
        std::cout << "Unalloceted capacity: " << A.get_free_capacity() << std::endl;
        A.insert(9, 2);
        print(A);
        std::cout << "Unalloceted capacity: " << A.get_free_capacity() << std::endl;
        A.resize(10);
        print(A);
        std::cout << "Unalloceted capacity: " << A.get_free_capacity() << std::endl;
    }
    catch (ARRAY_EXCEPTION &e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}