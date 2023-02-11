#include "List.h"


int main() {
    List<int> A;
    A.append(4);
    A.append(5);
    A.append(6);
    A.append(7);
    A.append(8);
    A.print();


    A.pop(2);
    A.print();


    return 0;
}