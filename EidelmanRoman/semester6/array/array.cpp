#include <cstring>
#include "array.h"


array::array(unsigned int len) {
    size = len;
    data = new double[size];
}


array::array(unsigned int len, double x) {
    size = len;
    data = new double[size];
    for (int i = 0; i < size; ++i)
        data[i] = x;
}


array::array(const array& arr) {
    size = arr.size;
    data = new double[size];
    memcpy(data, arr.data, size * sizeof(unsigned int));
}


array::array(array&& arr) noexcept {
    size = arr.size;
    data = new double[size];
    arr.data = nullptr;
    memcpy(data, arr.data, size * sizeof(unsigned int));
}


array::~array() {
    delete[] data;
}


double array::operator[](unsigned int index) {
    return data[index];
}


array& array::operator=(const array& arr) {
    if (this == &arr) {
        return *this;
    }
    delete[] data;
    size = arr.size;
    data = new double[size];
    memcpy(data, arr.data,  size * sizeof(unsigned int));
    return *this;
}


array& array::operator=(array&& arr) noexcept {
    if (this == &arr) {
        return *this;
    }
    delete[] data;
    data = arr.data;
    arr.data = nullptr;
    return *this;
}


unsigned int array::arr_size() {
    return size;
}


void array::add(double x) {
    ++size;
    double* newdata;
    newdata = new double[size];
    for (int i = 0; i < size - 1; ++i) {
        newdata[i] = data[i];
    }
    newdata[size - 1] = x;
    delete[] data;
    data = newdata;
}


void array::add(double x, unsigned int to) {
    ++size;
    double* newdata;
    newdata = new double[size];
    for (int i = 0; i < size; ++i) {
        if (i == to)
            newdata[i] = x;
            continue;
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}


double array::back() {
    return data[size - 1];
}


void array::fill(double x) {
    for (int i = 0; i < size; ++i)
        data[i] = x;
}


double array::front() {
    return data[0];
}


double* array::get(unsigned int index) {
    return &data[index];
}


void array::output() {
    std::cout << "[";
    for (int i = 0; i < size - 1; ++i)
        std::cout << data[i] << ", ";
    std::cout << data[size - 1] << "]" << "\n";
}


void array::rm() {
    --size;
    double* newdata;
    newdata = new double[size];
    for (int i = 0; i < size; ++i) {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}


void array::rm(unsigned int from) {
    --size;
    double* newdata;
    newdata = new double[size];
    for (int i = 0; i < size; ++i) {
        if (i == from)
            continue;
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}



//void array::sort() {
//    for (int i = 0; i < size; ++i) {

//    }
//}


void array::swap(array arr) {

}