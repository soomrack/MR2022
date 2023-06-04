#ifndef CPP_DYNAMIC_ARRAY_H
#define CPP_DYNAMIC_ARRAY_H

#include <iostream>
#include <cmath>

const double COMPARATION_CONST = 0.0001;


class Dynamic_array{

protected:

    unsigned int size;
    unsigned int capacity;
    float reserve;

public:
    double* data;

    Dynamic_array();
    explicit Dynamic_array(unsigned int size_, float reserve_);
    Dynamic_array(const Dynamic_array& x);
    Dynamic_array& operator=(const Dynamic_array& x);
    ~Dynamic_array();

    void push_back(double elm);
    void pop_back();
    void set(unsigned int pos, double elm);
    void resize(unsigned int size_);

    void output() const;

    unsigned int contain(double elm) const;
    void del(double elm) const;
    void remove(double elm);
    void clear();
    void shrink(unsigned int size_);
    void extend(unsigned int size_);
    unsigned int length() const;
};


Dynamic_array::Dynamic_array() {
    size = 0;
    reserve = 0;
    capacity = 0;
    data = nullptr;
}


Dynamic_array::Dynamic_array(const unsigned int size_, float reserve_) {
    size = size_;
    reserve = reserve_;
    capacity = unsigned(float(size) * (1 + reserve));  // capacity = size * (1 + reserve)
    if (capacity - size < 1) capacity = size + 1;
    data = new double[capacity];
}


Dynamic_array::Dynamic_array(const Dynamic_array& x) {
    size = x.size;
    reserve = x.reserve;
    capacity = x.capacity;
    data = new double[capacity];

    for (unsigned int idx = 0; idx < x.size; idx++){
        data[idx] = x.data[idx];
    }
}


Dynamic_array &Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!data) delete[] data;
        size = x.size;
        reserve = x.reserve;
        capacity = x.capacity;
        data = new double[capacity];
        for (unsigned int idx = 0; idx < capacity; idx++){
            data[idx] = x.data[idx];
        }
    }
    return *this;
}


Dynamic_array::~Dynamic_array() {
    delete[] data;
}


void Dynamic_array::push_back(double elm) {
    if (capacity < size + 1) {
        capacity = unsigned(float(size) * (1 + reserve));  // capacity = size * (1 + reserve)
        auto* temp = new double[capacity];
        for (unsigned int idx = 0; idx < size; idx++){
            temp[idx] = data[idx];
        }
        data = temp;
        delete[] data;
    }
    data[size++] = elm;
}


void Dynamic_array::pop_back() {
    data[size - 1] = 0;
    size--;
}


void Dynamic_array::set(unsigned int pos, double elm) {
    push_back(0);
    for (unsigned int idx = size; idx > pos; idx--)
        data[idx] = data[idx - 1];
    data[pos] = elm;
}


void Dynamic_array::resize(unsigned int size_) {
    if (capacity < size_) {
        capacity = unsigned(float(size_) * (1 + reserve));  // capacity = size_ * (1 + reserve)
        auto* temp = new double[capacity];
        for (unsigned int idx = 0; idx < size_; idx++){
            temp[idx] = data[idx];
        }
        delete[] data;
        data = temp;
    }
    size = size_;
}


void Dynamic_array::output() const {
    std::cout << "Length: " << size << "\n";
    if (size > 0) {
        for (unsigned int idx = 0; idx < size; idx++) {
            if (fabs(data[idx]) > COMPARATION_CONST && fabs(data[idx]) < pow(COMPARATION_CONST, -1))
                std::cout << data[idx] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

unsigned int Dynamic_array::length() const {
    return size;
}

unsigned int Dynamic_array::contain(double elm) const {
    for (unsigned int idx = 0; idx < size; idx++){
        if (fabs(data[idx] - elm) < COMPARATION_CONST){
            return idx + 1;
        }
    }
    return 0;
}


void Dynamic_array::del(double elm) const {
    unsigned int point = contain(elm);
    if (point){
        data[point - 1] = 0.0;
    }
}


void Dynamic_array::remove(double elm) {
    unsigned int point = contain(elm);
    if (point == 0) return;
    auto *temp = new double [size - 1];
    for (unsigned int idx = 0; idx < point - 1; idx++){
        temp[idx] = data[idx];
    }
    for (unsigned int idx = point; idx < size; idx++){
        temp[idx - 1] = data[idx];
    }
    //delete[] data;
    data = temp;
    size--;
}


void Dynamic_array::clear() {
    data = nullptr;
    size = 0;
}


void Dynamic_array::shrink(unsigned int size_) {
    if (size_ >= size) return;
    auto* temp = new double[size_];
    for (unsigned int idx = 0; idx < size_; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


void Dynamic_array::extend(unsigned int size_) {
    if (size_ <= size) return;
    auto* temp = new double[size_];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


#endif //CPP_DYNAMIC_ARRAY_H
