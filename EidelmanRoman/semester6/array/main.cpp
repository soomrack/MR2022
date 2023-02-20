#include "array.h"


int main() {

    array myarr(5, 0);
    myarr.output();
    myarr.add(5);
    myarr.output();
    myarr.add(5, 3);
    myarr.output();

    return 0;
}