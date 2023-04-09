/*Был изменен конструктор и добавлен буфер в 2 элемента
 * была изменена функция для изменения размера массива
 * с учетом добавленных 2х элементов*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class DynArray {
private:
    unsigned int *array;
    unsigned int size;

public:
    DynArray(unsigned int item, unsigned int n);
    ~DynArray();

    void fill_random(int num);
    void add(int value, int idx);
    void remove(int idx);
    void print();
    void clean();
    void resize(unsigned int nsize);
    unsigned int get(unsigned int number);
    void set(unsigned int number, unsigned int item);
    unsigned int operator[] (unsigned int number);

};


DynArray::DynArray(unsigned int item, unsigned int n) {
    size = n + 2;
    array = new unsigned int [size];
    for (unsigned int number = 0; number < n; ++number) {
        array[number] = item;
    }
}


DynArray::~DynArray() {
    delete[] array;
    size = 0;
}


void DynArray::fill_random(int num) {
    cout << "Fill randomly" << "\n";
    srand(time(NULL));
    array = new unsigned int[num];
    for (int i = 0; i < num - 1; ++i) {
        array[i] = rand() % 100;
    }
    size = num;
}


void DynArray::add(int value, int idx) {
    cout << "Adding an " << value << " on place " << idx << "\n";
    unsigned int *temp = new unsigned int[size + 1];
    for (int i = 0; i < idx; ++i) {
        temp[i] = array[i];
    }
    temp[idx] = value;
    for (int i = idx; i < size; ++i) {
        temp[i + 1] = array[i];
    }
    delete array;
    array = temp;
    size++;
}


void DynArray::remove(int idx) {
    cout << "Remove element on place " << idx << "\n";
    unsigned int *temp = new unsigned int[size - 1];
    for (int i = 0; i < idx; ++i) {
        temp[i] = array[i];
    }
    for (int i = idx + 1; i < size; ++i) {
        temp[i - 1] = array[i];
    }
    delete array;
    array = temp;
    size--;
}


void DynArray::print() {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}


void DynArray::clean() {
    delete[] array;
    array = nullptr;
    size = NULL;
}


void DynArray::resize(unsigned int nsize) {
    if (nsize - size <= 2) {
        unsigned int *temp = array;
        size = nsize;
        array = new unsigned int [size];
        for (unsigned int number = 0; number < size; ++number) {
            array[number] = temp[number];
        }
        delete temp;
    } else {
        unsigned int *temp = array;
        size = nsize + 2;
        array = new unsigned int [size];
        for (unsigned int number = 0; number < nsize; ++number) {
            array[number] = temp[number];
        }
        delete temp;
    }
}


unsigned int DynArray::get(unsigned int number) {
    return array[number];
}


void DynArray::set(unsigned int number, unsigned int item) {
    array[number] = item;
}


unsigned int DynArray::operator[](unsigned int number) {
    return array[number];
}


int main() {
    DynArray DA(1,6);

    DA.fill_random(10);
    DA.print();

    DA.remove(5);
    DA.print();

    DA.add(18, 2);
    DA.print();

    DA.get(3);
    DA.set(1, 0);

    DA.resize(8);
    DA.print();

    DA.clean();
}