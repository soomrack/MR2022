#include <iostream>
#include <cmath>

const double COMPARATION_CONST = 0.0001;


class Dynamic_array{

protected:

    unsigned int size;

public:
    double* data;

    Dynamic_array();
    explicit Dynamic_array(unsigned int size);
    Dynamic_array(const Dynamic_array& x);
    ~Dynamic_array();

    Dynamic_array& operator=(const Dynamic_array& x);

    void push_back(double elm);
    void pop_back();
    unsigned int contain(double elm) const;  // возвращает позицию первого найденного элемента + 1;
    void del(double elm) const;
    void remove(double elm);
    void clear();

    void shrink(unsigned int size_);
    void extend(unsigned int size_);
    void change_size(unsigned int size_);

    unsigned int length() const;
    void output() const;

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


Dynamic_array::~Dynamic_array() {
    delete[] data;
}


Dynamic_array &Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!data) delete[] data;
        size = x.size;
        data = new double[size];
        for (unsigned int idx = 0; idx < size; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


void Dynamic_array::push_back(double elm) {
    //double temp[size + 1];
    auto* temp = new double[size + 1];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    data[size++] = elm;
}


void Dynamic_array::pop_back() {
    auto* temp = new double[--size];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    //delete[] data;
    data = temp;

}


unsigned int Dynamic_array::contain(double elm) const {
    for (unsigned int idx = 0; idx < size; idx++){
        if (fabs(data[idx] - elm) < COMPARATION_CONST){
            return idx + 1;
        }
    }
    return 0;
}


void Dynamic_array::del(double elm) const {
    unsigned int point = contain(elm);
    if (point){
        data[point - 1] = 0.0;
    }
}


void Dynamic_array::remove(double elm) {
    unsigned int point = contain(elm);
    if (point == 0) return;
    auto *temp = new double [size - 1];
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


void Dynamic_array::shrink(unsigned int size_) {
    if (size_ >= size) return;
    auto* temp = new double[size_];
    for (unsigned int idx = 0; idx < size_; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


void Dynamic_array::extend(unsigned int size_) {
    if (size_ <= size) return;
    auto* temp = new double[size_];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}

void Dynamic_array::change_size(unsigned int size_) {  // shrink + extend
    auto* temp = new double[size_];
    for (unsigned int idx = 0; idx < size_; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    size = size_;
}


unsigned int Dynamic_array::length() const {
    return size;
}


void Dynamic_array::output() const {
    std::cout << "Length: " << size << "\n";

    if (size > 0) {

        for (unsigned int idx = 0; idx < size; idx++) {
            if (fabs(data[idx]) > COMPARATION_CONST && fabs(data[idx]) < pow(10, 64))
                std::cout << data[idx] << " ";
            else
                std::cout << "0 ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


int main() {
    Dynamic_array A;
    Dynamic_array B(10);
    Dynamic_array C(B);

    B.data[0] = 11.7;
    B.push_back(-13);
    B.data[5] = 15;
    C.data[5] = 15;

    A.output();
    B.output();
    C.output();

    B.remove(11.7);
    B.remove(-13);
    B.remove(15);
    B.output();

    B.pop_back();
    B.extend(10);
    B.shrink(2);
    //B.change_size(100);
    B.output();
    //B.clear();


    //B.output();
    return 0;
}
