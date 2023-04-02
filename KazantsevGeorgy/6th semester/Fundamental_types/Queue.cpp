#include <iostream>
#include "except.h"


AtypesException QUEUEOVERFLOW("Trying to push into full queue!");


template <typename Q>
class Queue{
    Q *Values;
    int Size{};
    int Tempsize;
    int Front;
    int Rear;
public:

    explicit Queue(int size);
    ~Queue();

    // методы
    Q Pop();
    void Push(Q item);
    Q Peek();
    int QSize();
    bool IsEmpty();
    void Print();
    bool IsFull();
};

template <typename Q>
Queue<Q>::Queue(int size) {
    Values = new double[size];
    this->Size = size;
    Tempsize = 0;
    Front = 0;
    Rear = -1;
}

template <typename Q>
Queue<Q>::~Queue() {
    delete [] Values;
}

template <typename Q>
Q Queue<Q>::Pop()
{
    if (IsEmpty())
    {
        throw QUEUEOVERFLOW;
    }
    double x = Values[Front];
    Front = (Front + 1) % Size;
    Tempsize--;
    return x;
}

template <typename Q>
void Queue<Q>::Push(Q item)
{
    if (IsFull())
    {
        throw QUEUEOVERFLOW;
    }
    Rear = (Rear + 1) % Size;
    Values[Rear] = item;
    Tempsize++;
}

template <typename Q>
Q Queue<Q>::Peek()
{
    if (IsEmpty())
    {
        throw QUEUEOVERFLOW;
    }
    return Values[Front];
}

template <typename Q>
int Queue<Q>::QSize() {
    return Tempsize;
}

template <typename Q>
bool Queue<Q>::IsEmpty() {
    return (QSize() == 0);
}

template <typename Q>
bool Queue<Q>::IsFull() {
    return (QSize() == Size);
}

template <typename Q>
void Queue<Q>::Print() {
    std::cout << "\n";
    for(int i = Front; i < Rear + 1; i++) {
        std::cout << Values[i] << "\t";
    }
}

void QueueTestProgram() {
    Queue <double>A(5);
    try {
        A.Push(4);
        A.Push(3);
        A.Push(2);
        A.Push(1);
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    A.Print();

    try {
        A.Pop();
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    A.Print();

    try {
        std::cout << std::endl << "Queue peek: " << A.Peek();
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    A.Print();



}

int main() {
    QueueTestProgram();
}