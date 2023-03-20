#include <iostream>
#include <new>
using namespace std;

double E = 0.00000001;

class QueueException {
public:
    int kod_mistake;
    QueueException();
    QueueException(int kod_mistake);
    void set_mistake (int kod_mistake);
};


QueueException Overflow=(1);
QueueException Underflow=(2);

QueueException:: QueueException(){
    kod_mistake = 999;
}


QueueException:: QueueException(int kod){
    kod_mistake = kod;
}


void QueueException::set_mistake (int error){
    switch (error) {
        case 1:
            std::cout << "\n"<< "       Overflow --> Program Terminated \n"<< "\n";
            break;
        case 2:
            std::cout<< "\n" << "       Underflow --> Program Terminated\n"<< "\n";
            break;
        default:
            std::cout << "       Unknown error \n";
    }
}


class Queue {
private:
    double *queue_massive;
    unsigned int size_max;
    int sp;
    int pp;
    unsigned int size_real;
    unsigned int RESERVE = 5;

public:
    Queue();
    Queue(unsigned int);
    Queue(const Queue &obj);
    Queue(Queue &&x);
    ~Queue();

    Queue& operator=(const Queue& obj);

    void push( double);
    double pop( );
    inline bool  is_empty();
    void  print();
    void  print(int);
    int  search(bool, double);
    int search(double);
    inline bool is_full();

};


Queue:: Queue(){
    size_max = 0;
    queue_massive = nullptr;
}


Queue:: Queue(unsigned int size){
    size_max = size + RESERVE;
    queue_massive = new double [size_max];
    sp = -1;
    pp = 0;
    size_real = 0;
}


Queue::Queue(const Queue &obj) {
    size_max = obj.size_max;
    queue_massive = new double[size_max];
    for (unsigned int number = 0; number < size_max; number++)
        queue_massive[number] = obj.queue_massive[number];
}


Queue::Queue(Queue &&x) {
    size_max = x.size_max;
    queue_massive = x.queue_massive;
    sp = x.sp;
    pp = x.pp;
    size_real = x.size_real;
    x.size_max = 0;
    x.queue_massive = nullptr;
    x.sp = 0;
    x.pp= 0;
    x.size_real = 0;
}


Queue:: ~Queue() {
    delete[] queue_massive;
}


Queue& Queue:: operator =(const Queue& X) {
    if (this == &X) {
        return *this;
    }
    delete[] this->queue_massive;
    size_max = X.size_max;
    queue_massive = new double [size_max];
    for (unsigned int number = 0; number < size_max; number++) {
        this->queue_massive[number] = X.queue_massive[number];
    }
}


inline bool Queue::is_full() {
    return size_real == size_max;
}


void Queue:: push(double item){
    if (is_full()) {
        try { throw Overflow; }
        catch (QueueException error) { error.set_mistake(1); }
    }
    sp = (sp + 1) % size_max;
    queue_massive[sp] = item;
    size_real++;
}


inline bool Queue:: is_empty() {
    return size_real == 0;
}


double Queue:: pop() {
    if (is_empty()) {
        try{ throw Underflow;}
        catch (QueueException error){ error.set_mistake(2);} // перенеси ловить исключения в меин
    }
    double item = queue_massive[pp];
    pp = (pp + 1) % size_max;
    size_real--;
    return  item;
}



void Queue:: print(int) {
    for (auto number = pp; number < size_max; number++)
        cout << queue_massive[number] << "  ";
    for (auto number = 0; number <= sp; number++  )
        cout << queue_massive[number] << "  ";

    cout << endl;
}


void Queue:: print() {
    for (auto number = pp; number <= sp; number++)
        cout << queue_massive[number] << "  ";
    cout << endl;
    if (pp > sp) print(1);

}


int Queue::search(bool,double item) {
    int chet = 0;
    for (auto number = pp; number < size_max; number++) {
        chet++;
        if (abs(queue_massive[number] - item) < E) return chet;
    }
    for (auto number =0; number <= sp; number++  ){
        chet++;
        if (abs(queue_massive[number] - item) < E) return chet;
    }

    return -1;
}


int Queue::search(double item) {
    if (pp > sp) return search(true,item);
    int chet = 0;
    for ( auto number = pp; number <= sp; number++){
        chet++;
        if (abs(queue_massive[number] - item) < E) return chet;
    }
    return -1;
}


int main() {
    Queue My_queue = Queue{5};
    double r1, r2, r3;
    My_queue.push(1.00);
    My_queue.push(2.00);
    My_queue.push(3.00);
    My_queue.push(4.00);
    My_queue.push(5.00);
    My_queue.print();


    r1 =  My_queue.pop();
    r2 =  My_queue.pop();
    r3 =  My_queue.pop();
    cout << "After pop -->   "<<"R1 =  "<<r1<<";  R2 =  "<<r2<<";  R3 =  "<<r3<< endl;
    My_queue.print();


    My_queue.push(6.00);
    My_queue.push(7.00);
    My_queue.push(8.00);
    My_queue.print();


    r1 =  My_queue.pop();
    r2 =  My_queue.pop();
    r3 =  My_queue.pop();
    cout << "After pop -->   "<<"R1 =  "<<r1<<";  R2 =  "<<r2<<";  R3 =  "<<r3<< endl;
    My_queue.print();

    cout << "Search -->   "<<"8--> "<<My_queue.search(8.00)<< endl;

    My_queue.push(9.00);
    My_queue.print();
    My_queue.push(10.00);
    My_queue.print();
    My_queue.push(11.00);
    My_queue.print();
    cout << "Search -->   "<<"11--> "<<My_queue.search(11.00)<< endl;
    My_queue.push(12.00);
    My_queue.print();
    My_queue.push(13.00);
    My_queue.print();
    My_queue.push(14.00);
    My_queue.print();
    My_queue.push(15.00);
    My_queue.print();
    My_queue.push(16.00);
    My_queue.print();
    My_queue.push(17.00);


    My_queue.print();


    return 0;

}






