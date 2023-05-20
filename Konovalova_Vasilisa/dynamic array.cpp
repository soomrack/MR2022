#include <iostream>
using namespace std;

class DynamicArray {
private:
    int *data;
    int size;
    int capacity;

public:

    DynamicArray();
    DynamicArray(int capacity);
    ~DynamicArray();

    int get(int index);
    void set(int index, int value);
    void add(int value);

    void resize(int new_size);

};

DynamicArray::DynamicArray() {
    capacity = 5;
    size = 0;
    data = new int[capacity];
}

DynamicArray::DynamicArray(int start_capacity) {
    capacity = start_capacity;
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
        resize(capacity + 5);
    }
    data[size++] = value;
}

void DynamicArray::resize(int new_size) {
    int *new_data = new int[new_size];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_size;
}


int main() {
    DynamicArray arr(3);
    arr.set(2, 5);
    std::cout << "Second element: " << arr.get(2) << std::endl;

    arr.add(22);
    arr.add(3);
    arr.add(128);

    arr.resize(5);

    arr.add(33);
    arr.add(28);


    return 0;
}