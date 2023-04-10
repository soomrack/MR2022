#include "Queue.h"


int main(){
    auto queue = new Queue();
    double filler_array1[] = {0, 1, 2, 3, 4, 5};
    double filler_array2[] = {13, 14, 15};


    std::cout<<"push test\n";
    for( double val : filler_array1){
        queue->push(val);
        std::cout <<"добавление элемента:"<< val <<"\n";
    }
    std::cout<<"\n";


    std::cout<<"pop test\n";
    for( int idx = 0; idx < 3; ++idx){
        std::cout << "удаление элемента:" << queue->get() <<"\n";
        queue->pop();
    }
    std::cout<<"\n";


    std::cout<<"push test\n";
    for( double val : filler_array2){
        queue->push(val);
        std::cout <<"добавление элемента:"<< val <<"\n";
    }
    std::cout<<"\n";

    std::cout<<"push test\n";
    for( double val : filler_array1){
        std::cout << "удаление элемента:" << queue->get() <<"\n";
        queue->pop();
    }
    std::cout<<"\n";

}
