#include <iostream>
using namespace std;

#define COMPARATION_CONST 0.0001

class Dynamic_array{
protected:
    unsigned int size;

public:
    double* data;

    Dynamic_array();
    Dynamic_array(const unsigned int size_);
    Dynamic_array(const Dynamic_array &x);
    Dynamic_array(Dynamic_array &&x);
    ~Dynamic_array();

    Dynamic_array& operator=(const Dynamic_array& x);

    void push_back(double el);
    void pop_back();
    unsigned int contain(double el);
    void del(double el);
    void remove(double el);
    void clear();

    void shrink(unsigned int size_ch);
    void expand(unsigned int size_ch);

    unsigned int length();
    void output();

};


Dynamic_array::Dynamic_array(){
    size = 0;
    data = nullptr;
}

Dynamic_array::Dynamic_array(const unsigned int size_){
    size = size_;
    data = new double[size];
}

Dynamic_array::Dynamic_array(const Dynamic_array &x){
    size = x.size;
    data = new double[size];

    for(unsigned int el = 0;el < size;el++){
        data[el] = x.data[el];
    }
}

Dynamic_array::Dynamic_array(Dynamic_array &&x){
    size = x.size;
    data = x.data;

    x.size = NULL;
    x.data = nullptr;
}

Dynamic_array::~Dynamic_array(){
    delete[] data;
    data = nullptr;
    size = NULL;
}

Dynamic_array &Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!data) delete[] data;

        size = x.size;
        data = new double [size];
        for(unsigned int el = 0;el < size; el++){
            data[el] = x.data[el];
        }
    }
    return *this;
}

void Dynamic_array::push_back(double el) {
    double *temp = new double[size + 1];
    for(unsigned int elm = 0;elm < size; elm++){
        temp[elm] = data[elm];
    }

    delete[] data;
    temp[size++] = el;
    data = temp;
    temp = nullptr;
}

void Dynamic_array::pop_back() {
    double *temp = new double[size - 1];
    for(unsigned int el = 0;el < size--; el++){
        temp[el] = data[el];
    }

    delete[] data;
    data = temp;
    temp = nullptr;
}

unsigned int Dynamic_array::contain(double el) {
    for(unsigned int elm = 0;elm < size; elm++){
        if (abs(data[elm] - el) < COMPARATION_CONST){
            return elm + 1;
        }
    }
    return 0;
}

void Dynamic_array::del(double el) {
    unsigned int pointer = contain(el);
    if (pointer){
        data[pointer - 1] = 0.0;
    }
}

void Dynamic_array::remove(double el) {
    unsigned int pointer = contain(el);
    if (pointer == 0) return;

    double *temp = new double[size - 1];

    for(unsigned int elm = 0;elm < pointer - 1; elm++){
        temp[elm] = data[elm];
    }
    for(unsigned int elm = pointer;elm < size; elm++){
        temp[elm - 1] = data[elm];
    }

    delete[] data;
    data = temp;
    temp = nullptr;
    size--;
}

void Dynamic_array::clear() {
    delete[] data;
    data = nullptr;
    size = NULL;
}

void Dynamic_array::shrink(unsigned int size_ch) {
    if (size_ch >= size) return;
    double *temp = new double[size_ch];
    for(unsigned int el = 0;el < size_ch; el++){
        temp[el] = data[el];
    }

    delete[] data;
    data = temp;
    size = size_ch;
    temp = nullptr;
}

void Dynamic_array::expand(unsigned int size_ch) {
    if (size_ch <= size) return;
    double *temp = new double[size_ch];
    for(unsigned int el = 0;el < size; el++){
        temp[el] = data[el];
    }

    delete[] data;
    data = temp;
    size = size_ch;
    temp = nullptr;
}

unsigned int Dynamic_array::length(){
    return size;
}

void Dynamic_array::output() {
    cout << "Length is: "<< size << endl;

    if (size > 0){
        for(unsigned int el = 0;el < size;el++){
            cout << data[el] << endl;
        }

        cout << "\n";
        cout << "\n";
    }

}

int main() {
    Dynamic_array A;
    Dynamic_array B(10);

    for(unsigned int el = 0;el < 10;el++){
        B.data[el] = rand() % 50;
    }

    B.data[0] = 11.1;
    B.push_back(15.1);
    B.data[3] = 7.7;

    A.output();
    B.output();

    B.remove(11.1);
    B.remove(15.1);
    B.remove(7.7);
    B.output();

    B.pop_back();
    B.expand(10);
    B.shrink(9);
    B.output();

    B.clear();
    B.output();
    return 0;
}
