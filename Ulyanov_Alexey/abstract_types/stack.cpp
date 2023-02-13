#include <iostream>


const double COMPARATION_CONST = 0.0001;
const unsigned int BASE_SIZE = 100;


class Stack {

protected:

    unsigned int size;
    unsigned int stack_point;
    double* data;

public:

    Stack();
    Stack(const unsigned int size_);
    Stack(const Stack& x);
    Stack(Stack&& x);
    ~Stack();

    Stack& operator=(const Stack& x);

    void push(const double x);
    void pop();
    double get(const unsigned int n = 0);  // возвращает n-ый с конца элемент  =  peek

    unsigned int get_size();
    bool empty();
    void output(bool show_size = false);

};


Stack::Stack() {
    size = BASE_SIZE;
    data = new double[size];
    stack_point = 0;
}


Stack::Stack(const unsigned int size_) {
    size = size_;
    data = new double[size];
    stack_point = 0;
}


Stack::Stack(const Stack& x) {
    size = x.size;
    stack_point = x.stack_point;
    data = new double[size];

    for (unsigned int idx = 0; idx < x.stack_point; idx++){
        data[idx] = x.data[idx];
    }
}


Stack::Stack(Stack &&x) {
    size = x.size;
    data = x.data;
    stack_point = x.stack_point;

    x.size = 0;
    x.stack_point = 0;
    x.data = nullptr;
}


Stack::~Stack() {
    delete[] data;
}


Stack &Stack::operator=(const Stack &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        size = x.size;
        stack_point = x.stack_point;

        this->data = new double[size];
        for (unsigned int idx = 0; idx < stack_point; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


void Stack::push(const double x) {
    if (stack_point == size){
        double *temp = new double[size + BASE_SIZE];
        for (unsigned int idx = 0; idx < stack_point; idx++){
            temp[idx] = data[idx];
        }
        //delete[] data;
        data = temp;
        size += BASE_SIZE;
    }
    data[stack_point++] = x;
}


void Stack::pop() {
    stack_point--;
}


double Stack::get(const unsigned int n) {
    unsigned int shift = std::min(n, stack_point - 1);
    return data[stack_point - 1 - shift];
}


unsigned int Stack::get_size() {
    return size;
}


bool Stack::empty() {
    return (stack_point == 0);
}


void Stack::output(bool show_size) {
    if (show_size) std::cout << "Size: " << size << "\n";

    for (unsigned int idx = 0; idx < stack_point; idx++){
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
