#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include <iostream>
#include <cmath>

#include "DynamicArray.h"
#include "Node.h"

template<typename T>
class BinomialHeap {
private:
    DynamicArray<Node<T> *> roots;
    Node<T> *minimum;
    unsigned int size;

    Node<T> *merge_trees(Node<T> *a, Node<T> *b);
    void delete_tree(Node<T> *node);
    DynamicArray<Node<T> *> collapse(Node<T> *node);

public:
    BinomialHeap() : roots(), minimum(nullptr), size(0) {}
    ~BinomialHeap();

    void insert(T data);
    T get_min();
    T extract_min();
    void print_roots();
    unsigned int get_size() { return size; };
};

template<typename T>
Node<T> *BinomialHeap<T>::merge_trees(Node<T> *a, Node<T> *b) {
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
void BinomialHeap<T>::delete_tree(Node<T> *node) {
    ListNode<Node<T> *> *child = (node->children).get_head();
    for (int i = 0; i < (node->children).get_size(); ++i) {
        delete_tree(child->data);
        child = child->get_next();
    }
    delete node;
}

template<typename T>
BinomialHeap<T>::~BinomialHeap() {
    for (int i = 0; i < roots.getSize(); ++i) {
        if (roots[i] != nullptr) {
            delete_tree(roots[i]);
        }
    }
}

template<typename T>
void BinomialHeap<T>::insert(T data) {
    auto *new_root = new Node<T>(data);

    if (size == 0) {
        minimum = new_root;
        roots.push_tail(new_root);
        size++;
        return;
    }

    if (minimum->data >= data)
        minimum = new_root;

    size++;
    int temp = ((int) (10 * std::log2(size))) % 10;
    if (temp == 0) roots.push_tail(nullptr);

    for (int i = 0; i < roots.getSize(); ++i) {
        if (roots[i] == nullptr) {
            roots[i] = new_root;
            break;
        }
        new_root = merge_trees(new_root, roots[i]);
        roots[i] = nullptr;
    }
}

template<typename T>
T BinomialHeap<T>::get_min() {
    if (minimum == nullptr) throw std::runtime_error("Heap is empty!");

    return minimum->data;
}

template<typename T>
DynamicArray<Node<T> *> BinomialHeap<T>::collapse(Node<T> *node) {
    DynamicArray<Node<T> *> nodes;
    int c_size = (node->children).get_size();

    if (c_size == 0) {
        nodes.push_tail(nullptr);
        return nodes;
    }

    for (int i = 0; i < c_size; ++i) {
        nodes.push_tail((node->children).pop_head()->data);
    }
    return nodes;
}

template<typename T>
T BinomialHeap<T>::extract_min() {
    if (minimum == nullptr) throw std::runtime_error("Heap is empty!");

    T min_value = minimum->data;

    DynamicArray<Node<T> *> new_roots = collapse(minimum);

    if (new_roots[0] == nullptr) {
        roots[0] = nullptr;
    } else {
        roots[new_roots.getSize()] = nullptr;
        int temp_index;
        Node<T> *temp_root = nullptr;
        for (int j = 0; j < new_roots.getSize(); ++j) {
            if (roots[j] == nullptr) {
                roots[j] = new_roots[j];
            } else {
                temp_index = j;
                temp_root = roots[j];
                for (; j < new_roots.getSize(); ++j) {
                    temp_root = merge_trees(temp_root, new_roots[j]);
                    new_roots[j] = nullptr;
                }
                break;
            }
        }

        if (temp_root != nullptr) {
            roots[temp_index] = nullptr;
            roots[new_roots.getSize()] = temp_root;
        }
    }

    unsigned int i = 0;
    while (i < roots.getSize() && roots[i] == nullptr) {
        i++;
    }

    size--;
    if (i == roots.getSize()) {
        minimum = nullptr;
        return min_value;
    }

    minimum = roots[i];
    for (; i < roots.getSize(); i++) {
        if (roots[i] != nullptr && roots[i]->data <= minimum->data) {
            minimum = roots[i];
        }
    }

    return min_value;
}

template<typename T>
void BinomialHeap<T>::print_roots() {
    for (unsigned int i = 0; i < roots.getSize(); ++i) {
        std::cout << "\nroot with rank = " << i << ": ";
        if (roots[i] != nullptr) std::cout << roots[i]->data;
    }
    std::cout << '\n';
}

#endif
