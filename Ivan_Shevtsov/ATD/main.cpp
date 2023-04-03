#include <iostream>

#include "list.h"
#include "stack.h"
#include "dynamic_array.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"

#define DEBUG

enum test_state{
    PASSED = 1,
    FAILED = 0,
    START = -1,
    ALL_PASSED = 2,
    MASKED = 3
};

void sep(const char* message= "")
{
    std::cout << "----------------------------" << message << "----------------------------\n";
}

void test_list(bool test_visible = true)
{
    sep("QUEUE TEST STARTED");
    using namespace list_names;
    list<int> lst1;
    lst1.insert_after(0, 0);
    lst1.push(1);
    lst1.push(2);
    lst1.push(3);
    lst1.push(4);
    lst1.push(5);
    lst1.show();
    sep("pop");
    lst1.pop();
    lst1.pop();
    lst1.show();
    sep("insert");
    lst1.insert_after(100, 3);
    lst1.show();
    sep("del after");
    lst1.delete_after(3);
    lst1.show();
    std::cout << lst1[1] << "\n";
    sep("list 2");
    list<int> lst2(lst1);
    lst2.show();
    if (lst1 == lst2)
        std::cout << "equal!\n";
}

void delay(){ int a; for (int i = 0; i < 1000000000; i++) {a = i;}}

void test_dynamic_array()
{
    using namespace DynArr_names;
    dynamic_array DA1(10);
    dynamic_array DA2(10);
    DA1.fill_random();
#ifndef DEBUG
    delay();
#endif
    DA2.fill_random();
    sep("DA2");
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
    using namespace stack_names;
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

void test_tree(){
    using namespace tree_names;


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

void test_graph(){
    using namespace graph_names;

}

int main() {
    using namespace std;
    try{
        //test_list(); //#TODO написать нормально тесты
        //test_stack();
        test_dynamic_array();
        //test_queue();
        //test_tree();
        //test_graph();
    }
    catch (const list_names::list_exceptions& err){
        std::cerr << "List exception: " << err.what() << std::endl;;}
    catch (const DynArr_names::dynamic_array_exceptions& err){
        std::cerr << "Dynamic array exception: " << err.what() << std::endl;}
    catch (const queue_names::queue_exceptions& err){
        std::cerr << "Queue exception: " << err.what() << std::endl;}
    catch (const tree_names::tree_exceptions& err){
        std::cerr << "Tree exception: " << err.what() << std::endl;}
    catch (const graph_names::graph_exceptions& err){
        std::cerr << "Graph exception: " << err.what() << std::endl;}
    catch (const stack_names::stack_exceptions& err){
        std::cerr << "Stack exception: " << err.what() << std::endl;}

    return 0;
}


