#include <iostream>

template<class T>
class dynamicArray
{
    private:
        T* array;
        int _size;
        int _capacity;
        T* tail;    
    
    public:
        dynamicArray(int size);
        ~dynamicArray();

        int size();
        int capacity();
       
        T operator[](int index); 
        

        void push_back(T data);
        void push_front(T data);
        void pop_back();
};

template<class T>
dynamicArray<T>::dynamicArray(int size)
{
    _size = size;
    _capacity = 2 * _size;
    array = new T[_capacity];
    tail = array;
}

template<class T>
dynamicArray<T>::~dynamicArray()
{
    delete array;
}

template<class T>
T dynamicArray<T>::operator[](int index) { return array[index]; }

template<class T>
int dynamicArray<T>::size() { return _size; }

template<class T>
int dynamicArray<T>::capacity() { return _capacity; }

template<class T>
void dynamicArray<T>::push_back(T data)
{
    *tail = data;
    ++_size;
}

template<class T>
void dynamicArray<T>::push_front(T data)
{
    
}

template<class T>
void dynamicArray<T>::pop_back()
{
    tail = &array[_size - 2];
    ++_size;
}


int main()
{
    dynamicArray<int> array(5);
    array.push_back(5);
    for (int index = 0; index < 5; ++index) std::cout << array[index] << " ";
    std::cout << std::endl;  

    return 0;
}
