#include "DArrayTest.h"

int main(){
    std::cout<<"Test of int type//////////////////////////////////////////////////////////////////////////////////\n";
    DArrayTest<int>::full_test();
    std::cout<<"Test of float type//////////////////////////////////////////////////////////////////////////////////\n";
    DArrayTest<float>::full_test();
    std::cout<<"Test of double type/////////////////////////////////////////////////////////////////////////////////\n";
    DArrayTest<double>::full_test();
    return 0;
}