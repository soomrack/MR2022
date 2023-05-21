#include "LIST.h"
#include <iostream>
int main() {
    try {
            List list;
            list.add_head(3);
            list.add_head(2);
            list.add_head(1);
            std::cout << "Head: " << list.get_head() << std::endl;
            list.print();
            list.del_head();
            list.del_head();
            list.del_head();
            list.del_head();
        } catch (const List_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

    return 0;
}
