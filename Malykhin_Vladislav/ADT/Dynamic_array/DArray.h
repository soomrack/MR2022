#ifndef MR2022_DARRAY_H
#define MR2022_DARRAY_H

#include <iostream>
#include <vector>
#include "DarrayException.h"


template<typename T>
class DArray {
protected:
    unsigned int size;
    T *data;
public:
    explicit DArray(std::vector<T> in_vector); // заполнение массива значениями из вектора при создании
    ~DArray() noexcept;
    DArray(const DArray<T> &other) ;
    DArray(DArray<T> &&other) noexcept;

    unsigned int get_size() const;
    T get_data(unsigned int id) const;
    void set(unsigned int id, T element);
    void resize(unsigned int new_size);
    void print() const;

};


#endif //MR2022_DARRAY_H