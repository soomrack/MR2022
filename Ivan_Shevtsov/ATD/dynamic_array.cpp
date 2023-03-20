#include "dynamic_array.h"
#ifndef ATD_DYNAMIC_ARRAY
#define ATD_DYNAMIC_ARRAY
#include <iostream>


dynamic_array::dynamic_array()
{
    size = 0;
    data = nullptr;
}

dynamic_array::dynamic_array(const int size)
{
    this->size = size;
    this->data = new int[size];
}

dynamic_array::dynamic_array(const dynamic_array &other)
{
    this->size = other.size;
    this->data = new int[size];
    for (int idx = 0; idx < size; idx++)
    {
        this->data[idx] = other.data[idx];
    }
}

dynamic_array::dynamic_array(dynamic_array &&other)
{
    this->size = other.size;
    this->data = other.data;

    other.size = 0;
    other.data = nullptr;
}

dynamic_array& dynamic_array::operator=(const dynamic_array &other)
{
    if (other.data != nullptr)
    {
        delete[] this->data;
    }
    this->size = other.size;
    this->data = new int[size];
    for (int idx = 0; idx < size; idx++)
    {
        this->data[idx] = other.data[idx];
    }

    return *this;
}

bool dynamic_array::operator==(const dynamic_array& other)
{
    if (other.size != this->size)
        return false;
    if (other.data == nullptr && this->data == nullptr)
        return true;
    for (int idx = 0; idx < size; idx++)
    {
        if (other.data[idx] != this->data[idx])
            return false;
    }
    return true;
}

bool dynamic_array::operator!=(dynamic_array& other)
{
    return !(other == *this);
}

int& dynamic_array::operator[](int idx)
{
    if (data == nullptr)
    {
        throw std::runtime_error("array is empty");
        exit;
    }
    else if (idx > size)
    {
        throw std::runtime_error("index out of the range");
        exit;
    }
    else
        return data[idx];
}

int dynamic_array::find(int element)
{
    for (int idx = 0; idx < size; idx++)
        if (data[idx] == element)
            return idx;
    return -1;
}

void dynamic_array::fill_random(int MAX_RANDOM_VALUE)
{
    if (size == 0)
        throw std::runtime_error("can`t fill zero size array");
    else
    {
#ifndef DEBUG
        srand(time(0));
#endif
#ifdef DEBUG
        srand(42);
#endif
        for (int idx = 0; idx < size; idx++)
        {
            data[idx] = rand() % (MAX_RANDOM_VALUE + 1);
        }
    }
}

void dynamic_array::show()
{

    if (size == 0)
        std::cout << "array is empty" << std::endl;
    for (int idx = 0; idx < size; idx++)
    {
        std::cout << data[idx] << "\t";
    }
    std::cout << "\n";
}

void dynamic_array::push_back(const int value)
{
    int* tmp_arr = new int[size + 1];
    for (int idx = 0; idx < size; idx++)
    {
        tmp_arr[idx] = data[idx];
    }
    tmp_arr[size] = value;
    size++;

    delete[] data;
    data = tmp_arr;

}

void dynamic_array::pop_back()
{
    int* tmp_arr = new int[size - 1];
    for (int idx = 0; idx < size - 1; idx++)
    {
        tmp_arr[idx] = data[idx];
    }
    size--;

    delete[] data;
    data = tmp_arr;

}

int dynamic_array::get_size()
{
    return size;
}

dynamic_array::~dynamic_array()
{
    size = 0;
    if (data != nullptr)
    {
        delete[] data;
    }
}

void dynamic_array::resize(int new_size) {

}

#endif ATD_DYNAMIC_ARRAY