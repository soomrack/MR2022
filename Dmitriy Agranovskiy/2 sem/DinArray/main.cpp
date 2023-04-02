#include <iostream>
#include "dinamic_array.h"
#include <cmath>
using namespace std;

DinArray::DinArray(int v_size){
    DinArray::size = v_size;
    for (int i = 0; i < size; i++){
        DinArray::array[i] = 0;
    }
}

void DinArray::set(int num, int mean){
    DinArray::array[num - 1] = mean;
}

void DinArray::resize(int v_size){
    for (int i = DinArray::size - 1; i < v_size; i++){
        DinArray::size++;
        array[i] = 0;
    };
    DinArray::size--;
}

void DinArray::push_back(int mean){
    DinArray::size++;
    DinArray::array[size - 1] = mean;
};

void DinArray::pop_back(){
    DinArray::array[DinArray::size - 1] = 0;
    DinArray::size--;
};

void DinArray::output(){
    std::cout << DinArray::size << "\n";
    for(int i = 0; i < DinArray::size; i++ ){
        std::cout << DinArray::array[i];
    };
    std::cout << "\n";
}

int main() {
    DinArray A(10);
    A.output();

    A.set(1, 444);
    A.output();

    A.resize(20);
    A.output();

    A.push_back(7);
    A.output();

    A.pop_back();
    A.output();
    return 0;
}
