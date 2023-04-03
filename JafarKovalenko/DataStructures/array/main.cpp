#include <cstddef>
#include <iostream>
#include "array.h"


template<class T>
void printDynamicArray(DynamicArray<T>& array)
{
    using namespace std;
    cout << "DynamicArray size = " << array.size() <<
            "\nDynamicArray capacity = " << array.capacity() << endl;
    for (int i = 0; i < array.size(); ++i)
        cout << array[i] << " ";
    cout << "\n" << endl;
}

template<class T>
void fillRandomDynamicArray(DynamicArray<T>& array)
{
    using namespace std;
    srand(time(nullptr));
    for (int i = 0; i < array.size(); ++i)
        array[i] = rand() % 100 * (rand() % 10 - 4);
}

int main()
{
    DynamicArray<> one(5);
    printDynamicArray(one);
    fillRandomDynamicArray(one);
    printDynamicArray(one);
    std::cout << "--------------------" << std::endl;

    DynamicArray<> two(one);
    printDynamicArray(two);
    two.sort();
    printDynamicArray(two);
    std::cout << "--------------------" << std::endl;

    DynamicArray<> three(2);
    three = two;
    printDynamicArray(three);
    three.resize(20);
    printDynamicArray(three);

    DynamicArray<> four; 
    four = one + three;
    printDynamicArray(four);
    return 0;
}

