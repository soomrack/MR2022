#include "Array.h"


int main() {

    Array myarr(5, 0);
    myarr.output();
    myarr.add(5);
    myarr.output();
    myarr.add(5, 4);
    myarr.output();
    myarr.rm();
    myarr.output();
    myarr.rm(5);
    myarr.output();

    return 0;
}