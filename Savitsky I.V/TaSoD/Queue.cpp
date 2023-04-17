#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define SIZE 1000
 
class queue {
protected:

    unsigned int size;
    unsigned int head_point;
    unsigned int tail_point;
    int* data;

public:

    queue(unsigned int size = SIZE);
    ~queue();

   // queue& operator=(const queue& x);

    void push(const int x);
    void pop();
    //double get(const unsigned int n = 0);  

    
    void show();
};

queue::queue(unsigned int size) {
    this->size = size;
    data = new int[size];
    head_point = 0;
    tail_point = 0;
}
queue::~queue() {
    delete[] data;
}

void queue::push(const int x) {
    if (tail_point < size)
        data[tail_point++] = x;
    else
        std::cout << "ќчередь заполнена" << std::endl;
}

void queue::pop() {
    if (head_point < tail_point) {
        
        std::cout <<"Ёлемент: " << data[head_point++]<< " удалЄн из очереди"<<std::endl;
        
    }
    else
        std::cout << "ќчередь пуста" << std::endl;
}

void queue::show(){
    
    for (unsigned int idx = head_point; idx < tail_point; idx++) {
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n\n";
}

void main() {
    setlocale(LC_ALL, "Russian");
    queue q = queue(20);
    for (int i = 0; i < 10; i++)
        q.push(i);
    q.show();
    for (int i = 0; i < 5; i++)
        q.pop();
    q.show();
    q.push(5);
    q.push(10);
    q.show();
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.push(5);
    q.push(10);
    q.pop();
    q.pop();
    q.pop();
    q.show();
}
