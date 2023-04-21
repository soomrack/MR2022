#ifndef GRAPH_DYNAMIC_ARRAY_H
#define GRAPH_DYNAMIC_ARRAY_H




template <typename T>
class Dynamic_array{

    //static_assert();

protected:

    unsigned int size;

public:
    T* data;

    Dynamic_array();
    Dynamic_array(const unsigned int size);
    Dynamic_array(const Dynamic_array<T>& x);
    ~Dynamic_array();

    T& operator[](unsigned int idx);

    void push_back(T elm);
    void pop_back();
    unsigned int position(T elm);  // возвращает позицию первого найденного элемента + 1;
    void clear();

    void shrink(unsigned int new_size);
    void extend(unsigned int new_size);

    unsigned int length();
    void output();

};


template <typename T>
Dynamic_array<T>::Dynamic_array() {
    size = 0;
    data = nullptr;
}


template <typename T>
Dynamic_array<T>::Dynamic_array(const unsigned int new_size) {
    size = new_size;
    data = new T[size];
}


template <typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array<T>& x) {
    size = x.size;
    data = new T[size];

    for (unsigned int idx = 0; idx < x.size; idx++){
        data[idx] = x.data[idx];
    }
}


template <typename T>
Dynamic_array<T>::~Dynamic_array() {
    delete[] data;
}


template <typename T>
T& Dynamic_array<T>::operator[](unsigned int idx) {
    return data[idx];
}


template <typename T>
void Dynamic_array<T>::push_back(T elm) {
    //double temp[size + 1];
    T* temp = new T[size + 1];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    data[size++] = elm;
}


template <typename T>
void Dynamic_array<T>::pop_back() {
    // удаление последнего элемента и уменьшение размера массива на 1?;
    //double temp[size + 1];
    T* temp = new T[--size];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    //delete[] data;
    data = temp;

}


template <typename T>
unsigned int Dynamic_array<T>::position(T elm) {
    for (unsigned int idx = 0; idx < size; idx++){
        if (data[idx] == elm){
            return idx + 1;
        }
    }
    return 0;
}


template <typename T>
void Dynamic_array<T>::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
}


template <typename T>
void Dynamic_array<T>::shrink(unsigned int new_size) {
    if (new_size >= size) return;
    double* temp = new double[new_size];
    for (unsigned int idx = 0; idx < new_size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = new_size;
}


template <typename T>
void Dynamic_array<T>::extend(unsigned int new_size) {
    if (new_size <= size) return;
    T* temp = new T[new_size];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = new_size;
}


template <typename T>
unsigned int Dynamic_array<T>::length(){
    return size;
}

#endif //GRAPH_DYNAMIC_ARRAY_H
