#include <iostream>

#include "list.h"
#include "stack.h"
#include "dynamic_array.h"
#include "queue.h"

#ifndef exceptions
#define exceptions
class common_exc: public std::domain_error{
public:
    common_exc(const char* massage): std::domain_error(massage){}
};

common_exc ZERO_SIZE("zero size error");
common_exc OUT_OF_TRE_RANGE_1("index out of the range(operator [])");
common_exc QUEUE_POP_ERROR("can`t pop from empty queue");
common_exc QUEUE_SHOW_ERROR("can`t show zero size queue");
common_exc CANT_ADD_ELEMENT("can`t add element in empty list");  // #TODO: сделать в каждом типе данных класс исключений, проверять на повторное включение этого класса, добавить сообщения об ошибках в каждый файл
#endif

#define DEBUG

// enum: psstate #TODO

void sep(const char* massege= "")
{
    std::cout << "----------------------------" << massege << "----------------------------\n";
}

void test_lits(bool test_visible = true)
{
    list<int> lst1;
    lst1.TEST();



    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;

/*    sep("pop_back");
    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;


    list<int> lst2(lst1);
    sep("list_2");
    for (int i = 0; i < lst1.lenght(); i++)
        std::cout << lst1[i] << std::endl;
    std::cout << lst1.lenght() << " nodes in list" << std::endl;

    if (lst1 == lst2)
        std::cout << "equal" << std::endl;*/
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

void test_queue() {
    sep("QUEUE TEST STARTED");
    using namespace queue_names;
    queue que1;
    que1.push(1);
    que1.push(2);
    que1.push(3);
    que1.push(4);
    sep("QUEUE1");
    que1.show();
    que1.pop();
    que1.pop();




    sep("POP");

    que1.show();
    std::cout << que1.get_element(0) << std::endl;
    std::cout << que1.get_element(1) << std::endl;
    std::cout << que1.get_element(2) << std::endl;  // error



}

int main() {
    using namespace std;

    try
    {
        //test_lits(); //#TODO write tests normaly
        //test_stack();
        //test_dynamic_array();
        test_queue();

    }
    catch (const common_exc& err)  // does`t work. why??
    {
        std::cerr << err.what() << std::endl;;
    }

    return 0;
}


