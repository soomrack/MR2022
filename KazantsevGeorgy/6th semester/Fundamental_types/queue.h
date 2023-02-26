//
// Created by delta on 19.02.2023.
//

#ifndef CLIONPROJECTS_QUEUE_H
#define CLIONPROJECTS_QUEUE_H

#endif

#include <iostream>
#include <cstdlib>
using namespace std;

class Queue{
    double *values; // значения в очереди
    int size; // общий размер очереди
    int tempsize; //текущий размер
    int front; // первый элемент в очереди
    int rear; //последний элемент
public:
    // конструктор
    Queue(int _size);
    // деструктор
    ~Queue();

    // методы
    double RemoveFromQueue();
    void AddToQueue(double x);
    double QueuePeek();
    int QueueSize();
    bool IsEmpty();
    void QueueOutput();
    bool IsFull();
};

Queue::Queue(int _size) {
    values = new double[_size];
    size = _size;
    tempsize = 0;
    front = 0;
    rear = - 1;
}

Queue::~Queue() {
    delete [] values;
}

// Вспомогательная функция для удаления переднего элемента из очереди
double Queue::RemoveFromQueue()
{
    if (IsEmpty())
    {
        cout << "Underflow";
    }
    double x = values[front];
    front = (front + 1) % size; // остаток от деления
    tempsize--;
    return x;
}

void Queue::AddToQueue(double item)
{
    if (IsFull())
    {
        cout << "Overflow";
    }
    rear = (rear + 1) % size;
    values[rear] = item;
    tempsize++;
}

double Queue::QueuePeek()
{
    if (IsEmpty())
    {
        cout << "Underflow";
    }
    return values[front];
}

int Queue::QueueSize() {
    return tempsize;
}

bool Queue::IsEmpty() {
    return (QueueSize() == 0);
}

bool Queue::IsFull() {
    return (QueueSize() == size);
}

void Queue::QueueOutput() {
    cout << "\n";
    for(int i = front; i < rear + 1; i++) {
        cout << values[i] << "\t";
    }
}