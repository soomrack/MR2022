#include "MaxHeap.h"

void testMaxHeap() {
    MaxHeap<int> heap;

    heap.insert(3);
    heap.insert(10);
    heap.insert(6);
    heap.insert(7);
    heap.insert(8);
    heap.insert(5);
    heap.insert(9);
    heap.insert(4);

    std::cout << "max element: " << heap.get_max() << '\n';

    heap.print();

    std::cout << "\nextracted max element: " << heap.extract_max();

    std::cout << "\n\nmax element: " << heap.get_max() << '\n';

    heap.print();

    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
    std::cout << "\nextracted max element: " << heap.extract_max();
}

int main() {
    system("chcp 65001");
    testMaxHeap();
    return 0;
}

