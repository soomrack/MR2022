#include "dynamic_array.h"
#include <iostream>
int main() {
    DynArray a(1,6);

    a.fill_random(10);
    a.print();
    a.add(18, 3);
    a.resize(8);
    a.print();
    a.clean();
}
