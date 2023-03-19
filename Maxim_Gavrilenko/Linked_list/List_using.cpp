#include <iostream>
#include "Linked_list.h"
template <typename T>
void print(List<T>& A)
{
    for(int i = 0; i < A.get_size(); i++)
    {
        std::cout << A[i] << " ";
    }
    std:: cout << std:: endl;
}

int main () {
    List<double> list;
    list.push_back(0);
    list.push_back(10);
    list.push_back(30);
    list.push_back(22);
    print(list);
    std:: cout << "Pop_back";
    list.pop_back();
    list.push_back(7);
    print(list);
    std:: cout << "Push_front";
    list.push_front(3);
    print(list);
    std:: cout << "Insert";
    list.insert(12,2);
    print(list);
    std:: cout << "Remove";
    list.remove(3);
    print(list);
    std:: cout << "Push_back";
    print(list);
    list.pop_front();
    std:: cout << "Pop_front";
    print(list);
    return 0;
}
