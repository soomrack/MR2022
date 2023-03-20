#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Queue {
private:
    int size;
    int *arr;
    int head;
    int tail;

public:
    Queue(int s) // constructor
    {
        size = s;
        arr = new int[s];
        head = 0;
        tail = 0;
    }

    void fill() //put '11)s' elements in the queue
    {
        //srand(time(0));
        for (int i = 0; i < size-1; i++)
            arr[i] = rand()%10;
        tail = size-1;
    }

    int pop() // take off one element from queue
    {
        if (head < tail)
            return arr[head++];
        else
            cout << "Очередь пустая." << endl;
        return 0;
    }


    void push(int el) // insert one element
    {
        if (tail < size)
            arr[tail++] = el;
        else
            cout << "Очередь переполнена." << endl;
    }

    void print() // print queue to console
    {
        for (int i = head; i < tail; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void free() // remove all elements from queue
    {
        delete arr;
    }

    bool is_empty() // check emptiness of  queue
    {
        return head == tail;
    }

    ~Queue() // destructor
    {
        delete arr;
    }
};





int main()
{
    Queue queue(15);
    queue.fill();
    queue.print();
    queue.push(10);
    queue.pop();
    queue.print();
    queue.free();
    cout << queue.is_empty() << endl;
    return 0;
}
