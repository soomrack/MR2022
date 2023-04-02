#include <iostream>
#include "DynamicArray.h"
#include "stack.h"
#define LIST_SIZE 10
#include "queue.h"


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
    Stack <double>A(10);
    Stack <double>B(10);
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


void DynamicArrayTestProgram()
{
    double TempElement;
    int TempLength, K = 5;
    DynamicArray<double> A;
    A = DynamicArray<double>(5).i_number();
    A.increase(5);
    TempElement = A.get(K);
    cout << "current element position " << K <<" :" <<TempElement;
    A.decrease();
    TempLength = A.length();
    cout << "\ncurrent length: " << TempLength;
}
int main() {
    StackTestProgram();
}
