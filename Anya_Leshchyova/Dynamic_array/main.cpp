#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <exception>

double E =0.00000001;

class Dynamic_array {
protected:
    unsigned int size;
    double* line;


public:

    Dynamic_array();
    Dynamic_array( const unsigned int number);
    Dynamic_array(const Dynamic_array& A);
    Dynamic_array(Dynamic_array&& A);
    ~Dynamic_array();



    void print();
    void searchAndReplace (double, double);
    void delet (double);
    void PushMove (double, int);
    bool search (double);


    Dynamic_array& operator=(const Dynamic_array &x);
};


Dynamic_array::Dynamic_array() {
    size = 0;
    line = nullptr;
}


Dynamic_array::Dynamic_array(const unsigned int number) {
    size = number;
    line = new double[size];
}


Dynamic_array& Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!line)
            delete[] line;
        size = x.size;
        this->line = new double[size];
        for (unsigned int number = 0; number < size; number++){
            line[number] = x.line[number];
        }
    }
    return *this;
}


Dynamic_array::Dynamic_array(const Dynamic_array& x) {
    size = x.size;
    line = new double[size];
    for (unsigned int number = 0; number < x.size; number++){
        line[number] = x.line[number];
    }
}


Dynamic_array::Dynamic_array(Dynamic_array &&x) {
    size = x.size;
    line = x.line;
    x.size = 0;
    x.line = nullptr;
}


Dynamic_array::~Dynamic_array() {
    delete[] line;
}


void Dynamic_array::PushMove(double X, int place) {
    if ( size == 0){
        line = new double [size + 1];
        line[size] = X;
        size++;
        return;
    }
    if ( place >= size) return;
    double* help = new double[size + 1];
    int t=0;
    for (unsigned int number = 0; number <= size  ; number ++){
        if ( number == place ){
            t=1;
            help[number] = X;
            continue;
        }
        help[number ] = line [number-t];
    }
    line = help;
    size++;
}


void Dynamic_array:: searchAndReplace (double search, double replace){
    for (unsigned int number = 0; number <= size  ; number ++){
        if ( abs( line[number] - search) < E ){
            line[number] = replace;
            return;
        }
    }
}


bool Dynamic_array:: search (double X){
    for (unsigned int number = 0; number <= size  ; number ++){
        if ( abs( line[number] - X) < E ){
            return false;
        }
    }
    return true;
}


void Dynamic_array:: delet (double X) {
    if (size == 0) return;
    if (search(X)) return;
    Dynamic_array help = {size - 1};
    int t=0;
    for (unsigned int number = 0; number < size  ; number ++){
        if ( abs(line[number] - X) < E){
            if (number == size -1) t-=1;
            t+=1;
        }
        help.line[number] = line [number+t];

    }
    line =help.line;
    size--;
}


void Dynamic_array::print (){
    for (unsigned int number = 0; number < size; number++){
        std::cout << line[number] << "  ";
    }
    std::cout << "\n";
}


int main() {
    Dynamic_array A;
    A.PushMove(1.90, 1);
    A.PushMove(2.032, 0);
    A.PushMove(6.011, 1);
    A.PushMove(34.05, 1);
    A.PushMove(7.04, 3);
    A.PushMove(98.06, 0);
    A.PushMove(4.08, 5);
    A.print();

    A.delet(1.90);
    A.delet(2.032);
    A.delet(6.011);
    A.print();

    A.searchAndReplace(98.06, 1.00);
    A.searchAndReplace(34.05, 2.00);
    A.searchAndReplace(7.04, 3.00);
    A.searchAndReplace(4.08, 4.00);
    A.print();

    A.delet(2.032);
    A.print();


    return 0;
}
