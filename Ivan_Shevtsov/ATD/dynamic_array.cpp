#include "dynamic_array.h"
#ifndef ATD_DYNAMIC_ARRAY
#define ATD_DYNAMIC_ARRAY
#include <iostream>


dynamic_array::dynamic_array()
{
    size = 0;
    data = nullptr;
    buf_size = 50;
    filled_size = 0;
}

dynamic_array::dynamic_array(const unsigned size, unsigned buf_size)  //Q: почему тут нельзя задать значение по умолчанию, если оно уже задано в хедере?

{
    this->size = size;
    this->buf_size = buf_size;
    this->data = new int[size + buf_size];
    filled_size = 0;
}

dynamic_array::dynamic_array(const dynamic_array &other)
{
    this->size = other.size;
    this->buf_size = other.buf_size;
    this->filled_size = other.filled_size;
    this->data = new int[size + buf_size];
    for (unsigned idx = 0; idx < (size + buf_size); idx++)
    {
        this->data[idx] = other.data[idx];
    }
}

dynamic_array::dynamic_array(dynamic_array &&other)
{
    this->size = other.size;
    this->buf_size =  other.buf_size;
    this->data = other.data;
    this->filled_size = other.filled_size;

    other.filled_size = 0;
    other.buf_size = 0;
    other.size = 0;
    other.data = nullptr;
}

dynamic_array& dynamic_array::operator=(const dynamic_array &other)
{
    if (other.data != nullptr)
    {
        delete[] this->data;
    }
    this->filled_size = other.filled_size;
    this->buf_size = other.buf_size;
    this->size = other.size;
    this->data = new int[size + buf_size];
    for (unsigned idx = 0; idx < (size + buf_size); idx++)
    {
        this->data[idx] = other.data[idx];
    }

    return *this;
}

bool dynamic_array::operator==(const dynamic_array& other)
{
    if (other.size != this->size or other.filled_size != this->filled_size)
        return false;
    if (other.data == nullptr && this->data == nullptr)
        if (other.buf_size != this->buf_size) {
            if (other.buf_size > this->buf_size)
                this->buf_size = other.buf_size;  // Q: add warning
            return true;
        }

    for (unsigned idx = 0; idx < size; idx++)
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

int& dynamic_array::operator[](unsigned idx)
{
    if (data == nullptr)
    {
        throw std::runtime_error("array is empty");  //#TODO
    }
    else if (idx > size + buf_size)
    {
        throw std::runtime_error("index out of the range");  //#TODO
    }
    else
        return data[idx];
}

int dynamic_array::find(int element)
{
    for (unsigned idx = 0; idx < size; idx++)
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
        for (unsigned idx = 0; idx < size; idx++)
        {
            data[idx] = rand() % (MAX_RANDOM_VALUE + 1);
        }
        filled_size = size;
    }
}

void dynamic_array::show(){
    if (size == 0)
        std::cout << "array is empty" << std::endl;
    for (unsigned idx = 0; idx < filled_size; idx++)
    {
        std::cout << data[idx] << "\t";
    }
    std::cout << "\n";
}

void dynamic_array::push_back(const int value)
{
    if (filled_size == size + buf_size ) {
        //throw "array already filled";  // Q: how to add warning here
        int *tmp_arr = new int[size + buf_size + buf_size];
        for (unsigned idx = 0; idx < size; idx++) {
            tmp_arr[idx] = data[idx];
        }
        tmp_arr[size] = value;
        delete[] data;
        data = tmp_arr;
    } else {
        data[filled_size + 1] = value;


    }
    size++;
    filled_size++;
}

void dynamic_array::pop_back()
{
    if (filled_size == size + buf_size ){
        int* tmp_arr = new int[size - 1];
        for (unsigned idx = 0; idx < size - 1; idx++)
        {
            tmp_arr[idx] = data[idx];
        }
        filled_size--;

        delete[] data;
        data = tmp_arr;}
    else{
        filled_size--;
    }

}

int dynamic_array::get_size()
{
    return size;
}

dynamic_array::~dynamic_array()
{
    filled_size = 0;
    buf_size =0;
    size = 0;
    if (data != nullptr)
    {
        delete[] data;
    }
}

void dynamic_array::resize(unsigned new_size) {
    size = new_size;
    if (data != nullptr)
    {
        delete[] data;
    }
    this->data = new int[size + buf_size];
}


#endif ATD_DYNAMIC_ARRAY