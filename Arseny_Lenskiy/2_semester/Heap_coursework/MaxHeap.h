#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <vector>

template<typename T>
class MaxHeap {
private:
    std::vector<T> heap;

    void heapify_up(unsigned int index);

    void heapify_down(unsigned int index);

public:
    MaxHeap() = default;

    ~MaxHeap() = default;

    void insert(T value);

    int get_max();

    int extract_max();

    bool is_empty() { return heap.empty(); }

    unsigned int size() { return heap.size(); }

    void print();
};

template<typename T>
void MaxHeap<T>::heapify_up(unsigned int index) {
    if (index == 0) {
        return;
    }

    unsigned int parent_index = (index - 1) / 2;
    if (heap[index] > heap[parent_index]) {
        std::swap(heap[index], heap[parent_index]);
        heapify_up(parent_index);
    }
}

template<typename T>
void MaxHeap<T>::heapify_down(unsigned int index) {
    unsigned int left_child_index = 2 * index + 1;
    unsigned int right_child_index = 2 * index + 2;
    unsigned int largest_index = index;

    if (left_child_index < size() && heap[left_child_index] > heap[largest_index]) {
        largest_index = left_child_index;
    }

    if (right_child_index < size() && heap[right_child_index] > heap[largest_index]) {
        largest_index = right_child_index;
    }

    if (largest_index != index) {
        std::swap(heap[index], heap[largest_index]);
        heapify_down(largest_index);
    }
}

template<typename T>
void MaxHeap<T>::insert(T value) {
    heap.push_back(value);
    heapify_up(size() - 1);
}

template<typename T>
int MaxHeap<T>::get_max() {
    if (is_empty()) throw std::runtime_error("Heap is empty!");

    return heap[0];
}

template<typename T>
int MaxHeap<T>::extract_max() {
    if (is_empty()) throw std::runtime_error("Heap is empty!");

    int max_value = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);
    return max_value;
}

template<typename T>
void MaxHeap<T>::print() {
    std::cout << "heap: ";
    for (int i = 0; i < size(); ++i) {
        std::cout << heap[i] << ' ';
    }
    std::cout << '\n';
}

#endif
