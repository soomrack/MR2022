#include <iostream>
#include <cstdlib>

using namespace std;

class Queue {
private:
    int size;
    int *arr;
    int first;
    int last;

public:
    Queue(int s) // Конструктор
    {
        size = s;
        arr = new int[s];
        first = 0;
        last = 0;
    }

    void fill()
    {
        for (int i = 0; i < size-1; i++)
            arr[i] = rand()%20;
        last = size-1;
    }

    int pop()
    {
        if (first < last)
            return arr[first++];
        else
            cout << "Очередь пустая" << endl;
        return 0;
    }


    void push(int p)
    {
        if (last < size)
            arr[last++] = p;
        else
            cout << "Очередь переполнена" << endl;
    }

    void print() // Вывод в консоль
    {
        for (int i = first; i < last; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void remove() // Очистить все элементы
    {
        delete arr;
    }

    bool is_empty() // Проверка пустая ли очередь
    {
        return first == last;
    }

    ~Queue() // Деструктор
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
    queue.remove();
    cout << queue.is_empty() << endl;
    return 0;
}
