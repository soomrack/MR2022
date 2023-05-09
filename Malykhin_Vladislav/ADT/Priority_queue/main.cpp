#include "Queue.h"


int main(){
    auto queue = new Queue();
    double filler_array1[] = {0, 1, 2, 3, 4, 5};
    double filler_array2[] = {13, 14, 15};
    int filler_priority[] = {0, 1, -1, 2, 0, 3, -3, 4, -4, 5, -5};
    int p_idx = 0;

    std::cout<<"push test\n";
    for( double val : filler_array1){
        queue->push(val, filler_priority[p_idx]);
        std::cout <<"pushing element:"<< val <<"  priority:"<< filler_priority[p_idx]<< "\n";
        ++p_idx;
    }
    std::cout<<"\n";
    queue->print();
    std::cout<<"\n";


    std::cout<<"pop test\n";
    for( int idx = 0; idx < 3; ++idx){
        std::cout << "popping element:" << queue->get() <<"  priority:"<<queue->prio()<<"\n";
        queue->pop();
    }
    std::cout<<"\n";
    queue->print();
    std::cout<<"\n";

    std::cout<<"push test\n";
    for( double val : filler_array2){
        queue->push(val, filler_priority[p_idx]);
        std::cout <<"pushing element:"<< val <<"  priority:"<< filler_priority[p_idx] << "\n";
        ++p_idx;
    }
    std::cout<<"\n";
    queue->print();
    std::cout<<"\n";

    std::cout<<"push test\n";
    for(int i = 0; i < 6; ++i){
        std::cout << "popping element:" << queue->get() <<"  priority:"<< queue->prio()<<"\n";
        queue->pop();
    }
    std::cout<<"\n";
    queue->print();
    std::cout<<"\n";

}
