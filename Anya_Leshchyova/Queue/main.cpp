#include <iostream>
#include <new>
using namespace std;


class Queue {
private:
    double *queue_massive; // динамический массив
    int count; // количество элементов в очереди

public:
    Queue();
    Queue(unsigned int);


    Queue(const Queue &obj);
    Queue(Queue &&x);
    ~Queue();

    void push( double);
    double pop( );

    Queue& operator=(const Queue& obj);
    double GetItem();
    bool  IsEmpty();
    int GetN();
    void  print();
    int search(double);

};



Queue:: Queue(){
    count = 0; // очередь пустая
    queue_massive = nullptr;
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


Queue:: ~Queue() {  // деструктор
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


void Queue:: push(double item){
    if (count == 0){
        queue_massive = new double [count +1];
        queue_massive[0] = item;
        count++;
        return;
    }
    double* queue_massive_2;
    queue_massive_2 = new double [count];
    for (int i = 0; i < count; i++){
        queue_massive_2[i] = queue_massive[i] ;
    }
    queue_massive_2[count] =item;
    queue_massive = queue_massive_2;
    count++;
}


bool Queue:: IsEmpty() {
    return count == 0;
}


double Queue:: pop() {
    if (IsEmpty()) return 0.00;
    double item = queue_massive[0] ;
    if (count == 0)
        return 0;
    double*  queue_massive_2 = new double[count - 1];
    for (int i = 0; i < count - 1; i++)
        queue_massive_2[i] = queue_massive[i + 1];

    queue_massive = queue_massive_2;
    count--;
    return item;
}


double Queue::GetItem() {
    if (count == 0) return 0;
    return queue_massive[0];
}


int Queue::GetN() {
    return count;
}


void Queue:: print() {
    cout << "\n------------------- Current queue------------------- \n";
    for (int i = 0; i < count; i++)
        cout << queue_massive[i] << "  ";
    cout << endl;
}


int Queue::search(double item) {
    for ( int number = 0; number < count; number++){
        if (queue_massive[number] == item) return number+1;
    }
    std:: cout << "Not found" << "\n";
    return 0;
}

int main() {
    Queue My_queue;
    double r;
    My_queue.push(1.00);
    My_queue.push(2.00);
    My_queue.push(3.00);
    My_queue.push(4.00);
    My_queue.push(5.00);
    My_queue.push(6.00);
    My_queue.push(7.00);

    My_queue.print();

    cout << "-------------------After deletion-------------------\n";
    r =  My_queue.pop();
    r =  My_queue.pop();
    r =  My_queue.pop();
    My_queue.print();
    cout << "-------------------After search-------------------\n";
    r = My_queue.search(7.00);
    std::cout <<"Current position in the queue  " <<r<<"\n";

    return 0;

}

