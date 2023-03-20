#include <iostream>
#include <new>
using namespace std;

double E = 0.00000001;
unsigned int RESERVE = 5;


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
    int count;  //максимум в очереди
    int sp;
    int pp;
    int count_real;
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
    count = 0;
    queue_massive = nullptr;
}


Queue:: Queue(unsigned int size){
    count = size + RESERVE;
    queue_massive = new double [count];
    sp = -1;
    pp = 0;
    count_real = 0;
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
    sp = x.sp;
    pp = x.pp;
    count_real = x.count_real;
    x.count = 0;
    x.queue_massive = nullptr;
    x.sp = 0;
    x.pp= 0;
    x.count_real = 0;
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


inline bool Queue::is_full() {
    return count_real == count;
}


void Queue:: push(double item){
    if (is_full()) {
        try { throw Overflow; }
        catch (QueueException error) { error.set_mistake(1); }
    }
        sp = (sp + 1) % count;
        queue_massive[sp] = item;
        count_real++;
}


inline bool Queue:: is_empty() {
    return count_real == 0;
}


double Queue:: pop() {
    if (is_empty()) {
        try{ throw Underflow;}
        catch (QueueException error){ error.set_mistake(2);}
    }
    double item = queue_massive[pp];
    pp = (pp + 1) % count;
    count_real--;
    return  item;
}



void Queue:: print(int) {
    for (int i = pp; i < count; i++)
        cout << queue_massive[i] << "  ";
    for (int i =0; i<=sp; i++  )
        cout << queue_massive[i] << "  ";

    cout << endl;
}

void Queue:: print() {
    for (int i = pp; i <= sp; i++)
        cout << queue_massive[i] << "  ";
    cout << endl;
    if (pp > sp) print(1);

}

int Queue::search(bool,double item) {
    unsigned int chet = 0;
    for (unsigned int number = pp; number < count; number++) {
        chet++;
        if (abs(queue_massive[number] - item) < E) return chet;
    }
    for (unsigned int number =0; number <= sp; number++  ){
        chet++;
        if (abs(queue_massive[number] - item) < E) return chet;
    }

    return -1;
}


int Queue::search(double item) {
    if (pp > sp) return search(true,item);
    unsigned int chet = 0;
    for ( int number = pp; number <= sp; number++){
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





