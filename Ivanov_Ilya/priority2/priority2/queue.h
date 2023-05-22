#ifndef MR2022_queue
#define MR2022_queue
#include "iostream"
class queue_error : public std:: domain_error{
    public:
    queue_error(const char* const message): std:: domain_error(message){}
};
queue_error empty("queue is empty");
queue_error full("queue is full");


class queue {
private:
    int* data;
    int* priorities;
    int capacity;
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
    this->capacity = capacity;
    data = new int[capacity];
    head = 0;
    tail = 0;
    current_size = 0;
}

queue::~queue() {
    delete[] data;
    //delete[] priorities;
    std::cout << "destructor"<< "\n";
}
bool queue::is_empty() {
    return head == -1 ;
};
bool queue::is_full() {
    return current_size == capacity;
}

void queue::push(int x, int priority) {
    if (is_full()) {
        throw full;
    }
    if (is_empty()) {
        head = 0;
        tail = 0;
        data[tail] = x;
        priorities[tail] = priority;
    } else {
        int i = tail;
        while (i >= head && priority < priorities[i]) {
            data[i + 1] = data[i];
            priorities[i + 1] = priorities[i];
            i--;
        }
        data[i + 1] = x;
        priorities[i + 1] = priority;
        tail = (tail + 1) % capacity;
    }
    current_size++;
}
int queue::pop() {
    if (is_empty()) {
        throw empty;
    }

    int value = data[head];
    head = (head + 1) % capacity;
    current_size--;
    return value;
}
unsigned int queue::get_size() {
    if (is_empty()) throw empty;
   return current_size;
}
void queue::print(){
    for (int i = 0; i < current_size; i++) {
        std::cout << data[(head + i) % capacity] << "\n";
    }
}
#endif //MR2022_queue
