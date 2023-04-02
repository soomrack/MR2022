#ifndef MR2022_ARRAY_H
#define MR2022_ARRAY_H


#include <iostream>
#include <cstring>


class Array {
private:
    double* data;
    unsigned int size;
public:
    Array() = default;
    Array(unsigned int len);
    Array(unsigned int len, double x);
    Array(const Array& arr);
    Array(Array&& arr) noexcept;
    ~Array();

    double operator[](unsigned int index);
    Array& operator=(const Array& arr);
    Array& operator=(Array&& arr) noexcept;

    void add(double x);
    void add(double x, unsigned int to);
    unsigned int arr_size();
    double back();
    void fill(double x);
    double front();
    double* get(unsigned int index);
    void output();
    void rm();
    void rm(unsigned int from);
    void sort();
    void swap(Array arr);
};


Array::Array(unsigned int len) {
    size = len;
    data = new double[size];
}


Array::Array(unsigned int len, double x) {
    size = len;
    data = new double[size];
    for (int i = 0; i < size; ++i)
        data[i] = x;
}


Array::Array(const Array& arr) {
    size = arr.size;
    data = new double[size];
    memcpy(data, arr.data, size * sizeof(unsigned int));
}


Array::Array(Array&& arr) noexcept {
    size = arr.size;
    data = new double[size];
    arr.data = nullptr;
    memcpy(data, arr.data, size * sizeof(unsigned int));
}


Array::~Array() {
    delete[] data;
}


double Array::operator[](unsigned int index) {
    return data[index];
}


Array& Array::operator=(const Array& arr) {
    if (this == &arr) {
        return *this;
    }
    delete[] data;
    size = arr.size;
    data = new double[size];
    memcpy(data, arr.data,  size * sizeof(unsigned int));
    return *this;
}


Array& Array::operator=(Array&& arr) noexcept {
    if (this == &arr) {
        return *this;
    }
    delete[] data;
    data = arr.data;
    arr.data = nullptr;
    return *this;
}


unsigned int Array::arr_size() {
    return size;
}


void Array::add(double x) {
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


void Array::add(double x, unsigned int to) {
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


double Array::back() {
    return data[size - 1];
}


void Array::fill(double x) {
    for (int i = 0; i < size; ++i)
        data[i] = x;
}


double Array::front() {
    return data[0];
}


double* Array::get(unsigned int index) {
    return &data[index];
}


void Array::output() {
    std::cout << "[";
    for (int i = 0; i < size - 1; ++i)
        std::cout << data[i] << ", ";
    std::cout << data[size - 1] << "]" << "\n";
}


void Array::rm() {
    --size;
    double* newdata;
    newdata = new double[size];
    for (int i = 0; i < size; ++i) {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}


void Array::rm(unsigned int from) {
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


void Array::swap(Array arr) {

}
#endif //MR2022_ARRAY_H
