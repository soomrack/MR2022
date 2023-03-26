#ifndef MR2022_DYNAMIC_ARRAY_H
#define MR2022_DYNAMIC_ARRAY_H

#include <algorithm>

class ARRAY_EXCEPTION: public std::domain_error
{
public:
    explicit ARRAY_EXCEPTION(const char* const str): std::domain_error(str) {};
};

ARRAY_EXCEPTION BADALLOC("Memory is not allocated");
ARRAY_EXCEPTION OUTOFRANGE("Out of range");
template <typename T>
class dynamic_array {
protected:
    unsigned int capacity;
    unsigned int size;
    T* arr;


public:
    dynamic_array();
    explicit dynamic_array(unsigned int);
    dynamic_array(const dynamic_array& A);
    dynamic_array(dynamic_array&& A) noexcept;
    ~dynamic_array();

    T& operator[](unsigned);
    void resize(unsigned int);
    void replace (T, T);
    void insert (T, unsigned int);
    bool search (T);
    unsigned int get_size() {return size;}
    unsigned int get_capacity() {return capacity;}
    unsigned int get_free_capacity() {return capacity - size;}
    dynamic_array& operator=(const dynamic_array& A);
};

template <typename T>
dynamic_array<T>::dynamic_array() {
    arr = nullptr;
    capacity = 0;
    size = 0;
}

template <typename T>
dynamic_array<T>::dynamic_array(const unsigned int value) {
    capacity = value;
    size = 0;
    arr = new T [capacity];
    if (!arr) throw BADALLOC;
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &array) : capacity(array.capacity), size(array.size) {
    this->arr = new T[this->size];
    if (!arr) throw BADALLOC;
    memcpy(arr,array.arr,sizeof(T)*array.size);
}

template <typename T>
dynamic_array<T>::dynamic_array(dynamic_array&& array) noexcept : capacity(array.capacity),size(array.size), arr(array.arr) {
    array.size = 0;
    array.capacity = 0;
    array.arr = nullptr;
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
    size = 0;
    capacity = 0;
    delete arr;
}

template <typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array& A) {
    if (this!=&A)
        if(!arr) delete arr;
    capacity = A.capacity;
    size = A.size;
    arr = new T [capacity];
    if (!arr) throw BADALLOC;
    memcpy(arr,A.arr, capacity * sizeof(T));
    return *this;
}

template <typename T>
bool dynamic_array<T>::search(T num) {
    for(unsigned int i = 0; i < size; i++) {
        if (arr[i] == num) return true;
    }
    return false;
}



template <typename T>
void dynamic_array<T>::replace(T num, T den) {
    if(search(num)){
        for (unsigned int i = 0; i < size; i++) {
            if (arr[i] == num) {
                arr[i] = den;
                break;
            }
        }
    }
}
template <typename T>
void dynamic_array<T>::insert(T value, unsigned int idx)
{
    if (idx > capacity) throw OUTOFRANGE ;
    if (size == capacity) resize(capacity * 2); // В случае конца массива, емкость расширяется в два раза
    std::copy(arr + idx, arr + size, arr + idx + 1);
    arr[idx] = value;
    size++;
}

template<typename T>
T& dynamic_array<T>::operator[](const unsigned int idx)
{
    return arr[idx];
}

template <typename T>
void dynamic_array<T>::resize(unsigned int new_size) {
    if (new_size < size) size = new_size;
    capacity = new_size;
    auto* new_data = new T[capacity];
    memcpy(new_data,arr,sizeof(T) * capacity);
    delete arr;
    arr = new_data;
}

#endif //MR2022_DYNAMIC_ARRAY_H
