#include <iostream>
#include <new>
using namespace std;

double E = 0.00000001;
unsigned int RESERVE = 5;
class Queue {
private:
    double *queue_massive;
    int count;
    int sp;


public:
    Queue();
    Queue(unsigned int);
    Queue(const Queue &obj);
    Queue(Queue &&x);
    ~Queue();

    Queue& operator=(const Queue& obj);

    void push( double);
    double pop( );
    bool  IsEmpty();
    void  print();
    int search(double);
    inline bool isFull();

};



Queue:: Queue(){
    count = 0;
    queue_massive = nullptr;
}


Queue:: Queue(unsigned int n){
    count = n + RESERVE;
    queue_massive = new double [count];
    sp = -1;

}


Queue::Queue(const Queue &obj) {
    count = obj.count;
    queue_massive = new double[count];
    for (int i = 0; i < count; i++)
        queue_massive[i] = obj.queue_massive[i];
}


Queue::Queue(Queue &&x) {
    count = x.count;
    queue_massive = x.queue_massive;
    x.count = 0;
    x.queue_massive = nullptr;
}


Queue:: ~Queue() {
    delete[] queue_massive;
}


Queue& Queue:: operator =(const Queue& X) {
    if (this == &X) {
        return *this;
    }
    delete[] this->queue_massive;
    count = X.count;
    queue_massive = new double [count];
    for (unsigned int number = 0; number < count; number++) {
        this->queue_massive[number] = X.queue_massive[number];
    }
}


inline bool Queue::isFull() {
    return sp == count - 1;
}


void Queue:: push(double item){
    if (isFull()) exit(EXIT_FAILURE);
    queue_massive[++sp] = item;
}


bool Queue:: IsEmpty() {
    return count == 0;
}


double Queue:: pop() {
    if (IsEmpty()) exit(EXIT_FAILURE);
    double item =queue_massive [0];
    for (unsigned int number = 1; number <= sp; number ++){
        queue_massive[number -1] = queue_massive[number];
    }
    sp--;
    return item;
}


void Queue:: print() {
    for (int i = 0; i <= sp; i++)
        cout << queue_massive[i] << "  ";
    cout << endl;
}


int Queue::search(double item) {
    for ( int number = 0; number < count; number++){
        if (abs(queue_massive[number] - item) < E) return number+1;
    }
    std:: cout << "Not found" << "\n";
    return 0;
}

int main() {
    Queue My_queue = Queue{5};
double r;
    My_queue.push(1.00);
    My_queue.push(2.00);
    My_queue.push(3.00);
    My_queue.push(4.00);
    My_queue.push(5.00);
    My_queue.push(6.00);
    My_queue.push(7.00);
    My_queue.push(8.00);
    My_queue.push(9.00);
    My_queue.push(10.00);


    My_queue.print();

    r =  My_queue.pop();
    r =  My_queue.pop();
    r =  My_queue.pop();
    My_queue.push(11.00);
    My_queue.print();

    r = My_queue.search(7.00);


    return 0;

}




