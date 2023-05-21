#include "queue.h"
using namespace :: std;
int main(){
    queue a;
    try {
    a.push(10,1);
    a.push(9,2);
    a.push(6,1);
    a.push(1,6);
    a.push(5,2);
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
