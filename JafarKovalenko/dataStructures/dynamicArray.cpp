#include <iostream>

template<class T>
class dynamicArray
{
    private:
        T* array;
        int array_size;
        int array_capacity;
    public:
        dynamicArray(int size);
        ~dynamicArray();

        const int size();
        const int capacity();

        T operator [] (int index);

        void push_back(T data);
        void push_front(T data);
        void pop_back();
        void pop_front();
        void insert(int pos, T data);
        void erase(int pos);
        void clear();

        bool empty();
        void sort();
        dynamicArray<T> copy();
};


template<class T>
dynamicArray<T>::dynamicArray(int size)
{
    if (size <= 0) size = 1;

    array_size = 0;
    array_capacity = 1.5 * size;
    array = new T[array_capacity];
}

template<class T>
dynamicArray<T>::~dynamicArray()
{
    delete array;
    array = nullptr;
}

template<class T>
T dynamicArray<T>::operator[](int index) 
{ 
    if (index < 0) return 0;

    if (index >= size()) return 0; 

    return array[index]; 
}

template<class T>
dynamicArray<T>operator + (dynamicArray<T>& one, dynamicArray<T>& two)
{
    dynamicArray<T> result(one.size() + two.size());
    
    for (int index = 0; index < one.size(); ++index)
        result.push_back( one[index] );

    for (int index = 0; index < two.size(); ++index)
        result.push_back( two[index] );

    return result;
}


template<class T>
const int dynamicArray<T>::size() { return array_size; }

template<class T>
const int dynamicArray<T>::capacity() { return array_capacity; }

template<class T>
void dynamicArray<T>::push_back(T data)
{
    if (array_size >= array_capacity)
    {
        array_capacity *= 1.25;
        auto ptr = new T[array_capacity];
        for (int index = 0; index < array_size; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }

    array[array_size] = data;
    ++array_size;
}

template<class T>
void dynamicArray<T>::push_front(T data)
{
    if (array_size >= array_capacity)
    {
        array_capacity *= 2;
        auto ptr = new T[array_capacity];
        for (int index = 0; index < array_size; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }
    
    for (int index = array_size++; index > 0; --index)
        array[index] = array[index - 1];
    
    array[0] = data;
}

template<class T>
void dynamicArray<T>::pop_back()
{
    if (array_size == 0) return;
    --array_size;
}

template<class T>
void dynamicArray<T>::pop_front()
{
    if (array_size == 0) return;

    if (array_size == 1)
    {
        --array_size;
        return;
    }
    
    for (int index = 0; index < array_size; ++index)
        array[index] = array[index + 1];
    
    --array_size;
}

template<class T>
void dynamicArray<T>::insert(int pos, T data)
{
    if (pos < 0) return;

    if (pos >= array_size)
    {
        push_back(data);
        return;
    }

    if (pos == 0)
    {
        push_front(data);
        return;
    }
    
    if (array_size >= array_capacity)
    {
        array_capacity *= 2;
        auto ptr = new T[array_capacity];
        for (int index = 0; index < array_size; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }

    for (int index = array_size++; index > pos; --index)
        array[index] = array[index - 1];
    
    array[pos] = data;
}

template<class T>
void dynamicArray<T>::erase(int pos)
{
    if (pos < 0) return;

    if (pos >= array_size)
    {
        pop_back();
        return;
    }    

    if (pos == 0)
    {
        pop_front();
        return;
    }

    for (int index = pos; index < array_size; ++index)
        array[index] = array[index + 1];
    
    --array_size;
}

template<class T>
void dynamicArray<T>::clear() { while(array_size > 0) pop_back(); }

template<class T>
bool dynamicArray<T>::empty()
{
    if (array != nullptr && array_size > 0) return true; 
    return false;
}

template<class T>
void dynamicArray<T>::sort()
{
    if (array_size < 2) return;
    
    int half = array_size >> 1;
    T pivot = array[half];
    
    dynamicArray<T> left(half);
    dynamicArray<T> right(array_size - half);

    for (int i = 0; i < array_size; ++i)
    {
        if (pivot > array[i])
        {
            left.push_back(array[i]);
        } else {
            right.push_back(array[i]);
        }
    }
    
    left.sort();
    right.sort();
    
    for (int i = 0; i < (left + right).size(); ++i)
        array[i] = (left + right)[i];
   
    return; 
}

int main()
{
    using namespace std;

    dynamicArray<int> one(1);
    one.push_back(2);
    one.push_back(3);
    one.push_front(-2); // -2 2 3
    
    dynamicArray<int> two(5);
    two.push_back(83);
    two.pop_front();
    two.push_front(100);
    two.insert(1, 32);  // 100 32
    
    dynamicArray<int> array = one + two;  // -2 2 3 100 32
    array.sort();

    for (int index = 0; index < array.size(); ++index) cout << array[index] << " "; // should be -2 2 3 32 100
    cout << endl;

    cout << array.size() << " " << array.capacity() << " " << array[array.size() - 1]  << array.empty() << endl;  
    return 0;
}
