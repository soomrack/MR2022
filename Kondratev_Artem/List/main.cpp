#include "List.h"


int main() {
    List<int> A;
    A.append(4, 0);
    A.append(5);
    A.append(6, 2);
    A.append(7);
    A.append(8, 4);
    A.print();

    int c[] = {5, 10, 8, 3};
    List<int> B(4, c);
    B.print();

    return 0;
}