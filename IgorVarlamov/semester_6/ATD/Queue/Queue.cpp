#include <iostream>
#include "Queue.h"
template <typename T>
void print(Queue<T>& A) {
    if (A.is_empty()) throw std::domain_error("Queue is Empty");
    for (unsigned int i = 0; i < A.get_size(); i++){
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}
int main() {
    Queue<int> q(5);
    Queue<int> z(5);
    try {
        q.push(10);
        q.push(20);
        q.push(30);
        q.push(40);
        q.push(50);
        std::cout << "Print q: ";
        print(q);
        q.pop();
        q.pop();
        q.pop();
        q.pop();
        q.pop();
        q.push(3);
        q.push(7);
        std::cout << "Print q: ";
        print(q);
        std::cout << "Front element: " << q.get_top() << std::endl;
        std::cout << "Current_size:" << q.get_size() << std::endl;
    }
    catch (std::domain_error& e) {
        std::cerr << "Caught: " << e.what() << std::endl;
    }
    return 0;
}
