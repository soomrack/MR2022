#include <iostream>
//#include "main.h"
#include "stack.h"
//#include "exception.h"
#define STACK_SIZE 10
#include "queue.h"
#include "BinarTree.h"
using namespace std;

void QueueTestProgram() {
        Queue q(5);
        q.AddToQueue(1);
        q.AddToQueue(2);
        q.AddToQueue(3);
        q.QueueOutput();
        q.RemoveFromQueue();
        q.QueueOutput();
        q.AddToQueue(2.8);
        q.QueueOutput();
}

void StackTestProgram() {
    int position = 1;
    Stack A(STACK_SIZE);
    Stack B(STACK_SIZE);
    A.StackZering(); B.StackZering();
    A.StackPush(1);
    A.StackPush(2);
    A.StackPush(3);
    A.StackPush(4);
    A.StackPush(5);
    A.size_output();
    A.StackPop();
    A.size_output();
    A.StackPush(9.6);
    A.top_output();
    cout << "\nStack size: " << A.StackSize();
    cout << "\nStack top element: " << A.StackPeek();
    B = A;
    B.top_output();
    cout << "\nElement from the " << position << " position: " << B.StackGet(position);
}

void BinaryTreeTestProgram() {
    double Element = 8.9;
    Tree <double>A(6);
    A.insert(5.9);
    A.insert(9.7);
    A.insert(10.5);
    A.insert(8.9);
    A.erase(5.9);
    cout << "Is Element? " << A.find(Element) << "\n";
    A.print();
    cout << "TreeSize: " << A.BTSize() << "\n";
}

void EXceptionTestProgram() {
    int a, b, c;
    a = 2; b = 2;
    cin >> c;
    if (c == 0) throw DIVISIONBYZERO;
    a = b/c;
    cout << a;

    try {
        EXceptionTestProgram();
    }
    catch(const Exception &e)
    {
        cerr << "Caught: " << e.what() << endl;
        cerr << "Type: " << typeid(e).name() << endl;
    }
}



int main() {
    BinaryTreeTestProgram();
}
