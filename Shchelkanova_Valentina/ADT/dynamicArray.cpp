#include <iostream>
#include <cstdlib>
#include <ctime>

class DynamicArray {
private:
    int *arr; // указатель на начало массива
    int size; // текущий размер массива

public:
    DynamicArray();

    ~DynamicArray();

    void add(int value, int index);

    void fillRandom(int n);

    void remove(int index);

    void print();

    void resize(int n);

    void clear();
};
DynamicArray::DynamicArray() {
        arr = nullptr;
        size = 0;
    }

DynamicArray::~DynamicArray() {
        delete[] arr;
    }

    void DynamicArray::fillRandom(int n) {
        srand(time(nullptr));
        arr = new int[n]; // создаем массив нужной длины

        for (int i = 0; i < n-3; i++) {
            arr[i] = rand() % 100;
        }

        size = n;
    }

    void DynamicArray::add(int value, int index) {
        int* temp = new int[size + 1]; // создаем временный массив на один элемент больше
        for (int i = 0; i < index; i++) {
            temp[i] = arr[i]; // копируем элементы до индекса
        }
        temp[index] = value; // вставляем новый элемент
        for (int i = index; i < size; i++) {
            temp[i + 1] = arr[i]; // копируем элементы после индекса
        }
        delete[] arr;
        arr = temp;
        size++;
    }

    void DynamicArray::remove(int index) {
        int* temp = new int[size - 1]; // создаем временный массив на один элемент меньше
        for (int i = 0; i < index; i++) {
            temp[i] = arr[i]; // копируем элементы до индекса
        }
        for (int i = index + 1; i < size; i++) {
            temp[i - 1] = arr[i]; // копируем элементы после индекса
        }
        delete[] arr;
        arr = temp;
        size--;
    }

    void DynamicArray::print() {
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void DynamicArray::resize(int n) {
        int* temp = new int[n]; // создаем временный массив нужной длины
        int minSize = (size < n) ? size : n; // определяем минимальный размер для копирования
        for (int i = 0; i < minSize; i++) {
            temp[i] = arr[i]; // копируем элементы из текущего массива во временный
        }
        delete[] arr;
        arr = temp;
        size = n;
    }

    void DynamicArray::clear() {
        delete[] arr;
        arr = nullptr;
        size = 0;
    }

int main() {
    DynamicArray arr;
    arr.fillRandom(10);
    arr.print();

    arr.add(42, 5);
    arr.print();

    arr.remove(3);
    arr.print();

    arr.resize(6);
    arr.print();

    arr.clear();

    return 0;
}