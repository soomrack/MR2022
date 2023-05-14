#include <iostream>
using namespace std;

class PriorityQueue {
private:
    int *data; // Массив элементов очереди
    int capacity; // Максимальная вместимость очереди
    int size; // Текущий размер очереди

public:
    PriorityQueue(int n); // Конструктор, инициализирующий массив и устанавливающий размер на 0
    ~PriorityQueue(); // Деструктор, освобождающий память, выделенную под массив

    void push(int value); // Добавление элемента в очередь
    void pop(); // Удаление элемента из очереди
    int front(); // Возвращает значение первого элемента в очереди (с наибольшим приоритетом)
    int rear(); // Возвращает значение последнего элемента в очереди (с наименьшим приоритетом)
    bool is_empty(); // Проверка, является ли очередь пустой
    bool is_full(); // Проверка, является ли очередь полной
};

PriorityQueue::PriorityQueue(int n) {
    capacity = n;
    data = new int[capacity];
    size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] data;
}

void PriorityQueue::push(int value) {
    if (is_full()) {
        return;
    } else {
        int i = 0;
        while (i < size && data[i] > value) {
            i++;
        }
        for (int j = size; j > i; j--) {
            data[j] = data[j - 1];
        }
        data[i] = value;
        size++;
    }
}

void PriorityQueue::pop() {
    if (is_empty()) {
        return;
    } else {
        for (int i = 0; i < size; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
}

int PriorityQueue::front() {
    if (is_empty()) {
        return -1;
    } else {
        return data[size - 1];
    }
}

int PriorityQueue::rear() {
    if (is_empty()) {
        return -1;
    } else {
        return data[0];
    }
}

bool PriorityQueue::is_empty() {
    return (size == 0);
}

bool PriorityQueue::is_full() {
    return (size == capacity);
}

int main() {
    PriorityQueue pq(5);

    pq.push(3);
    pq.push(5);
    pq.push(1);

    std::cout << "Front element of the priority queue: " << pq.front() << std::endl;
    std::cout << "Rear element of the priority queue: " << pq.rear() << std::endl;

    pq.pop();

    std::cout << "Front element of the priority queue after pop: " << pq.front() << std::endl;
    std::cout << "Rear element of the priority queue after pop: " << pq.rear() << std::endl;

    return 0;
}
