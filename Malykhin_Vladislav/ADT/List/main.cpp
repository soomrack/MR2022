#include "List.h"


int main(){
    List new_list;
    new_list.push_head(1);
    new_list.print();

    List::Iterator iter = new_list.head;
    new_list.push(2, ++iter);
    new_list.print();

    new_list.push(3, ++iter);
    new_list.print();

    new_list.push(4, ++iter);
    new_list.print();

    List::Iterator new_iter = new_list.head;
    for(int a = 0; a < 3; a++)
        ++new_iter;
    new_list.pop(new_iter);
    new_list.print();

    new_list.pop_head();
    new_list.print();
}
