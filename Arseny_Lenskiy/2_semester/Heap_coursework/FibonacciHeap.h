#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>

#include "Node.h"
#include "DynamicArray.h"

template<typename T>
class FibonacciHeap {
private:
    DynamicArray<Node<T> *> roots;
    unsigned int size;
    Node<T> *minimum;

    Node<T> *merge_trees(Node<T> *a, Node<T> *b);
    void delete_tree(Node<T> *node);
    void consolidate();

public:
    FibonacciHeap() : roots(), size(0), minimum(nullptr) {};
    ~FibonacciHeap();

    void merge(FibonacciHeap<T> &heap);
    void insert(T data);
    T get_min() { return minimum->data; }
    T extract_min();
    void print_roots();
    unsigned int get_size() { return size; }
    void roots_sort();
};

template<typename T>
Node<T> *FibonacciHeap<T>::merge_trees(Node<T> *a, Node<T> *b) {
    if (a == nullptr && b == nullptr) throw std::invalid_argument("All nodes are nullptr!");
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (a->data > b->data) {
        std::swap(a, b);
    }
    int c_size = a->children.get_size();

    if (c_size == 0) {
        a->children.push_head(b);
    } else {
        a->children.push_next(b, c_size - 1);
    }

    return a;
}

template<typename T>
void FibonacciHeap<T>::delete_tree(Node<T> *node) {
    ListNode<Node<T> *> *child = (node->children).get_head();
    for (int i = 0; i < (node->children).get_size(); ++i) {
        delete_tree(child->data);
        child = child->get_next();
    }
    delete node;
}

template<typename T>
FibonacciHeap<T>::~FibonacciHeap() {
    for (int i = 0; i < roots.getSize(); ++i) {
        if (roots[i] != nullptr) {
            delete_tree(roots[i]);
        }
    }
}

template<typename T>
void FibonacciHeap<T>::merge(FibonacciHeap<T> &heap) {
    for (int i = 0; i < heap.roots.getSize(); ++i) {
        roots.push_tail(heap.roots[i]);
    }

    if (minimum->data > heap.minimum->data) minimum = heap.minimum;
    size += heap.size;

    heap.size = 0;
    heap.roots = DynamicArray<Node<T> *>();
    heap.minimum = nullptr;
}

template<typename T>
void FibonacciHeap<T>::insert(T data) {
    auto *temp = new Node<T>(data);

    if (roots.getSize() == 0) minimum = temp;

    roots.push_tail(temp);

    if (minimum->data > data) minimum = temp;
    size++;
}

template<typename T>
T FibonacciHeap<T>::extract_min() {
    if (minimum == nullptr) throw std::runtime_error("Heap is empty!");

    T min_value = minimum->data;

    if ((minimum->children).get_size() != 0) {
        LinkedList<Node<T> *> children_nodes = minimum->children;

        do {
            Node<T> *child_node = children_nodes.pop_head()->data;
            roots.push_tail(child_node);
        } while (!children_nodes.is_empty());
    }

    std::swap(minimum->data, (roots[roots.getSize() - 1])->data);
    std::swap(minimum->children, (roots[roots.getSize() - 1])->children);
    roots.pop_tail();
    size--;

    roots_sort();

    if (size != 0) {
        consolidate();

        minimum = roots[0];
        for (int i = 0; i < roots.getSize(); ++i) {
            if (roots[i]->data < minimum->data) {
                minimum = roots[i];
            }
        }
    } else {
        minimum = nullptr;
    }

    return min_value;
}

template<typename T>
void FibonacciHeap<T>::consolidate() {
    DynamicArray<Node<T> *> res_arr;
    Node<T> *temp;

    for (int i = roots.getSize() - 1; i > 0; i--) {
        if (roots[i - 1]->children.get_size() == roots[i]->children.get_size()) {
            temp = merge_trees(roots[i - 1], roots[i]);
            roots[i - 1] = temp;
            roots.pop_tail();
            roots_sort();
        } else {
            res_arr.push_tail(roots[i]);
            roots.pop_tail();
        }
    }
    res_arr.push_tail(roots[0]);
    roots = res_arr;
}

template<typename T>
void FibonacciHeap<T>::print_roots() {
    roots_sort();
    int c_size;
    for (unsigned int i = 0; i < roots.getSize(); ++i) {
        c_size = roots[i]->children.get_size();
        std::cout << "\nroots with rank = " << c_size << ": ";
        std::cout << roots[i]->data;
        while (i + 1 < roots.getSize() && c_size == roots[i + 1]->children.get_size()) {
            i++;
            std::cout << ", " << roots[i]->data;
        }
    }
    std::cout << '\n';
}

template<typename T>
void FibonacciHeap<T>::roots_sort() {
    Node<T> *temp;
    for (int i = 0; i < roots.getSize(); ++i) {
        bool flag = true;
        for (int j = 0; j < roots.getSize() - (i + 1); j++) {
            if (roots[j]->children.get_size() < roots[j + 1]->children.get_size()) {
                flag = false;
                temp = roots[j];
                roots[j] = roots[j + 1];
                roots[j + 1] = temp;
            }
        }
        if (flag) {
            break;
        }
    }
}


#endif
