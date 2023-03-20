#include <iostream>

class ATD_exc: public std::exception{
public:
    ATD_exc(const char* message): std::exception(){

    }

};

#include "list.h"
#include "stack.h"
#include "dynamic_array.h"

#define DEBUG

// enum: psstate #TODO
// git token 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


void sep(const char* massege= "")
{
    std::cout << "----------------------------" << massege << "----------------------------\n";
}

void test_lits(bool test_visible = true)
{
    list<int> lst1;
    lst1[1];

    lst1.push_back(10);
    lst1.push_back(5);
    lst1.push_back(42);

    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;

    lst1.removeEl(0);
    sep("pop_back");
    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;


    list<int> lst2(lst1);
    sep("list_2");
    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;

    if (lst1 == lst2)
        std::cout << "equal" << std::endl;
}

void delay(){ int a; for (int i = 0; i < 1000000000; i++) {a = i;}}

void test_dynamic_array()
{
    dynamic_array DA1(10);
    dynamic_array DA2(10);
    DA1.fill_random();
#ifndef DEBUG
    delay();
#endif
    DA2.fill_random();
    DA1.show();
    sep("DA2");
    DA2.show();
    sep("pop");
    DA1.pop_back();
    DA1.show();
    sep("push_100");
    DA1.push_back(100);
    DA1.show();
    sep("comaration");
    std::cout << DA1[1] << " is in array in " << DA1.find(DA1[1]) << " pos" << std::endl;
    if (DA1 == DA2)
        std::cout << "is equal" << std::endl;
    else if (DA1 != DA2)
        std::cout << "is`t equal" << std::endl;


}

void test_stack()
{
    stack<int> st1(10);
    st1.push(10);
    st1.push(10312);
    st1.push(13230);
    st1.push(1230);
    st1.push(101322);


/*    st1.print();
    st1.clear();
    st1.print();  // terminal must be empty

    stack<int> st2(st1);

    sep();
    if (st1 == st2)
        std::cout << "equal \n";
    sep();*/





}

int main() {
    using namespace std;

    try
    {
        test_lits(); //#TODO write tests normaly
        //test_stack();
        //test_dynamic_array();

    }
    catch (exception& err)  // does`t work. why??
    {
        err.what();
    }

    return 0;
}
