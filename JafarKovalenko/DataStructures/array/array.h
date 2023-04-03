#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <utility>

template<class T = double>
class DynamicArray
{

private:
    
    size_t size_;
    size_t capacity_;
    T* array_;

    void swap(DynamicArray<T>& other);
    size_t partition(size_t left_bound, size_t right_bound);
    void quickSortImpl(size_t left_bound, size_t right_bound);

public:

    explicit DynamicArray(size_t size = 0);
    ~DynamicArray();
    DynamicArray(const DynamicArray<T>& other);
    
    DynamicArray<T>& operator= (const DynamicArray<T>& other);
    T& operator[] (size_t index);
    const T operator[] (size_t index) const;
    DynamicArray<T> operator+(const DynamicArray<T>& other) const;

    size_t size() const;
    size_t capacity() const;
    
    void resize(size_t new_size);
    void sort();    
    
    void clear();
    bool empty();
    
};



template<class T>
DynamicArray<T>::DynamicArray(size_t size)
    : size_(size), capacity_(size + 10), array_(new T[capacity_])
{
    for (int i = 0; i < capacity_; ++i)
        array_[i] = 0;
}

template<class T>
DynamicArray<T>::~DynamicArray() { delete[] array_; }

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
    : DynamicArray(other.size_) 
{ 
    for (int index = 0; index < other.size_; ++index)
         array_[index] = other[index];
}

template<class T>
void DynamicArray<T>::swap(DynamicArray<T> &other)
{
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
    std::swap(other.array_, array_);
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &other)
{
    if (this != &other)
        DynamicArray(other).swap(*this);
    return *this;
}

template<class T>
size_t DynamicArray<T>::size() const { return size_; }

template<class T>
size_t DynamicArray<T>::capacity() const { return capacity_; }

template<class T>
void DynamicArray<T>::resize(size_t new_size)
{
    if (new_size < capacity_)
    {
        size_ = new_size;
        return;
    }

    DynamicArray temp(new_size);
            
    for (int index = 0; index < size_; ++index)
        temp.array_[index] = array_[index];
                    
    delete[] array_;
    array_ = temp.array_;
    size_ = temp.size_;
    capacity_ = temp.capacity_;
    temp.array_ = nullptr;
}

template<class T>
T& DynamicArray<T>::operator[](size_t index)
{
    if (index >= size_)
        return array_[size_ - 1];
    return array_[index];
}

template<class T>
const T DynamicArray<T>::operator[](size_t index) const
{
    if (index >= size_)
        return 0;
    return array_[index];
}

template<class T>
size_t DynamicArray<T>::partition(size_t left_bound, size_t right_bound)
{
    T pivot = array_[right_bound];
    size_t less = left_bound;

    for (int i = left_bound; i < right_bound; ++i)
    {
        if (array_[i] < pivot)
        {
            std::swap(array_[i], array_[less]);
            ++less;
        }
    }

    std::swap(array_[less], array_[right_bound]);
    return less;
        
}

template<class T>
void DynamicArray<T>::quickSortImpl(size_t left_bound, size_t right_bound)
{
    if (left_bound < right_bound)
    {
        size_t new_bound = partition(left_bound, right_bound);
        quickSortImpl(left_bound, !new_bound ? new_bound : new_bound - 1);
        quickSortImpl(new_bound + 1, right_bound);
    }

}

    
template<class T>
void DynamicArray<T>::sort()
{
    if (size_ > 1)
        quickSortImpl(0, size_ - 1);
}

template<class T>
DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray<T>& other) const
{
    DynamicArray<T> result(size() + other.size());
                
    for (int index = 0; index < size(); ++index)
        result.array_[index] = array_[index];

    for (int index = 0; index < other.size(); ++index)
        result.array_[index + size()] = other[index];

    return result;
}

template<class T>
void DynamicArray<T>::clear()
{
    size_ = 0;
}

template<class T>
bool DynamicArray<T>::empty()
{
    return !size_ ? true : false;
}

#endif // ARRAY_H

