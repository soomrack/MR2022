#include <iostream>
#include "typeinfo"

const double COMPARATION_CONST = 0.0001;


class Dynamic_array{

protected:

    unsigned int size;

public:
    double* data;

    Dynamic_array();
    Dynamic_array(const unsigned int size);
    Dynamic_array(const Dynamic_array& x);
    Dynamic_array(Dynamic_array&& x);
    ~Dynamic_array();

    Dynamic_array& operator=(const Dynamic_array& x);
    friend std::ostream& operator<<(std::ostream& out, const Dynamic_array& x);

    void push_back(double elm);
    void pop_back();
    unsigned int contain(double elm);  // возвращает позицию первого найденного элемента + 1;
    void del(double elm);
    void remove(double elm);
    void clear();

    void shrink(unsigned int size_);
    void extend(unsigned int size_);

    unsigned int length();
    void output();

};


Dynamic_array::Dynamic_array() {
    size = 0;
    data = nullptr;

}


Dynamic_array::Dynamic_array(const unsigned int size_) {
    size = size_;
    data = new double[size];

}


Dynamic_array::Dynamic_array(const Dynamic_array& x) {
    size = x.size;

    data = new double[size];

    for (unsigned int idx = 0; idx < x.size; idx++){
        data[idx] = x.data[idx];
    }
}


Dynamic_array::Dynamic_array(Dynamic_array &&x) {
    size = x.size;
    data = x.data;

    x.size = 0;
    x.data = nullptr;
}


Dynamic_array::~Dynamic_array() {
    delete[] data;
}


Dynamic_array &Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        size = x.size;

        this->data = new double[size];
        for (unsigned int idx = 0; idx < size; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


std::ostream& operator<<(std::ostream& out, const Dynamic_array& x){

    for (unsigned int idx = 0; idx < x.size; idx++){
        out << x.data[idx] << " ";
    }
    out << "\n";
    return(out);
}


void Dynamic_array::push_back(double elm) {
    //double temp[size + 1];
    double* temp = new double[size + 1];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    data[size++] = elm;
}


void Dynamic_array::pop_back() {
    // удаление последнего элемента и уменьшение размера массива на 1?;
    //double temp[size + 1];
    double* temp = new double[--size];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    //delete[] data;
    data = temp;

}


unsigned int Dynamic_array::contain(double elm) {
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(data[idx] - elm) < COMPARATION_CONST){
            return idx + 1;
        }
    }
    return 0;
}


void Dynamic_array::del(double elm) {
    unsigned int point = contain(elm);
    if (point){
        data[point - 1] = 0.0;
    }
}


void Dynamic_array::remove(double elm) {
    unsigned int point = contain(elm);
    if (point == 0) return;
    double *temp = new double [size - 1];
    for (unsigned int idx = 0; idx < point - 1; idx++){
        temp[idx] = data[idx];
    }
    for (unsigned int idx = point; idx < size; idx++){
        temp[idx - 1] = data[idx];
    }
    //delete[] data;
    data = temp;
    size--;
}


void Dynamic_array::clear() {
    data = nullptr;
    size = 0;
}


void Dynamic_array::shrink(unsigned int size_) {  // shrink & extend можно обобщить
    if (size_ >= size) return;
    double* temp = new double[size_];
    for (unsigned int idx = 0; idx < size_; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


void Dynamic_array::extend(unsigned int size_) {
    if (size_ <= size) return;
    double* temp = new double[size_];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


unsigned int Dynamic_array::length(){
    return size;
}


void Dynamic_array::output() {
    std::cout << "Length: " << size << "\n";

    if (size > 0) {

        for (unsigned int idx = 0; idx < size; idx++) {
            std::cout << data[idx] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


int main() {
    Dynamic_array A;
    Dynamic_array B(10);

    B.data[0] = 11.1;
    B.push_back(13.2);
    B.data[5] = 15.9;

    A.output();
    B.output();
    
    B.remove(11.1);
    B.remove(15.9);
    B.remove(13.2);
    B.output();

    B.pop_back();
    B.extend(10);
    B.shrink(2);
    B.output();
    B.clear();

    // как реализовать B = {1.2, 3.4, 5.6, 7.8}; ??
    B.output();
    return 0;
}
