#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class DynArray {
private:
    int *array;
    int size;

public:
    DynArray();
    ~DynArray();

    void fill_random(int num);
    void add(int value, int idx);
    void remove(int idx);
    void print();
    void clean();
    void resize(int num);
    unsigned int get(unsigned int number);
    void set(unsigned int number, unsigned int item);
    unsigned int operator[] (unsigned int number);

};


DynArray::DynArray() {
    array = nullptr;
    size = NULL;
}


DynArray::~DynArray() {
    delete[] array;
    size = 0;
}


void DynArray::fill_random(int num) {
    cout << "Fill randomly" << "\n";
    srand(time(NULL));
    array = new int[num];
    for (int i = 0; i < num - 1; ++i) {
        array[i] = rand() % 100;
    }
    size = num;
}


void DynArray::add(int value, int idx) {
    cout << "Adding an " << value << " on place " << idx << "\n";
    int *temp = new int[size + 1];
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
    int *temp = new int[size - 1];
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
    cout << "\n";
}


void DynArray::clean() {
    delete[] array;
    array = nullptr;
    size = NULL;
}


void DynArray::resize(int num) {
    cout << "Size changed to " << num << "\n";
    int *temp = new int[num];
    int minSize = min(size, num);
    for (int i = 0; i < minSize; ++i) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    size = num;
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
    DynArray DA;

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