#include <iostream>
#include "Graph.h"


int main() {

    Peak peak1(1);
    Peak peak2(2);
    Peak peak3(3);
    Peak peak4(4);

    std::cout<<peak1.getValue()<<"\n";
    std::cout<<peak1.getAddress()<<"\n";

    return 0;
}