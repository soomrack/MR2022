#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template<class T>
class DynamicArray {
private:
    T *data;
    size_t size;
    size_t capacity;

public:
    DynamicArray();;
    ~DynamicArray();
    T &operator[](size_t index);
    DynamicArray<T> &operator=(const DynamicArray &newArr);

    size_t getSize();
    void expand(int k);
    void push_tail(const T &item);
    void print(std::ostream &out) const;
    void pop_tail();
};

template<typename T>
DynamicArray<T>::DynamicArray() {
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    if (data != nullptr) delete[] data;
}

template<typename T>
T &DynamicArray<T>::operator[](const size_t index) {
    try {
        if (index >= size) throw std::out_of_range("Invalid index!1");
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        exit(-1);
    }
    return data[index];
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &newArr) {
    if (this == &newArr) return *this;

    if (data != nullptr) delete[] data;

    size = newArr.size;
    capacity = newArr.capacity;
    data = new T[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = newArr.data[i];
    }
    return *this;
}

template<class T>
size_t DynamicArray<T>::getSize() {
    return size;
}

template<class T>
void DynamicArray<T>::expand(int k) {
    T *temp = new T[size];
    for (int i = 0; i < size; ++i)
        temp[i] = data[i];
    capacity += k;
    data = new T[capacity];
    for (int i = 0; i < size; ++i) {
        data[i] = temp[i];
    }
    delete[] temp;
}

template<class T>
void DynamicArray<T>::push_tail(const T &item) {
    if (size == capacity) {
        expand(capacity + 1);
    }
    data[size] = item;
    size++;
}

template<class T>
void DynamicArray<T>::print(std::ostream &out) const {
    for (size_t i = 0; i < size; i++)
        out << data[i] << ' ';
}

template<class T>
void DynamicArray<T>::pop_tail() {
    if (size != 0) size--;
    else throw std::out_of_range("Invalid index!2");
}

#endif
