#include <iostream>
#include "dual_linked_list.h"
template <typename T>
void print(LinkedList<T> &A)
{
    for (unsigned int i = 0; i < A.get_size(); i++){
    std:: cout << A[i] << " ";
    }
    std:: cout << std::endl;
}
int main()
{
    LinkedList<double> list;
    list.push_head(3);
    list.push_head(10);
    list.push_head(12);
    list.push_tail(11);
    print(list);
    list.remove(10);
    print(list);
    Node<double> *temp = list.get_node(4);
    list.insert(temp,5);
    print(list);
}