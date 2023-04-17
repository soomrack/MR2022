#include <iostream>
#include <cmath>
#include "FSM.h"


const double K = 2;


double k(double u) {
    return K * u;
}


double tg(double u) {
    return tan(u);
}


int main() {

    FSM A;
    A.setState(k);

    std::cout << A.activeState(5);

    return 0;
}
