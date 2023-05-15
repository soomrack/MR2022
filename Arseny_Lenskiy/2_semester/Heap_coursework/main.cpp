#include "MaxHeap.h"
#include "BinomialHeap.h"
#include "FibonacciHeap.h"

void testMaxHeap() {
    std::cout << "\n\nMAX_HEAP_TEST\n\n\n";
    MaxHeap<int> heap;

    heap.insert(10);
    heap.insert(9);
    heap.insert(4);
    heap.insert(7);
    heap.insert(8);
    heap.insert(5);
    heap.insert(9);
    heap.insert(4);

    heap.print();
    while (!heap.is_empty()) {
        std::cout << "Максимальный элемент: " << heap.get_max() << '\n';
        std::cout << "\nДостали максимальный элемент: " << heap.extract_max();
        heap.print();
    }

    std::cout << '\n';
    DynamicArray<int> arr_int;

    int seed;
    std::cout << "\nВведи любое целое для генерации набора чисел: ";
    std::cin >> seed;

    srand(seed);

    for (int i = 0; i < 10; ++i) {
        arr_int.push_tail(rand() % 10 + 1);
    }

    std::cout << "\nСгенерированный набор чисел: ";
    arr_int.print(std::cout);

    MaxHeap<int> heap2(arr_int);

    heap2.print();
    while (!heap2.is_empty()) {
        std::cout << "Максимальный элемент: " << heap2.get_max() << '\n';
        std::cout << "\nДостали максимальный элемент: " << heap2.extract_max();
        heap2.print();
    }
}


void testBinomialHeap() {
    std::cout << "\n\n\nBINOMIAL_HEAP_TEST\n\n\n";
    BinomialHeap<int> heap;

    int seed, random;
    std::cout << "\nВведи любое целое для генерации набора чисел: ";
    std::cin >> seed;

    srand(seed);

    for (int i = 0; i < 10; ++i) {
        random = rand() % 10 + 1;
        heap.insert(random);
        std::cout << "\nВставлен элемент = " << random;
        heap.print_roots();
    }

    std::cout << "\n=============================================\n";
    heap.print_roots();

    while (heap.get_size() > 0) {
        std::cout << "\nМинимальный элемент: " << heap.get_min() << '\n';
        std::cout << "\nДостали минимальный элемент: " << heap.extract_min();
        heap.print_roots();
    }
}


void testFibonacciHeap() {
    std::cout << "\n\n\nFIBONACCI_HEAP_TEST\n\n\n";
    FibonacciHeap<int> heap, heap2;

    int seed, random;
    std::cout << "\nВведи любое целое для генерации набора чисел: ";
    std::cin >> seed;

    srand(seed);

    for (int i = 0; i < 10; ++i) {
        random = rand() % 10 + 1;
        heap.insert(random);
        std::cout << "\nВставлен элемент = " << random << " в heap";
        heap.print_roots();
    }


    for (int i = 0; i < 10; ++i) {
        random = rand() % 10 + 1;
        heap2.insert(random);
        std::cout << "\nВставлен элемент = " << random << " в heap2";
        heap2.print_roots();
    }

    std::cout << "\n=============================================\n";

    std::cout << "\nМинимальный элемент в heap: " << heap.get_min() << '\n';
    std::cout << "\nheap: ";
    heap.print_roots();
    std::cout << "\nМинимальный элемент в heap2: " << heap2.get_min() << '\n';
    std::cout << "\nheap2: ";
    heap2.print_roots();
    std::cout << "\nДостали минимальный элемент из heap: " << heap.extract_min();
    std::cout << "\nheap: ";
    heap.print_roots();
    std::cout << "\nСоединили heap и heap2: ";
    heap.merge(heap2);
    std::cout << "\nheap2: ";
    heap2.print_roots();
    std::cout << "\nheap: ";
    heap.print_roots();

    while (heap.get_size() > 0) {
        std::cout << "\nМинимальный элемент: " << heap.get_min() << '\n';
        std::cout << "\nДостали минимальный элемент: " << heap.extract_min();
        heap.print_roots();
    }
}


int main() {
    system("chcp 65001");

    int test;
    std::cout << "Введи тип кучи, тесты для которой хочешь посмотреть (0: max, 1: binomial, 2: fibonacci)\n";

    std::cin >> test;

    switch (test) {
        case 0:
            testMaxHeap();
            break;
        case 1:
            testBinomialHeap();
            break;
        case 2:
            testFibonacciHeap();
            break;
        default:
            std::cout << "В другой раз!\n";
    }

    return 0;
}
