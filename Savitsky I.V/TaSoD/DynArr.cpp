#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data; 
    int size;  
    int capacity; 

public:

    DynamicArray();
    DynamicArray(int capacity);
    ~DynamicArray();

    
    int get(int index);  
    void set(int index, int value);
    void add(int value); 

    void expand(int new_capacity);  
    int get_capacity();  
    int get_size();  
};

DynamicArray::DynamicArray() {
    size = 0;
    data = nullptr;
    capacity=0;
}

DynamicArray::DynamicArray(int initial_capacity) {
    capacity = initial_capacity;
    size = 0;
    data = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

int DynamicArray::get(int index) {
    return data[index];
}

void DynamicArray::set(int index, int value) {
    data[index] = value;
}


void DynamicArray::add(int value) {
    if (size == capacity) {
        expand(capacity + 1);
    }
    data[size++] = value;
}

void DynamicArray::expand(int new_capacity) {
    int* new_data = new int[new_capacity];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}


int DynamicArray::get_size() {
    return size;
}


int DynamicArray::get_capacity() {
    return capacity;
}

void main(){

DynamicArray arr(0);

arr.add(5);
arr.add(2);
arr.add(8);
arr.add(0);

std::cout << "Size: " << arr.get_size() << std::endl;
std::cout << "Capacity: " << arr.get_capacity() << std::endl;

arr.set(1, 20);

std::cout << "Element at index 1: " << arr.get(1) << std::endl;


arr.add(6);
arr.add(7);

std::cout << "Size: " << arr.get_size() << std::endl;
std::cout << "Capacity: " << arr.get_capacity() << endl;
}