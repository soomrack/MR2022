#include <iostream>
#include "ListList.h"
#include "except.h"
#include <cstdlib>


AtypesException FAILTOPOP("Trying to pop empty linked list!");
AtypesException FAILTOFRONTBACK("Try to access an item in an empty linked list!");


template <typename Q>
LinkedListNode<Q>::LinkedListNode(Q value, LinkedListNode<Q>*previos, LinkedListNode<Q>*next)
    : Data(value),
      Previos(previos),
      Next(next)
{
    //
}

template <typename Q>
LinkedList<Q>::LinkedList()
    : Head(nullptr)
{
    //
}

template <typename Q>
LinkedList<Q>::~LinkedList() {

}

template <typename Q>
void LinkedList<Q>::PushBack(Q value) {
    if (Head == nullptr)
    {
        Head = new LinkedListNode<Q>(value);
    }
    else
    {
        LinkedListNode<Q>* Current = Head;
        while(Current->Next != nullptr)
        {
            Current = Current->Next;
        }
        LinkedListNode<Q>* Temp = new LinkedListNode(value, Current);
        Current->Next = Temp;
    }
}

template <typename R>
std::ostream &operator<<(std::ostream &ostr, const LinkedList<R> &rhs) {

    LinkedListNode<R>* Current = rhs.Head;
    while (Current != nullptr)
    {
        std::cout << Current->Data << "\t";
        Current = Current->Next;
    }

    return ostr;
}

template <typename Q>
void LinkedList<Q>::PopBack() {
    if (Head == nullptr)
    {
        throw FAILTOPOP;
    }
    if (Head->Next == nullptr)
    {
        delete Head;
        Head = nullptr;
    }
    else
    {
        LinkedListNode<Q>* Current = Head;
        while (Current->Next != nullptr)
        {
            Current = Current->Next;
        }
        Current->Previos->Next = nullptr;
        delete Current;
    }
}

template <typename Q>
double LinkedList<Q>::Front() {
    if (Head == nullptr)
    {
        throw FAILTOFRONTBACK;
    }
    return Head->Data;
}

template <typename Q>
double LinkedList<Q>::Back() {
    if (Head == nullptr)
    {
        throw FAILTOFRONTBACK;
    }
    LinkedListNode<Q>* Current = Head;
    while (Current->Next != nullptr)
    {
        Current = Current->Next;
    }
    return Current->Data;
}

template <typename Q>
bool LinkedList<Q>::Empty() {
    return Head == nullptr;
}

template <typename Q>
void LinkedList<Q>::Clear() {
    LinkedListNode<Q>* Current = Head;
    while (Current != nullptr)
    {
        LinkedListNode<Q>* Temp = Current->Next;
        delete Current;
        Current = Temp;
    }
    Head = nullptr;
}

template <typename Q>
bool LinkedList<Q>::Find(Q value) {
    LinkedListNode<Q>* Current = Head;
    while (Current->Next != nullptr)
    {
        if (Current->Data == value)
        {
            return true;
        }
        Current = Current->Next;
    }
    return false;
}


int main() {
    LinkedList <double>A;
    A.PushBack(double(rand() % 100) + 0.5);
    A.PushBack(double(rand() % 100) + 0.4);
    A.PushBack(double(rand() % 100) + 0.3);
    A.PushBack(double(rand() % 100) + 0.2);
    A.PushBack(double(rand() % 100) + 0.1);
    std::cout << A << std::endl;
    std::cout << "FIND 69: " << A.Find(69.1) << std::endl;

    try {
        A.PopBack();
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    std::cout << A << std::endl;

    try {
        std::cout << "Front value: "<< A.Front() << std::endl;
        std::cout << "Back value: "<< A.Back() << std::endl;
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    std::cout << "Is empty: " << A.Empty() << std::endl;
    A.Clear();
    std::cout << "Is empty: " << A.Empty() << std::endl;
    std::cout << A << std::endl;
    return 0;
}