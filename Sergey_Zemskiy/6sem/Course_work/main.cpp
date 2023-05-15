#include <iostream>
#include "queue3.h"
#include <thread>



int main()
{
    const unsigned int N = 500000;
    Queue<unsigned int, N> l;
    std::thread push_thread([&] () {
        for (unsigned int count = 0; count < N * 1; count++){
            l.push(count);
        }
    });
    int g;
    std::thread pop_thread([&] () {
        for (unsigned int count = 0; count < N * 1; count++){
            //std::cout << l.pop() << " poped " << count << "\n";
            g = l.pop();
            if (g != count) {
                std::cout << "error: count = " << count << " l.pop = " << g << '\n' ;
                count--;
            }
        }
    });
    push_thread.join();
    pop_thread.join();
    return 0;
}
