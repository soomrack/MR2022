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
    try {
        List<double> list;
        list.push_back(0);
        list.push_back(10);
        list.push_back(30);
        list.push_back(22);
        print(list);
        std::cout << "Pop_back and resize ";
        list.resize(7);
        std::cout<<"GET SIZE" << list.get_size();
        list.pop_back();
        print(list);
        std::cout << "Push_back ";
        list.push_back(7);
        print(list);
        std::cout << "Push_front ";
        list.push_front(3);
        print(list);
        std::cout << "Insert ";
        list.advance(list, 2);
        list.insert(list, 12);
        print(list);
        list.advance(list, 3);
        std::cout << "Remove ";
        list.remove(list);
        print(list);
        list.pop_front();
        std::cout << "Pop_front ";
        print(list);
    }

    catch (LIST_ERROR &e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}
