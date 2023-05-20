#include <iostream>

const double COMPARATION_CONST = 0.0001;
const unsigned int BASE_SIZE = 100;

class Stack {

protected:

    unsigned int size;
    unsigned int stack_pointer;
    double* data;


public:

    Stack();
    Stack(const unsigned int size_);
    Stack(const Stack& x);
    ~Stack();

    void push (const double x);
    double pop ();
    double get (const unsigned int n = 0);

    unsigned int get_size ();
    bool empty ();
    void output (bool show_size = false);

};


Stack::Stack() {
    size = BASE_SIZE;
    data = new double[size];
    stack_pointer = 0;
}


Stack::Stack(const unsigned int size_) {
    size = size_;
    data = new double[size];
    stack_pointer = 0;
}


Stack::Stack(const Stack& x) {
    size = x.size;
    data = new double[size];

    for (unsigned int i = 0; i < x.stack_pointer; i++) {
        data[i] = x.data[i];
    }
}


Stack::~Stack() {
    delete[] data;
}


void Stack::push(const double x) {
    if (stack_pointer == size) {
        double* temp = new double[size + BASE_SIZE];
        for (unsigned int i = 0; i < stack_pointer; i++) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        size += BASE_SIZE;
    }
    data[stack_pointer++] = x;
}


double Stack::pop() {
    if (stack_pointer == 0)  return 0;

    double poped = data[stack_pointer];
    stack_pointer--;

    return poped;
}


double Stack::get(const unsigned int n) {
    unsigned int chk_n = std::min(n, stack_pointer);
    return data[chk_n];
}


unsigned int Stack::get_size() {
    return size;
}


bool Stack::empty() {
    return (stack_pointer == 0);
}


void Stack::output(bool show_size) {
    if (show_size) std::cout << "Size: " << size << "\n";

    for (unsigned int idx = 0; idx < stack_pointer; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n\n";
}


int main() {
    Stack A;
    Stack B = Stack(5);

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
