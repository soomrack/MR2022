#ifndef GRAPH_DARRAY_H
#define GRAPH_DARRAY_H


#include <iostream>
#include <list>
#include <cmath>
#include <cstring>
#include "Graph.h"


class Node;
class DArray {
protected:
    unsigned int size;
    unsigned int default_cache = 5;
    unsigned int real_cache = 5;

public:
    Node **data;
    void set_default_cache_size (unsigned int new_size);
    unsigned int get_default_cache_size() const;
    //get_reserved, get_capacity
    unsigned int get_reserved() const;
    unsigned int get_capacity() const;
    explicit DArray(unsigned int size = 0, int new_cache_size = -1); // заполнение массива значениями из массива при создании
    ~DArray() noexcept;
    unsigned int get_size() const;
    void resize(unsigned int new_size);

    Node* & operator[] (unsigned int idx);
    //Node** get_data();
};


DArray::DArray(unsigned int in_size , int new_cache_size) {
    size = in_size;
    if(new_cache_size >= 0){
        default_cache = new_cache_size;
    }
    real_cache = default_cache;
    data = new Node * [size + default_cache];
    for(int id = 0; id < size; ++id) {
        data[id] = nullptr;
    }
}


DArray::~DArray() = default;


unsigned int DArray::get_size() const {
    return size;
}

unsigned int DArray::get_default_cache_size() const {
    return default_cache;
}



unsigned int DArray::get_reserved() const{
    return real_cache;
}




unsigned int DArray::get_capacity() const{
    return real_cache + size;
}



void DArray::set_default_cache_size(unsigned int new_cache_size) {
    default_cache = new_cache_size;
}


Node* & DArray::operator[] (unsigned int idx){
    return data[idx];
}


void DArray::resize(unsigned int new_size) {
    if (new_size <= size + real_cache) {
        real_cache -= new_size - size;
        size = new_size;
        return ;
    }
    Node* *new_data = new Node*[new_size + default_cache];
    std::memcpy(new_data, data, sizeof(Node*) * size); //умножать на std::minimum(new_data, data)
    size = new_size;
    delete (data);
    data = new_data;
    real_cache = default_cache;
}


/*Node* DArray::get_data() {
    return
}*/


#endif //GRAPH_DARRAY_H
