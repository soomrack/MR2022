//
// Created by delta on 13.02.2023.
//

#ifndef CLIONPROJECTS_MAIN_H
#define CLIONPROJECTS_MAIN_H

#endif //CLIONPROJECTS_MAIN_H
#include <iostream>
using namespace std;

template <typename T>
class DynamicArray {

public:
    unsigned int size;
    T *values;
//конструкторы
DynamicArray();
DynamicArray(unsigned int size);
DynamicArray(const DynamicArray &other);
DynamicArray(DynamicArray&& DA) noexcept; //переноса
//деструкторы
~DynamicArray();

//методы
DynamicArray<T> one_number(T n);
DynamicArray<T> i_number();
//переопределенные операторы
DynamicArray<T>& operator=(DynamicArray<T>&& DA);
template <typename R>friend std::ostream& operator<<(std::ostream& out, DynamicArray<R> DA); //для оператора вывода необходимо использовать другой шаблон};
void output();
T get(int position); //метод доступа к элементу

unsigned int length();
void increase(double temp);
void decrease();

};

//конструктор создает пустой динамический массив
template <typename T>
DynamicArray<T>::DynamicArray() {
    size = 0;
    values = nullptr;
}

template <typename T>
DynamicArray<T>::DynamicArray(unsigned int temp_size) {
    size = temp_size;
    values = new T[size];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) {
    size = other.size;
    values = new T[size];
    if (values==nullptr) throw ;
    memcpy(values, other.values, size * sizeof(T)); //функция memcpy() копирует данные other.values в values
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->values;
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& DA) noexcept : values(DA.values), size(DA.size)
{
    DA.values = nullptr;
    DA.size = 0;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::one_number(T n) {

    for (unsigned int i = 0; i < size; ++i) {
        values[i] = n;
    }
    return *this;

}

template <typename T>
DynamicArray<T> DynamicArray<T>::i_number() {

    for (unsigned int i = 0; i < size; ++i) {
        values[i] = i;
    }
    return *this;

}

template <typename T>
void DynamicArray<T>::output() {

    if (size > 0)
    {
        for (int i = 0; i < size; ++i) {
            cout << values[i] << " ";
        }
    }
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& DA)
{
    if (this != &DA){
        if (values == nullptr) delete[] values;
    }
    size = DA.size;

    this->values = new double[size];
    for (unsigned int i = 0; i < size; i++){
        values[i] = DA.values[i];
    }

    return *this;
}

template <typename R>
std::ostream& operator<<(std::ostream& out, DynamicArray<R> DA)
{
    {
        for (unsigned int i = 0; i < DA.size; i++)
        {
            out << DA.values[i] << "\t";
        }
        out << std::endl;
        return(out);
    }
}

template <typename T>
T DynamicArray<T>::get(int position){
    return values[position];
}

template <typename T>
unsigned int DynamicArray<T>::length() {
    return size;
}

template <typename T>
void DynamicArray<T>::increase(double temp) {
    T *temp_array = new T[size + 1];
    for (int i = 0; i < size; i++) {
        temp_array[i] = values[i];
    }

    delete[] values;
    values = temp_array;
    values[size] = temp;
    size++;
}

template <typename T>
void DynamicArray<T>::decrease() {
    T *temp_array = new T[size - 1];
    for (int i = 0; i < size-1; i++) {
        temp_array[i] = values[i];
    }

    delete[] values;
    values = temp_array;
    size--;
}

void DynamicArrayTestProgram()
{
    double TempElement;
    int TempLength, K = 5;
    DynamicArray<double> A;
    A = DynamicArray<double>(5).i_number();
    A.increase(5);
    TempElement = A.get(K);
    cout << "current element position " << K <<" :" <<TempElement;
    A.decrease();
    TempLength = A.length();
    cout << "\ncurrent length: " << TempLength;
}
