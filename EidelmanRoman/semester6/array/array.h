#ifndef MR2022_ARRAY_H
#define MR2022_ARRAY_H


#include <iostream>


class array {
private:
    double* data;
    unsigned int size;
public:
    array() = default;
    array(unsigned int len);
    array(unsigned int len, double x);
    array(const array& arr);
    array(array&& arr) noexcept;
    ~array();

    double operator[](unsigned int index);
    array& operator=(const array& arr);
    array& operator=(array&& arr) noexcept;

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
    void swap(array arr);
};


#endif //MR2022_ARRAY_H
