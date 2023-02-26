#include <iostream>


const double COMPARATION_CONST = 0.0001;
const unsigned int BASE_SIZE = 100;


class Queue {

protected:

    unsigned int size;
    unsigned int head_point;
    unsigned int tail_point;
    double* data;

    bool is_normalized;
    bool is_empty;

public:

    Queue();
    Queue(const unsigned int size_);
    Queue(const Queue& x);
    Queue(Queue&& x);
    ~Queue();

    Queue& operator=(const Queue& x);

    void push(const double x);
    void pop();
    double get(const unsigned int n = 0);  // возвращает n-ый с начала элемент  =  peek

    unsigned int get_size();
    bool empty();
    void output(bool show_details = false);

};


Queue::Queue() {
    size = BASE_SIZE;
    data = new double[size];
    head_point = 0;
    tail_point = 0;
    is_normalized = true;
    is_empty = true;
}


Queue::Queue(const unsigned int size_) {
    size = size_;
    data = new double[size];
    head_point = 0;
    tail_point = 0;
    is_normalized = true;
    is_empty = true;
}


Queue::Queue(const Queue& x) {
    size = x.size;
    head_point = x.head_point;
    tail_point = x.tail_point;
    data = new double[size];

    is_normalized = x.is_normalized;
    is_empty = x.is_empty;

    for (unsigned int idx = 0; idx < x.size; idx++){
        data[idx] = x.data[idx];
    }
}


Queue::Queue(Queue &&x) {
    size = x.size;
    data = x.data;
    head_point = x.head_point;
    tail_point = x.tail_point;
    is_normalized = x.is_normalized;
    is_empty = x.is_empty;


    x.size = 0;
    x.head_point = 0;
    x.tail_point = 0;
    x.data = nullptr;
}


Queue::~Queue() {
    delete[] data;
}


Queue &Queue::operator=(const Queue &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        size = x.size;
        head_point = x.head_point;
        tail_point = x.tail_point;
        is_normalized = x.is_normalized;
        is_empty = x.is_empty;

        this->data = new double[size];

        for (unsigned int idx = 0; idx < size; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


void Queue::push(const double x) {
    if (is_normalized){
        if (tail_point == size){
            if (head_point != 0){
                is_normalized = false;
                tail_point = 0;
                data[tail_point++] = x;
            } else {

                double *temp = new double[size + BASE_SIZE];
                for (unsigned int idx = 0; idx < size; idx++){
                    temp[idx] = data[idx];
                }
                temp[size] = x;
                //delete[] data;
                data = temp;
                size += BASE_SIZE;
            }
        } else {
            data[tail_point++] = x;
        }
    }
    else {
        if (head_point == head_point){
            double *temp = new double[size + BASE_SIZE];
            for (unsigned int idx = 0; idx < tail_point; idx++){
                temp[idx] = data[idx];
            }
            for (unsigned int jdx = size - 1; jdx >= head_point; jdx--){
                temp[jdx + BASE_SIZE] = data[jdx];
            }
            //delete[] data;
            data = temp;
            size += BASE_SIZE;
        }
        data[tail_point++] = x;
    }
}


void Queue::pop() {
    if (is_normalized){
        if (head_point != tail_point)
            head_point++;
    }
    else {
        if (head_point == size - 1){
            head_point = 0;
            is_normalized = true;
        } else {
            head_point++;
        }
    }
}


double Queue::get(const unsigned int n) {
    if (is_normalized){
        return data[std::max(head_point, tail_point - n - 1)];
    } else {
        if (n >= tail_point){
            return data[size - n + tail_point];
        } else {
            return data[tail_point - n];
        }
    }
}


unsigned int Queue::get_size() {
    return size;
}


bool Queue::empty() {
    return (head_point == tail_point);
}


void Queue::output(bool show_details) {
    if (show_details) std::cout << "Size: " << size << "\nHead: " << head_point << ";    Tail: " << tail_point << "\n";

    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n\n";
}


int main() {
    Queue A;
    Queue B = Queue(10);
    double *a = {0.1, 1.2, 2.3, 3.4, 4.5, 5.6};
    B.push(0.1);
    B.push(1.2);
    B.push(2.3);
    B.push(3.4);
    B.push(4.5);
    B.push(5.6);

    B.output(true);

    std::cout << B.get(3) << "\n";

    B.pop();
    B.output(true);
    std::cout << B.get(3) << "\n";

    A.push(10.0);
    A.pop();
    std::cout << A.empty();

    return 0;
}
