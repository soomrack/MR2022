#include <iostream>
#include "DynamicArray.h"
#include "stack.h"
//#include "ExceptError.h"
#define STACK_SIZE 10
#define LIST_SIZE 10
#include "queue.h"
#include "BinarTree.h"
#include "List.h"
ExceptError DIVISIONBYZERO("DIV BY ZERO\n");
ExceptError STACKOVERFLOW("STACK IS FULL\n");
ExceptError BINARYTREEFULL("BINARYTREEFULL\n");
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
void ListTestProgram() {
    List <double>list;
    list.Print();
    ListNode<double> *s = list.getFirst();
    double ListArray[LIST_SIZE] = {1.6, 2.6, 2.8, 2.6, 3.9, -4.6,
                                   -6.4, -7.8, 0.6, 9.6,};
    for (double i : ListArray) {
        s = list.Add(i, s);
    }
    list.Print();
    cout << "List last value: " << List<double>::getValue(list.getLast())<< endl;

    ListNode<double> *p = list.getFirst();
    do {
        if (List<double>::getValue(p) < 0)
            p = list.Delete(p);
        else
            p = list.Next(p);
    }
    while (p != nullptr);

    List<double>::setValue(s, 5.1);
    list.Print();
    cout << "List count: " << list.getCount() << " " << endl;
    list.Swap(list.getFirst(), list.getLast());
    list.Print();
    list.Clear();
    list.Print();
    cout << "" << list.getCount() << "" << endl;
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

void ExceptionTestProgram() {
    try {
        int a, b, c;
        b = 2;
        cin >> c;
        a = b/c;
        cout << a;
    }
    catch(const ExceptError &e)
    {
        cerr << "Caught: " << e.what() << endl;
        cerr << "Type: " << typeid(e).name() << endl;
    }
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
    ListTestProgram();
}
