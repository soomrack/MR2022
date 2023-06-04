#include "dynamic_array.h"
#include <iostream>
int main() {
    DynArray a(1,6);

    a.fill_random(10);
    a.print();
    a.add(18, 3);
    a.resize(16,4);
    a.print();
    a.clean();
}
