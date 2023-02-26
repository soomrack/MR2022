#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Queue {
private:
    // Размер очереди
    int size;
    // Указатель на массив чисел
    int *arr;
    // Начало очереди
    int head;
    // Конец очереди
    int tail;

public:
    // Конструктор
    Queue(int s)
    {
        size = s;
        arr = new int[s];
        head = 0;
        tail = 0;
    }

    // Заполнение очереди случайными числами
    void fill_queue()
    {
        srand(time(0));
        for (int i = 0; i < size-1; i++)
            arr[i] = rand()%20;
        tail = size-1;
    }

    // Добавление нового элемента в конец очереди
    void add(int el)
    {
        if (tail < size)
            arr[tail++] = el;
        else
            cout << "Очередь переполнена." << endl;
    }
    // Удаление элемента из начала очереди
    int remove()
    {
        if (head < tail)
            return arr[head++];
        else
            cout << "Очередь пустая." << endl;
        return 0;
    }
    // Вывод очереди
    void print_queue()
    {
        for (int i = head; i < tail; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
    // Удаление всей очереди
    void free_queue()
    {
        delete arr;
    }
    // Проверка очереди на пустоту
    bool is_empty()
    {
        return head == tail;
    }
    // Деструктор
    ~Queue()
    {
        delete arr;
    }
};

// Главная функция
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