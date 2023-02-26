#include <iostream>

template<class T>
class dynamicArray
{
    private:
        T* array;
        int size_;
        int capacity_;
    public:
        dynamicArray(int size);
        ~dynamicArray();

        int size();
        int capacity();

        T operator[](int index);
        
        void push_back(T data);
        void push_front(T data);
        void pop_back();
        void pop_front();
        void insert(int pos, T data);
        void erase(int pos);
        void clear();
};

template<class T>
dynamicArray<T>::dynamicArray(int size)
{
    if (size <= 0) size = 1;

    size_ = 0;
    capacity_ = 2 * size;
    array = new T[capacity_];
}

template<class T>
dynamicArray<T>::~dynamicArray()
{
    delete array;
}

template<class T>
T dynamicArray<T>::operator[](int index) 
{ 
    if (index < 0) return 0;

    if (index >= size()) return 0; 

    return array[index]; 
}

template<class T>
int dynamicArray<T>::size() { return size_; }

template<class T>
int dynamicArray<T>::capacity() { return capacity_; }

template<class T>
void dynamicArray<T>::push_back(T data)
{
    if (size_ >= capacity_)
    {
        capacity_ *= 2;
        auto ptr = new T[capacity_];
        for (int index = 0; index < size_; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }

    array[size_] = data;
    ++size_;
}

template<class T>
void dynamicArray<T>::push_front(T data)
{
    if (size_ >= capacity_)
    {
        capacity_ *= 2;
        auto ptr = new T[capacity_];
        for (int index = 0; index < size_; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }
    
    for (int index = size_++; index > 0; --index)
        array[index] = array[index - 1];
    
    array[0] = data;
}

template<class T>
void dynamicArray<T>::pop_back()
{
    if (size_ == 0) return;
    --size_;
}

template<class T>
void dynamicArray<T>::pop_front()
{
    if (size_ == 0) return;

    if (size_ == 1)
    {
        --size_;
        return;
    }
    
    for (int index = 0; index < size_; ++index)
        array[index] = array[index + 1];
    
    --size_;
}

template<class T>
void dynamicArray<T>::insert(int pos, T data)
{
    if (pos < 0) return;

    if (pos >= size_)
    {
        push_back(data);
        return;
    }

    if (pos == 0)
    {
        push_front(data);
        return;
    }
    
    if (size_ >= capacity_)
    {
        capacity_ *= 2;
        auto ptr = new T[capacity_];
        for (int index = 0; index < size_; ++index)
            ptr[index] = array[index];
        delete array;
        array = ptr;
    }

    for (int index = size_++; index > pos; --index)
        array[index] = array[index - 1];
    
    array[pos] = data;
}

template<class T>
void dynamicArray<T>::erase(int pos)
{
    if (pos < 0) return;

    if (pos >= size_)
    {
        pop_back();
        return;
    }    

    if (pos == 0)
    {
        pop_front();
        return;
    }

    for (int index = pos; index < size_; ++index)
        array[index] = array[index + 1];
    
    --size_;
}

template<class T>
void dynamicArray<T>::clear() { while(size_ > 0) pop_back(); }



int main()
{
    using namespace std;

    dynamicArray<int> array(1);
    array.push_back(2);
    array.push_back(32);
    array.push_front(-2);
    array.pop_back();
    array.push_back(83);
    array.pop_front();
    array.push_front(100);
    array.insert(1, 322);
    array.erase(2);

    for (int index = 0; index < array.size(); ++index) cout << array[index] << " "; // should be 100 322 83
    cout << endl;

    cout << array.size() << " " << array.capacity() << " " << array[array.size() - 1] << endl;  
    return 0;
}

