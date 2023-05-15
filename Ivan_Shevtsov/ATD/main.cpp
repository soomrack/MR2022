#include <iostream>

#include "list.h"
#include "stack.h"
#include "dynamic_array.h"
#include "queue.h"
#include "tree.h"
#include "graph.h"

//#define DEBUG

enum test_state{
    PASSED = 1,
    FAILED = 0,
    START = -1,
    ALL_PASSED = 2,
    MASKED = 3
};

void exc_text();

void sep(const char* message= "")
{
    std::cout << "----------------------------" << message << "----------------------------\n";
}

void test_list(bool test_visible = true)
{
    sep("LIST TEST STARTED");
    using namespace list_names;
    list<int> lstTest;
    lstTest.push(1);
    lstTest.push(2);
    lstTest.push(3);
    lstTest.push(4);
    lstTest.push(5);

    for (auto &&node: lstTest){
        std::cout << node << std::endl;
    }

    list<int> lst1;
    try {
        lst1.insert_after(0, 0);
    }
    catch (ListException& ex){
        std::cerr << "List exception in func: " << ex.what() << std::endl;}
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

    sep("list 2");
    list<int> lst2(lst1);
    lst2.show();
    lst1.show();
    if (lst1 == lst2)
        std::cout << "equal!\n";
    sep("LIST TEST ENDED");
}

void delay(){ int a; for (int i = 0; i < 1000000000; i++) {a = i;}}

void test_dynamic_array()
{
    sep("ARRAY TEST STARTED");

    using namespace DynArr_names;
    dynamic_array<int> DA1(10);
    dynamic_array<int> DA2(10);
    DA1.fill_random_int();
#ifndef DEBUG
    delay();
#endif
    DA2.fill_random_int();
    sep("DA1");
    DA1.show();
    sep("DA2");
    DA2.show();
    sep("pop");
    DA1.pop_back();
    DA1.show();
    sep("push_100");
    DA1.push_back(100);
    DA1.show();
    sep("comparison");
    std::cout << DA1[1] << " is in array in " << DA1.find(DA1[1]) << " pos" << std::endl;
    if (DA1 == DA2)
        std::cout << "is equal" << std::endl;
    else if (DA1 != DA2)
        std::cout << "is`t equal" << std::endl;
    sep("test transfer constructor");
    dynamic_array<int> DA3(10);
    DA3.fill_random_int();
    DA3.show();

    auto DA4 = std::move(DA3);
    DA4.show();

/*
    for (auto value : DA4){
        std::cout << value << std::endl;
    }
*/


    sep("ARRAY TEST ENDED");
}

void test_stack()
{
    sep("STACK TEST STARTED");
    using namespace stack_names;
    stack<int> st1(50);
    st1.push(1);
    st1.push(2);
    st1.push(3);
    st1.push(4);
    st1.push(5);
    st1.push(6);
    st1.push(7);
    st1.push(8);
    st1.push(9);
    st1.push(10);
    st1.push(43);
    st1.push(2);
    st1.push(3);
    st1.push(42);
    st1.push(5);
    st1.push(6);
    st1.push(7);
    st1.push(8);
    st1.push(9);
    st1.push(10);
    st1.print();
    st1.clear();
    stack<char>st2(50);
    st2.push('i');
    st2.push('v');
    st2.push('a');
    st2.push('n');
    st2.print();
    sep("pop");
    st2.pop();
    st2.push('N');
    st2.print();
    auto a = st2.top();
    std::cout <<"TOP: " << a << "\n";
    stack st3(st2);
    if (st3 == st2){
        sep("equal");
    }
    else sep("not equal");
    sep("STACK TEST ENDED");

}

void test_tree(){
    using namespace tree_names;


}

void test_queue() {
    sep("QUEUE TEST STARTED");
    using namespace queue_names;
    queue<double> que1;
    que1.push(1);
    que1.push(2);
    que1.push(3);
    que1.push(4);
    sep("QUEUE1");
    que1.show();
    que1.pop();

    sep("POP");

    que1.show();
    sep("PRINT VALUE");
    std::cout << que1.get_element(0) << std::endl;
    std::cout << que1.get_element(1) << std::endl;
    std::cout << que1.get_element(2) << std::endl;
    std::cout << "NOW MAST BE EXCEPTION: \n";
    std::cout << que1.get_element(3) << std::endl;  // error


    queue<double> que2;
    que2.push(1);
    que2.push(2);
    que2.push(3);
    que2.push(4);
    sep("QUEUE2");

    sep("QUEUE TEST ENDED");

}

void test_graph(){
    using namespace graph_names;
    Graph graph1;
    sep("GRAPH TEST STARTED");

    // input
    Node* node1 = new   Node(1.0);
    Node* node2 = new   Node(2);
    Node* node3 = new   Node(3);
    Node* node4 = new   Node(4);
    Node* node5 = new   Node(5);
    Node* node6 = new   Node(6);
    Node* node7 = new   Node(7);
    Node* node8  = new  Node(8 );
    Node* node9  = new  Node(9 );
    Node* node10  = new Node(10);
    Node* node11 = new  Node(11);


    graph1.add_node(node1);
    graph1.add_node(node2);
    graph1.add_node(node3);
    graph1.add_node(node4);
    graph1.add_node(node5);
    graph1.add_node(node6);
    graph1.add_node(node7);
    graph1.add_node(node8 );
    graph1.add_node(node9 );
    graph1.add_node(node10);
    graph1.add_node(node11);

    graph1.add_edge(node1, node2, 3);
    graph1.add_edge(node1, node3, 2);
    graph1.add_edge(node1, node4, 1);
    graph1.add_edge(node4, node5, 10);
    graph1.add_edge(node5, node5, 10);
    graph1.add_edge(node5, node9, 15);
    graph1.add_edge(node3, node6, 8);
    graph1.add_edge(node6, node5, 5);
    graph1.add_edge(node6, node8, 6);
    graph1.add_edge(node8, node9, 1);
    graph1.add_edge(node10, node8, 5);
    graph1.add_edge(node2, node7, 12);
    graph1.add_edge(node2, node6, 4);
    graph1.add_edge(node7, node6, 3);


    //Node* delNode1 = new Node(2);
    //Node* delNode2 = new Node(2);
    //graph1.add_node(delNode1);
    //graph1.add_node(delNode2);
    //graph1.add_edge(delNode1, delNode2, 2);
    //graph1.add_edge(delNode2, delNode1, 3);
    //graph1.add_edge(node2, delNode2, 4);
    //graph1.add_edge(node1, delNode1, 4);

    // test
    graph1.show();
    sep();
    //graph1.del_node(2, false);
    //graph1.show();
    sep("dijkstra test");
    std::cout << graph1.dijkstra_simple(node1, node9, true)->dist << "\n";

    sep("dijkstra path");
    graph1.dijkstra_simple(node1, node9, false)->restore_path().show();
    sep("A* test");
    // GENERATE GRID MANUALLY
    auto* x_array = new DynArr_names::dynamic_array<double>;
    auto* y_array = new DynArr_names::dynamic_array<double>;

/*    x_array->push_back(0);
    x_array->push_back(20);
    x_array->push_back(10);
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();
    x_array->push_back();*/

    sep("GRAPH TEST ENDED");
}

void exc_text() {
    using namespace list_names;
    list<int> list1;
    list1.show();
}

int main() {
    using namespace std;
    try{
        //test_list(); //#TODO написать нормально тесты
        //test_stack();
        //test_dynamic_array();
        test_queue();
        //test_tree();

        //exc_text();
        //test_dijst();
       //test_graph();
    }
    catch (const list_names::ListException& err){
        std::cerr << "List exception: " << err.what() << std::endl;}
    catch (const DynArr_names::dynamic_array_exceptions& err){
        std::cerr << "Dynamic array exception: " << err.what() << std::endl;}
    catch (const queue_names::queue_exceptions& err){
        std::cerr << "Queue exception: " << err.what() << std::endl;}
    catch (const tree_names::tree_exceptions& err){
        std::cerr << "Tree exception: " << err.what() << std::endl;}
    catch (const graph_names::GraphException& err){
        std::cerr << "Graph exception: " << err.what() << std::endl;}
    catch (const stack_names::stack_exceptions& err){
        std::cerr << "Stack exception: " << err.what() << std::endl;}

    return 0;
}



