#include <iostream>
#include "FSM.h"


void print8() {
    std::cout << "8" << std::endl;
}


void print9() {
    std::cout << "9" << std::endl;
}


int main() {

    FSM A;


    A.setState(print8);
    A.activeState();
    A.setState(print9);
    A.activeState();
    A.delState();
    A.activeState();

    return 0;
}
