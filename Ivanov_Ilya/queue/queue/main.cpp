#include "queue.h"
using namespace :: std;
int main(){
    queue a;
    try {
    a.push(10);
    a.push(9);
    a.push(6);
    a.print();
    a.pop();
    a.print();
    cout << "Current_size:" << a.get_size() <<"\n";
    
    }
    catch (const queue_error& e) {
        std::cerr << e.what();
    }

}
