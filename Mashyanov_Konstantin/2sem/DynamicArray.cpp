#include <iostream>
#include <cstdlib>


class DynamicArray {
private:
    int* array;  //  Указатель на начало массива
    int size;  

public:
    DynamicArray();
    ~DynamicArray();
    void add(int value, int index);
    void fill_random(int n);
    void remove(int index);
    void print();
    void resize(int n);
    void clear();
};
DynamicArray::DynamicArray() {
        array = nullptr;
        size = 0;
    }

DynamicArray::~DynamicArray() {
        delete[] array;
    }

    void DynamicArray::fill_random(int n) {
        srand(time(nullptr));  //  Генерация рандомных чисел для массива
        array = new int[n];  //  Создаем массив нужной длины
        for (int i = 0; i < n-1; i++) {
            array[i] = rand() % 10;
        }
        
        size = n;
    }

    void DynamicArray::add(int value, int index) {
        int* temp = new int[size + 1];  
        for (int i = 0; i < index; i++) {
            temp[i] = array[i];  //  Копируем элементы до индекса
        }
        temp[index] = value;  //  Вставляем новый элемент
        for (int i = index; i < size; i++) {
            temp[i + 1] = array[i];  
        }
        delete[] array;
        array = temp;
        size++;
    }

    void DynamicArray::remove(int index) {
        int* temp = new int[size - 1];  
        for (int i = 0; i < index; i++) {
            temp[i] = array[i];  
        }
        for (int i = index + 1; i < size; i++) {
            temp[i - 1] = array[i]; 
        }
        delete[] array;
        array = temp;
        size--;
    }

    void DynamicArray::print() {
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    void DynamicArray::resize(int n) {
        int* temp = new int[n];  //  Создаем временный массив нужной длины
        int min_size = (size < n) ? size : n;  //  Определяем минимальный размер для копирования
        for (int i = 0; i < min_size; i++) {
            temp[i] = array[i];  //  Копируем элементы из текущего массива во временный
        }
        delete[] array;
        array = temp;
        size = n;
    }

    void DynamicArray::clear() {
        delete[] array;
        array = nullptr;
        size = 0;
    }

int main() {
    DynamicArray array;
    array.fill_random(5);
    array.print();

    array.add(29, 3);
    array.print();

    array.remove(2);
    array.print();

    array.resize(4);
    array.print();

    array.clear();

    return 0;
}
