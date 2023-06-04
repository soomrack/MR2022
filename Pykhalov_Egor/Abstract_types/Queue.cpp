#include <iostream>


const double COMPARATION_CONST = 0.0001;
const unsigned int BASE_SIZE = 100;

class Queue {

protected:

    unsigned int size;
    unsigned int head_pointer;
    unsigned int tail_pointer;
    double* data;

    bool is_normalized;
    bool is_empty;

public:

    Queue();
    Queue(const unsigned int size_);
    Queue(const Queue& x);
    ~Queue();

    void push (const double x);
    void pop ();
    double get (const unsigned int n = 0);

    unsigned int get_size ();
    bool empty ();
    void output (bool show_size = false);

};


Queue::Queue() {
    size = BASE_SIZE;
    data = new double[size];
    head_pointer = 0;
    tail_pointer = 0;
    is_normalized = true;
    is_empty = true;
}

Queue::Queue(const unsigned int size_) {
    size = size_;
    data = new double[size];
    head_pointer = 0;
    tail_pointer = 0;
    is_normalized = true;
    is_empty = true;
}


Queue::Queue(const Queue& x) {
    size = x.size;
    head_pointer = x.head_pointer;
    tail_pointer = x.tail_pointer;
    data = new double[size];

    is_normalized = x.is_normalized;
    is_empty = x.is_empty;
}


Queue::~Queue() {
    delete[] data;
}

void Queue::push(const double x) {
    if (is_normalized){
        if (tail_pointer == size){
            if (head_pointer != 0){
                is_normalized = false;
                tail_pointer = 0;
                data[tail_pointer++] = x;
            } else {
                double *temp = new double[size + BASE_SIZE];
                for (unsigned int idx = 0; idx < size; idx++) {
                    temp[idx] = data[idx];
                }
                temp[size] = x;
                delete[] data;
                data = temp;
                size += BASE_SIZE;
            }
        } else {
            data[tail_pointer++] = x;
        }
    } else {
        if (head_pointer == tail_pointer) {
            double *temp = new double[size + BASE_SIZE];
            for (unsigned int idx = 0; idx < tail_pointer; idx++) {
                temp[idx] = data[idx];
            }
            for (unsigned int jdx = size - 1; jdx >= head_pointer; jdx--) {
                temp[jdx + BASE_SIZE] = data[jdx];
            }

            data = temp;
            size += BASE_SIZE;
        }
        data[tail_pointer++] = x;

    }
}


void Queue::pop() {
    if (is_normalized) {
        if (head_pointer != tail_pointer)
            head_pointer++;
    }
    else {
        if (head_pointer == size - 1) {
            head_pointer = 0;
            is_normalized = true;
        } else {
            head_pointer++;
        }
    }
}


double Queue::get(const unsigned int n) {
    if (is_normalized) {
        return data[std::max(head_pointer, tail_pointer - n - 1)];
    } else {
        if (n >= tail_pointer) {
            return data[size - n + tail_pointer];
        } else {
            return data[tail_pointer - n];
        }
    }
}

unsigned int Queue::get_size() {
    return size;
}


bool Queue::empty() {
    return (head_pointer == tail_pointer);
}


void Queue::output(bool show_details) {
    if (show_details) std::cout << "Size: " << size << "\nHead: " << head_pointer << ";    Tail: " << tail_pointer << "\n";

    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n\n";
}


int main() {
    Queue A;
    Queue B = Queue(10);
    //double *a = {0.1, 1.2, 2.3, 3.4, 4.5, 5.6};
    B.push(0.1);
    B.push(1.2);
    B.push(2.3);
    B.push(3.4);
    B.push(4.5);
    B.push(5.6);
    B.push(6.5);
    B.push(7.4);
    B.push(8.3);
    B.push(9.2);

    B.output(true);

    std::cout << B.get(3) << "\n";

    B.pop();
    B.pop();
    B.pop();
    B.output(true);
    std::cout << B.get(3) << "\n";

    B.push(10.1);
    B.output(true);

    A.push(10.0);
    A.pop();
    std::cout << A.empty();

    return 0;
}
