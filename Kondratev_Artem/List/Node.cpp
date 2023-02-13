//
// Created by user on 11.02.23.
//

#include "Node.h"


template<typename T>
Node<T>::Node(T object) {
    data = object;
}


template
class Node<double>;

template
class Node<float>;

template
class Node<uint64_t>;

template
class Node<int>;
