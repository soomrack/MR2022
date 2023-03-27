#include "PriorityQueue.h"


int main() {
    PriorityQueue<int> A;
    A.push(0, 0);
    A.push(1, 1);
    A.push(2, 5);
    A.push(3, 2);
    A.push(4, 0);
    A.push(5, 5);
    A.print();

    A.pop();
    A.print();

    return 0;
}
