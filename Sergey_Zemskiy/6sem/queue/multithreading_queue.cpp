#include <iostream>
#include "queue3.h"
#include <thread>
#include <ctime>


int main()
{
    unsigned int start_time =  clock();
    const unsigned int N = 500000;
    Queue<unsigned int, N> l;
    /*std::thread push_thread([&] () {
        for (unsigned int count = 0; count < N; count++){
            l.push(rand() * 1000. + 13);
        }
    });
    std::thread pop_thread([&] () {
        for (unsigned int count = 0; count < N; count++){
            l.pop();
        }
    });
    push_thread.join();
    pop_thread.join();*/
    for (unsigned int count = 0; count < N; count++){
        l.push(rand() * 1000. + 13);
        l.pop();
    }
    unsigned int end_time = clock();
    std::cout <<"working time = " << end_time - start_time << " ms.";
    std::cout <<"start time = " << start_time << " ms.";

    /*Queue l2(l);
    Queue l3 = l;
    std::cout << l2[151] << std::endl; // for "private" testing, because operator[] isn't available for user
    std::cout << l3[151] << std::endl;
    l.pop();
    l.push( 2147483647);
    l.push(9992);
    std::cout << std::endl << l.pop() << std::endl;
    std::cout << l[0] << ' ' << l[1] << std::endl;*/


    //std::cout << "thread " << std::this_thread::get_id() << " main stopped" << std::endl;

    return 0;
}
