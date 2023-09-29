#include "queue.h"
using namespace :: std;
int main(){
    queue a(10);
    try {
    a.push(10);
    a.push(9);
    a.push(6);
    a.push(1);
    a.push(5);
    a.print();
    a.pop();
    a.pop();
    a.pop();
    a.print();
    cout << "Current_size:" << a.get_size() <<"\n";
    
    }
    catch (const queue_error& e) {
        std::cerr << e.what();
    }

}
