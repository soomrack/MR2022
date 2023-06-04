#ifndef MR2022_DYNAMIC_ARRAY_H
#define MR2022_DYNAMIC_ARRAY_H

#include <algorithm>
#include <cstring>
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
    size_t capacity;
    size_t size;
    T* data;


public:
    dynamic_array();
    explicit dynamic_array(unsigned int);
    dynamic_array(const dynamic_array& A);
    dynamic_array(dynamic_array&& A) noexcept;
    dynamic_array& operator=(const dynamic_array&);
    dynamic_array& operator=(dynamic_array&&) noexcept;
    ~dynamic_array();

    T& operator[](unsigned);
    void resize(unsigned int);
    void replace (T, T);
    void insert (T, unsigned int);
    bool search (T);
    unsigned int get_size() {return size;}
    unsigned int get_capacity() {return capacity;}
    unsigned int get_free_capacity() {return capacity - size;}
};

template <typename T>
dynamic_array<T>::dynamic_array() {
    data = nullptr;
    capacity = 0;
    size = 0;
}

template <typename T>
dynamic_array<T>::dynamic_array(const unsigned int value) {
    capacity = value;
    size = 0;
    data = new T [capacity];
    if (!data) throw BADALLOC;
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &array) : capacity(array.capacity), size(array.size) {
    this->data = new T[this->size];
    if (!data) throw BADALLOC;
    memcpy(data,array.data,sizeof(T)*array.size);
}

template <typename T>
dynamic_array<T>::dynamic_array(dynamic_array&& array) noexcept : capacity(array.capacity), size(array.size), data(array.data) {
    array.size = 0;
    array.capacity = 0;
    array.data = nullptr;
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
    size = 0;
    capacity = 0;
    delete data;
}

template <typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array& A) {
    if (this == &A) return *this;
    capacity = A.capacity;
    size = A.size;
    data = new T [capacity];
    if (!data) throw BADALLOC;
    memcpy(data,A.data, capacity * sizeof(T));
    return *this;
}

template <typename T>
bool dynamic_array<T>::search(T num) {
    for(unsigned int i = 0; i < size; i++) {
        if (data[i] == num) return true;
    }
}

template <typename T>
void dynamic_array<T>::replace(T num, T den) {
    if(search(num)){
        for (unsigned int i = 0; i < size; i++) {
            if (data[i] == num) {
                data[i] = den;
                break;
            }
        }
    }
}

template <typename T>
void dynamic_array<T>::insert(T value, unsigned int idx) {
    if (idx > capacity) throw OUTOFRANGE ;
    if (size == capacity) resize(capacity * 2); // В случае конца массива, емкость расширяется в два раза
    std::copy(data + idx, data + size, data + idx + 1);
    data[idx] = value;
    size++;
}

template<typename T>
T& dynamic_array<T>::operator[](const unsigned int idx) {
    return data[idx];
}

template <typename T>
void dynamic_array<T>::resize(unsigned int new_size) {
    if (new_size < size) size = new_size;
    capacity = new_size;
    auto* new_data = new T[capacity];
    memcpy(new_data,data,sizeof(T) * size);
    delete data;
    data = new_data;
}

template <typename T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T>&& array) noexcept {
    if (this == &array) return *this;
    size = array.size;
    capacity = array.capacity;
    data = array.data;
    array.size = 0;
    array.capacity = 0;
    array.data = nullptr;
}
#endif //MR2022_DYNAMIC_ARRAY_H
