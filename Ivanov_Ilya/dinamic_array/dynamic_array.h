#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


class Array_Exceptions: public std::domain_error {
public:
    Array_Exceptions(const char* const error) : std::domain_error(error) {}
};

Array_Exceptions IS_EMPTY ("Error: Array is empty");


class DynArray {
private:
    unsigned int *array;
    unsigned int size;
    unsigned int filled_size;

public:
    unsigned buffer;
    DynArray();
    DynArray(unsigned int size, unsigned int buffer = 10);
    DynArray(const DynArray &other);
    ~DynArray();
    void fill_random(int num);
    void add(int value, int idx);
    void remove(int idx);
    void print();
    void clean();
    void resize(unsigned int new_size);
    unsigned int get(unsigned int number);
    void set(unsigned int number, unsigned int item);
    unsigned int operator[] (unsigned int number);
    bool is_empty();
    void dop();
};


DynArray::DynArray() {
    {
        size = 0;
        array = nullptr;
        buffer = 50;
        filled_size = 0;
    }
}


DynArray::DynArray (const unsigned size, unsigned buffer)
{
    this->size = size;
    this->buffer = buffer;
    array = new unsigned int [size + buffer];
    filled_size = 0;
}


DynArray::DynArray(const DynArray &other)
{
    size = other.size;
    buffer = other.buffer;
    filled_size = other.filled_size;
    array = new unsigned int[size + buffer];
    for (unsigned idx = 0; idx < (size + buffer); idx++)
    {
        array[idx] = other.array[idx];
    }
}


DynArray::~DynArray() {
    filled_size = 0;
    buffer = 0;
    size = 0;
    if (array != nullptr) {
        delete[] array;
    }
}


void DynArray::fill_random(int num) {
    srand(time(NULL));
    array = new unsigned int[num];
    for (int i = 0; i < num - 1; ++i) {
        array[i] = rand() % 100;
    }
    size = num;
    filled_size = size;
}


void DynArray::add(int value, int number) {
    unsigned int *temp = new unsigned int[size + 1];
    for (int i = 0; i < number; ++i) {
        temp[i] = array[i];
    }
    temp[number] = value;
    for (int i = number; i < size; ++i) {
        temp[i + 1] = array[i];
    }
    delete array;
    array = temp;
    size++;
    filled_size++;
}


void DynArray::remove(int number) {
    unsigned int *temp = new unsigned int[size - 1];
    for (int i = 0; i < number; ++i) {
        temp[i] = array[i];
    }
    for (int i = number + 1; i < size; ++i) {
        temp[i - 1] = array[i];
    }
    delete array;
    array = temp;
    size--;
    if (size == 0) {
        throw IS_EMPTY;
    }
    filled_size--;
}


void DynArray::print() {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}


void DynArray::clean() {
    delete[] array;
    array = nullptr;
    size = NULL;
    filled_size = NULL;
}


void DynArray::resize(unsigned int new_size) {
    if (new_size < size)
        size = new_size;
    auto* new_data = new unsigned int[new_size + buffer]; //добавлен буффер
    memcpy(new_data, array, sizeof(unsigned int) * size);
    delete[] array;
    array = new_data;
    size = new_size;
}



unsigned int DynArray::get(unsigned int number) {
    return array[number];
}


void DynArray::set(unsigned int item, unsigned int number) {
    array[number] = item;
}


unsigned int DynArray::operator[](unsigned int number) {
    return array[number];
}


bool DynArray::is_empty() {
    return size == 0;
}


#endif //DYNAMIC_ARRAY
