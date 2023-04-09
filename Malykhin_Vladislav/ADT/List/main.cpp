#include "List.h"


int main(){
    List new_list;
    std::cout<<"Size:"<<new_list.size()<<"\n\n";
    new_list.push_head(1);
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";

    List::Iterator iter = new_list.head;
    new_list.push(2, iter);
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";

    new_list.push(3, ++iter);
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";

    new_list.push(4, ++iter);
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";

    List::Iterator new_iter = new_list.head;
    for(int a = 0; a < 2; a++)
        ++new_iter;
    new_list.pop(new_iter);
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";

    new_list.pop_head();
    new_list.print();
    std::cout<<"Size:"<<new_list.size()<<"\n\n";
}
