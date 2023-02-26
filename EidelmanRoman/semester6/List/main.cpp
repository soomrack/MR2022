#include <iostream>
#include "List.h"


int main() {
    List lst;
    lst.push_back(5);
    lst.push_back(6);
    lst.push_back(8);

    std::cout << lst.getSize() << "\n";
    std::cout << lst[2] << "\n";
}