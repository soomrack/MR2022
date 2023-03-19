
#ifndef MR2022_DYNAMIC_ARRAY_H
#define MR2022_DYNAMIC_ARRAY_H
#include <algorithm>
template <typename T>
class dynamic_array {
protected:
    unsigned int size;
    unsigned int capacity;
    T* arr;


public:
    dynamic_array();
    dynamic_array(const unsigned int);
    dynamic_array(const dynamic_array& A);
    dynamic_array(dynamic_array&& A) noexcept;
    ~dynamic_array();

    T& operator[](const unsigned);
    void resize_capacity(); // Увеличение размера в два раза
    void resize(unsigned int);
    void replace (T, T);
    void insert (T, int);
    bool search (T);
    void fill_zero();
    unsigned int lenght();
    dynamic_array& operator=(const dynamic_array& A);
};

template <typename T>
void dynamic_array<T>::fill_zero()
{
    for(unsigned int i = 0; i < capacity; i++)
        arr[i] = 0;
    size = capacity;
}
template <typename T>
dynamic_array<T>::dynamic_array() {
    arr = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
dynamic_array<T>::dynamic_array(const unsigned int number) {
    size = 0;
    capacity = number;
    arr = new T [capacity];
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &array) : capacity(array.capacity), size(array.size) {
    this->arr = new T[this->capacity];
    if (!arr) throw std::bad_alloc();
    memcpy(arr,array.arr,sizeof(T)*array.capacity);
}

template <typename T>
dynamic_array<T>::dynamic_array(dynamic_array&& array) noexcept : size(array.size), arr(array.arr),capacity(array.capacity) {
    array.capacity = 0;
    array.size = 0;
    array.arr = nullptr;
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
    capacity = 0;
    size = 0;
    delete arr;
    arr = nullptr;
}

template <typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array& A) {
    if (this!=&A)
        if(!arr) delete arr;
    size = A.size;
    capacity = A.capacity;
    arr = new T [size];
    memcpy(arr,A.arr, size * sizeof(T));
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
void dynamic_array<T>::resize(unsigned int new_size) {
    auto* new_data = new T[new_size];
    memcpy(new_data,arr,sizeof(T) * new_size);
    size = new_size;
    delete arr;
    arr = new_data;
}

template <typename T>
void dynamic_array<T>::replace(T num, T den) {
    for (unsigned int i = 0; i < size; i++) {
        if (arr[i] == num) {
            arr[i] = den;
        }
    }
}
template <typename T>
void dynamic_array<T>::insert(T value, int idx) {
    if (idx > size || idx < 0) throw std::out_of_range("Out of range");
    if (size == capacity) resize_capacity();
    std::copy(arr + idx, arr + size, arr + idx + 1);
    arr[idx] = value;
    size++;
}
template <typename T>
unsigned int dynamic_array<T>::lenght() {return size;}

template<typename T>
T& dynamic_array<T>::operator[](const unsigned int idx)
{
    return arr[idx];
}

template<typename T>
void dynamic_array<T>::resize_capacity()
{
    unsigned int new_capacity = capacity * 2;
    T *new_arr = new T[new_capacity];

    // копируем элементы в новый массив
    memcpy(new_arr,arr,sizeof(T) * new_capacity);

    delete[] arr;
    arr = new_arr;
    capacity = new_capacity;
}
#endif //MR2022_DYNAMIC_ARRAY_H
