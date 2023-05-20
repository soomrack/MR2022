#include "stack.h"
int main(){
    stack a;
    try {
    a.push (3);
    a.push (4);
    a.push (4);
    a.push (4);
    a.push (4);
    a.pop ();
    a.print();
    a.~stack ();
    a.push (1);
    a.print();
    std::cout << "Current_size:" << a.get_size() <<"\n";
    a.pop();
    a.pop();
   }
    catch (const stack_error& e) {
        std::cerr << e.what();
    }

}
