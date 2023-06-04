#ifndef MR2022_QUEUE
#define MR2022_QUEUE

#include <iostream>

class queue_error : public std::domain_error {
public:
    queue_error(const char* const message) : std::domain_error(message) {}
};

queue_error empty("queue is empty");
queue_error full("queue is full");

class queue {
private:
    int* data;
    int* priorities;
    int capacity;  // Добавлено поле capacity для хранения максимальной вместимости очереди
    int head;
    int current_size;
    int tail;
public:
    queue(int capacity);
    ~queue();
    void push(int x, int priority);
    int pop();
    void print();
    bool is_empty();
    bool is_full();
    unsigned int get_size();
};

queue::queue(int capacity) {
    this->capacity = capacity; // Инициализируем capacity значением по умолчанию
    data = new int[capacity];
    priorities = new int[capacity];
    head = -1;
    tail = -1;
    current_size = 0;
}
bool queue::is_full() {
    return current_size == capacity;
}
queue::~queue() {
    delete[] data;
    delete[] priorities;
    std::cout << "destructor" << std::endl;
}

bool queue::is_empty() {
    return head == -1;
}

void queue::push(int x, int priority) {
    if (is_full()) {
        throw full;
    }
    if (is_empty()) {
        head = 0;
        tail = 0;
        tail = (tail + 1) % capacity;
        data[tail] = x;
        priorities[tail] = priority;
        current_size++;
        return;
    }
    int i = tail;
    while (i >= head && priority < priorities[i]) {
        int next_index = (i + 1) % capacity;
        data[next_index] = data[i];
        priorities[next_index] = priorities[i];
        i = (i - 1 + capacity) % capacity;
    }/* в формуле обновления значения i было добавлено + capacity,так как изначальный код мог выдать отрицательное значение, что не правильно, после изменений, значение (i - 1) сначала увеличивается на capacity, а затем берется остаток от деления на capacity, что гарантирует положительное значение i в диапазоне от 0 до capacity-1.*/
    int next_index = (i + 1) % capacity;
    data[next_index] = x;
    priorities[next_index] = priority;
    tail = (tail + 1) % capacity;
    current_size++;
}

int queue::pop() {
    if (is_empty()) throw empty;
    int value = data[head];
    head = (head + 1) % capacity;  // Обновляем значение head с учетом кольцевого поведения
    if (head == tail) {
        head = -1;
        tail = -1;
    }
    current_size--;
    return value;
}

unsigned int queue::get_size() {
    if (is_empty()) throw empty;
    return current_size;
}

void queue::print() {
    if (is_empty()) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }
    int i = head;
    while (i != tail) {
        std::cout << data[i] << std::endl;
        i = (i + 1) % capacity;  // Обновляем значение i с учетом кольцевого поведения
    }
    std::cout << data[i] << std::endl;
}

#endif // MR2022_QUEUE
