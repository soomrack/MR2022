#include <iostream>
#include "queue.h"
template <typename T>
void print(queue<T>& A) {
    if (A.is_empty()) throw std::domain_error("queue is Empty");
    for (unsigned int i = 0; i < A.get_size(); i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    queue<int> q(5);
    queue<int> z(5);
    try {
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);
        z.push(30);
        z.push(20);
        z.push(1000);
        z.push(21);
        z.push(52);
        std::cout << "Front element: " << q.get_top() << std::endl;
        std::cout << "Current_size:" << q.get_size() << std::endl;
        std::cout << "Print q: ";
        print(q);
        std::cout << "Print z: ";
        print(z);
        std::cout << "Print q:";
        print(q);
        queue<int>ab(std::move(q));
        print(ab);
    }
    catch (std::domain_error& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    return 0;
}
