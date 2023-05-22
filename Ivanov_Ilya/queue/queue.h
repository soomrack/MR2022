#ifndef MR2022_queue
#define MR2022_queue
#include "iostream"
class queue_error : public std:: domain_error{
    public:
    queue_error(const char* const message): std:: domain_error(message){}
};
queue_error empty("queue is empty");

class queue {
private:
    int* data;
    int head;
    int current_size;
    int tail;
public:
    queue();
   ~queue();
    void push(int x);
    int pop();
    void print();
    bool is_empty();
    unsigned int get_size();
};


queue::queue() {
    current_size = 0;
    data = new int[current_size];
    head = -1;
    tail = -1;
};

queue::~queue() {
    delete[] data;
    std::cout << "destructor"<< "\n";
}
bool queue::is_empty() {
    return head == -1 ;
};
void queue::push(int x){
    tail++;
    data[tail] = x;
    current_size++;
    if (head == -1) head = 0;
    }
int queue::pop() {
    if(is_empty()) throw empty;
    int value = data[head];
    head++;
    if (head > tail) {
      head = tail = -1;
    }
    current_size--;
    return value;
  }

unsigned int queue::get_size() {
    if (is_empty()) throw empty;
   return current_size;
}
void queue::print(){
    for (int i = head; i <=tail; i++) {
     std:: cout << data[i] << "\n";
}
}
#endif //MR2022_queue
