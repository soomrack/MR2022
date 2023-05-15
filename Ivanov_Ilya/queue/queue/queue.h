#ifndef MR2022_queue
#define MR2022_queue
#include "iostream"
class queue_error : public std:: domain_error{
    public:
    queue_error(const char* const message): std:: domain_error(message){}
};
queue_error overflowed("queue is over");
queue_error empty("queue is empty");

class queue {
private:
    int *data;
    int head;
    int capacity;
    int current_size;
    int tail;
public:
    queue();
   ~queue();
    void push(int x);
    int pop();
    void print();
    bool is_full();
    bool is_empty();
    unsigned int get_size();
};


queue::queue() {
    current_size = 0;
    head = -1;
    tail = -1;
};

queue::~queue() {
    std::cout << 'desr';
}
bool queue::is_full() {
    return tail == capacity - 1;
};
bool queue::is_empty() {
    return head == -1 || head > tail;
};
void queue::push(int x){
    if(is_full()) throw overflowed;
        data[++tail] = x;
        current_size++;
        if (head == -1) head = 0;
    }
int queue::pop() {
    if (is_empty()) throw empty;
    current_size--;
   return data[head++];
}
unsigned int queue::get_size() {
    if (is_empty()) throw empty;
   return current_size;
}
void queue::print(){
    for(int i=0; i<current_size;i++){
    std::cout << data[i] << " ";
}
}
#endif //MR2022_queue
