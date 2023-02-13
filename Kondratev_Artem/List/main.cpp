#include "List.h"


int main() {
    List<uint64_t> A;
    A.append(4, 0);
    A.append(5);
    A.append(6, 2);
    A.append(7);
    A.append(8, 4);
    A.print();

    uint64_t c[] = {5, 10, 8, 3};
    List<uint64_t> B(4, c);
    B.print();
    List<uint64_t> C = A + B;
    C.print();

    return 0;
}