#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include "DynamicArray.h"

template<typename T>
class MaxHeap {
private:
    DynamicArray<T> heap;
    unsigned int size;

    void heapify_up(unsigned int index);
    void heapify_down(unsigned int index);

public:
    MaxHeap() : size(0) {};
    MaxHeap(DynamicArray<T> array);
    ~MaxHeap() = default;

    void insert(T value);
    int get_max();
    int extract_max();
    bool is_empty() { return size == 0; }
    unsigned int get_size() { return size; }
    void print();
};

template<typename T>
MaxHeap<T>::MaxHeap(DynamicArray<T> array) {
    heap = array;
    size = array.getSize();
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify_down(i);
    }
}

template<typename T>
void MaxHeap<T>::heapify_up(unsigned int index) {
    DynamicArray<unsigned int> dop_index;
    bool is_array_empty;
    do {
        while (index > 0) {
            unsigned int parent_index = (index - 1) / 2;
            if (heap[index] > heap[parent_index]) {
                dop_index.push_tail(index);
                std::swap(heap[index], heap[parent_index]);
                index = parent_index;
            } else {
                break;
            }
        }

        is_array_empty = dop_index.getSize() == 0;

        if (!is_array_empty) {
            index = dop_index[dop_index.getSize() - 1];
            dop_index.pop_tail();
        }
    } while (!is_array_empty);
}

template<typename T>
void MaxHeap<T>::heapify_down(unsigned int index) {
    unsigned int left_child_index;
    unsigned int right_child_index;
    unsigned int largest_index;

    while (true) {
        left_child_index = 2 * index + 1;
        right_child_index = 2 * index + 2;
        largest_index = index;

        if (left_child_index < get_size() && heap[left_child_index] > heap[largest_index]) {
            largest_index = left_child_index;
        }

        if (right_child_index < get_size() && heap[right_child_index] > heap[largest_index]) {
            largest_index = right_child_index;
        }

        if (largest_index != index) {
            std::swap(heap[index], heap[largest_index]);
            index = largest_index;
        } else {
            break;
        }
    }
}


template<typename T>
void MaxHeap<T>::insert(T value) {
    size++;
    heap.push_tail(value);
    heapify_up(get_size() - 1);
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
    heap[0] = heap[get_size() - 1];
    heap.pop_tail();
    size--;
    heapify_down(0);
    return max_value;
}

template<typename T>
void MaxHeap<T>::print() {
    std::cout << "\nheap: ";
    for (int i = 0; i < get_size(); ++i) {
        std::cout << heap[i] << ' ';
    }
    std::cout << '\n';
}

#endif
