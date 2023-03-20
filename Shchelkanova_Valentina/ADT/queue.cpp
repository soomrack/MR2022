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
    Queue();

    ~Queue();

    void fill_queue();

    void push(int el);

    int pop();

    void print_queue();

    void free_queue();

    bool is_empty();

    Queue(int s);
};
    Queue::Queue(){
        size = s;
        arr = new int[s];
        head = 0;
        tail = 0;
    }

    void Queue::fill_queue()  // Заполнение очереди случайными числами
    {
        srand(time(0));
        for (int i = 0; i < size-1; i++)
            arr[i] = rand()%20;
        tail = size-1;
    }


    void Queue::push(int el)  // Добавление нового элемента в конец очереди
    {
        if (tail < size)
            arr[tail++] = el;
        else
            cout << "Очередь переполнена." << endl;
    }

    int Queue::pop()  // Удаление элемента из начала очереди
    {
        if (head != tail)
            return arr[head++];
        else return nullptr;
        return 0;
    }

    void Queue::print_queue()  // Вывод очереди
    {
        for (int i = head; i < tail; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void Queue::free_queue()  // Удаление всей очереди
    {
        delete arr;
    }

    bool Queue::is_empty()  // Проверка очереди на пустоту
    {
        return head == tail;
    }

    Queue::~Queue()  // Деструктор
    {
        delete arr;
    }
};

int main()
{
    Queue queue(10);
    queue.fill_queue();
    queue.print_queue();
    queue.add(3);
    queue.remove();
    queue.print_queue();
    queue.free_queue();
    cout << queue.is_empty() << endl;
    return 0;
}