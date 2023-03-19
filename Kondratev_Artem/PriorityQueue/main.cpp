#include "PriorityQueue.h"


int main() {
    PriorityQueue<int> A;
    A.append(0, 3);
    A.append(1, 3);
    A.append(2, 4);
    A.append(3, 5);
    A.append(4, 4);
    A.append(5, 3);
    std::cout << A.pop() << std::endl;
    A.print();

    return 0;
}
