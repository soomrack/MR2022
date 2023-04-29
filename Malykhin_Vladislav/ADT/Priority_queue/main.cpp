#include "Queue.h"


int main(){
    auto queue = new Queue();
    double filler_array1[] = {0, 1, 2, 3, 4, 5};
    double filler_array2[] = {13, 14, 15};
    int filler_priority[] = {0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
    int p_idx = 0;

    std::cout<<"push test\n";
    for( double val : filler_array1){
        queue->push(val, filler_priority[p_idx]);
        std::cout <<"добавление элемента:"<< val <<"  приоритет:"<< filler_priority[p_idx]<< "\n";
        ++p_idx;
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
        queue->push(val, filler_priority[p_idx]);
        std::cout <<"добавление элемента:"<< val <<"  приоритет:"<< filler_priority[p_idx] << "\n";
        ++p_idx;
    }
    std::cout<<"\n";

    std::cout<<"push test\n";
    for(int i = 0; i < 6; ++i){
        std::cout << "удаление элемента:" << queue->get() <<"\n";
        queue->pop();
    }
    std::cout<<"\n";

}
