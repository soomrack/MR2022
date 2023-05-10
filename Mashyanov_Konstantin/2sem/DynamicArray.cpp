#include <iostream>
using namespace std;

class DynamicArray {
private:
    int *data; // Массив элементов
    int size;  // Текущий размер массива
    int capacity; // Максимальная вместимость массива

public:
   
    DynamicArray();
    DynamicArray(int capacity);
    ~DynamicArray();

    // Методы для доступа к элементам
    int get(int index);  // Получение элемента по индексу
    void set(int index, int value); // Изменение элемента по индексу 
    void add(int value);  // Добавление элемента в конец массива

    void resize(int new_capacity);  // Изменение размера массива
    int get_capacity();  // Возвращает максимальную вместимость массива
    int get_size();  // Возвращает текущий размер массива
};

DynamicArray::DynamicArray() {
    capacity = 8;
    size = 0;
    data = new int[capacity];
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
        resize(capacity * 2);
    }
    data[size++] = value;
}

void DynamicArray::resize(int new_capacity) {
    int *new_data = new int[new_capacity];
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

int main() {
    DynamicArray arr(4);

    arr.add(1);
    arr.add(2);
    arr.add(3);
    arr.add(4);

    std::cout << "Size: " << arr.get_size() << std::endl;
    std::cout << "Capacity: " << arr.get_capacity() << std::endl;

    arr.set(1, 5);

    std::cout << "Element at index 1: " << arr.get(1) << std::endl;

    arr.resize(6);

    arr.add(6);
    arr.add(7);

    std::cout << "Size: " << arr.get_size() << std::endl;
    std::cout << "Capacity: " << arr.get_capacity() << endl;
    
     return 0;
}
