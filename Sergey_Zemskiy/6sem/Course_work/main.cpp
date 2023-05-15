#include <iostream>
#include "queue3.h"
#include <thread>
#include <ctime>


int main()
{
    const unsigned int N = 500000;
    Queue<unsigned int, N> l;
    //for (unsigned int count = 0; count < N / 2; count++) l.push(count);
    unsigned int start_time =  clock();
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
            if (g != count) std::cout << "error: count = " << count << " l.pop = " << g << '\n' ;
        }
    });
    push_thread.join();
    pop_thread.join();
    //for (unsigned int count = 0; count < N * 100; count++) l.push(count);
    //for (unsigned int count = 0; count < N * 100; count++) l.pop();
    unsigned int end_time = clock();
    std::cout <<"working time = " << end_time - start_time << " ms.";
    return 0;
}
