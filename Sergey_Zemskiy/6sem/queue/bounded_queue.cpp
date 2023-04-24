#include <iostream>
#include "queue_lock_free.h"
#include <thread>



int main()
{
    std::cout << "thread " << std::this_thread::get_id() << " main started" << std::endl;
    const unsigned int N = 500;
    Queue<int, N> l;

    std::thread push_thread([&] () {
        std::cout << "thread " << std::this_thread::get_id() << " push started" << std::endl;
        for (int count = 0; count < N; count++){
            l.push(count + 1);
        }
        std::cout << "thread " << std::this_thread::get_id() << " push stopped" << std::endl;

    });


    std::thread pop_thread([&] () {
        std::cout << "thread " << std::this_thread::get_id() << " pop started" << std::endl;
        for (int count = 0; count < N/2; count++){
            l.pop();
        }
        std::cout << "thread " << std::this_thread::get_id() << " pop stopped" << std::endl;
    });

    Queue l2(l);
    Queue l3 = l;

    push_thread.join();
    pop_thread.join();
    std::cout << l[N/2 + 10];
    std::cout << l[N/2 - 10];
    //l.print();
    /*int proba = 10;
    int* pointer = &proba;
    (*pointer)++;
    delete (&proba);
    std::cout << proba  ;*/
    std::cout << "thread " << std::this_thread::get_id() << " main stopped" << std::endl;


    return 0;
}
