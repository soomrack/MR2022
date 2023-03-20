#include <iostream>
#include "typeinfo"
#include <math.h>
using namespace std;

const double COMP_CONST = pow(10, -4);

class Dyn_array {
protected:
    unsigned int size;
public:
    double* value;

    Dyn_array();
    Dyn_array(const unsigned int size);
    Dyn_array(const Dyn_array& dynArray);
    Dyn_array(Dyn_array&& dynArray);
    ~Dyn_array();

    Dyn_array& operator= (const Dyn_array& dynArray);

    void push_back (double item);
    void pop_back();
    void del (double item);
    void remove (double item);
    void clean();
    unsigned int contain (double item);

    void shrink (unsigned int newsize);
    void extend (unsigned int newsize);

    unsigned int length();
    void print();
};


Dyn_array::Dyn_array() {
    size = 0;
    value = nullptr;
}


Dyn_array::~Dyn_array() {
    delete[] value;
}


Dyn_array::Dyn_array(const unsigned int newsize) {
    size = newsize;
    value = new double [size];
}


Dyn_array::Dyn_array(const Dyn_array& dynArray) {
    size = dynArray.size;
    value = new double [size];
    for (unsigned int number = 0; number < dynArray.size; number++) {
        value[number] = dynArray.value[number];
    }
}


Dyn_array::Dyn_array(Dyn_array &&dynArray) {
    size = dynArray.size;
    value = dynArray.value;
    dynArray.size = 0;
    dynArray.value = nullptr;
}


Dyn_array &Dyn_array::operator= (const Dyn_array& dynArray) {
    if (this != &dynArray) {
        if (!value) delete[] value;
    size = dynArray.size;
    this->value = new double[size];
        for (unsigned int number = 0; number < size; number++) {
            value[number] = dynArray.value[number];
        }
    }
    return *this;
}


void Dyn_array::push_back(double item) {
    double* temp = new double[size + 1];
    for (unsigned int number = 0; number < size; number++) {
        temp[number] = value[number];
    }
    delete[] value;
    value = temp;
    value[size++] = item;
}


void Dyn_array::pop_back() {
    double* temp = new double [size--];
    for (unsigned int number = 0; number < size; number++) {
        temp[number] = value[number];
    }
    value = temp;
}


unsigned int Dyn_array::contain(double item) {
    for (unsigned int number = 0; number < size; number++) {
        if (abs(value[number] - item) < COMP_CONST) {
            return number + 1;
        }
    }
    return 0;
}


void Dyn_array::del(double item) {
    unsigned int pt = contain(item);
    if (pt) {
        value[pt - 1] = 0.0;
    }
}


void Dyn_array::remove(double item) {
    unsigned int pt = contain(item);
    if (pt == 0) return;
    double* temp = new double[size - 1];
    for (unsigned int number = 0; number < size; number++) {
        temp[number] = value[number];
    }
    for (unsigned int number = pt; number < size; number++) {
        temp[size - 1] = value[size];
    }
    value = temp;
    size--;
}


void Dyn_array::clean() {
    value = nullptr;
    size = 0;
}


void Dyn_array::shrink(unsigned int newsize) {
    if (newsize > size) return;
    double* temp = new double [newsize];
    for (unsigned int number = 0; number < size; number++) {
        temp[number] = value[number];
    }
    delete value;
    value = temp;
    size = newsize;
}


void Dyn_array::extend(unsigned int newsize) {
    if (newsize <= size) return;
    double* temp = new double [newsize];
    for (unsigned int number = 0; number < size; number++) {
        temp[number] = value[number];
    }
    delete[] value;
    value = temp;
    size = newsize;
}


unsigned int Dyn_array::length() {
    return size;
}


void Dyn_array::print() {
    cout << "Length: " << size << "\n";
    if (size > 0) {
        for (unsigned int number = 0; number < size; number++) {
            cout << value[number] << ' ';
        }
        cout << "\n";
    }
    cout << "\n";
}


int main() {
    Dyn_array D;
    D.value[0] = 1;
    D.push_back(2);
    D.value[5] = 3;

/*
    A.print();
*/
    D.print();

    D.remove(1);
    D.remove(2);
    D.remove(3);
    D.print();

    D.pop_back();
    D.extend(8);
    D.shrink(3);
    D.print();
    D.clean();
    D.print();
    return 0;
}
