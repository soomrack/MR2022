#include "dynamic_array.h"
#include <iostream>
int main() {
    DynArray DA(1,6);

    DA.fill_random(10);
    DA.print();

    DA.remove(5);
    DA.print();

    DA.add(18, 2);
    DA.print();

    DA.get(3);
    DA.set(1, 1);

    DA.resize(8, 5);
    DA.print();

    DA.clean();
}
