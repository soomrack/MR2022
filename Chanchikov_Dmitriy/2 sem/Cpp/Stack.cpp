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
    explicit Stack(unsigned int size_);
    Stack(const Stack& x);
    ~Stack();
    Stack& operator=(const Stack& x);

    void push(double x);
    void pop();

    double top();
    double get(unsigned int n);

    unsigned int get_size() const;
    unsigned int get_stack_point() const;

    void output(bool inf = false);

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
        //Stack temp;
        auto *temp = new double[size + BASE_SIZE];
        for (unsigned int idx = 0; idx < stack_point; idx++){
            temp[idx] = data[idx];
        }
        delete[] data;
        data = temp;
        size += BASE_SIZE;
    }
    data[stack_point++] = x;
}


void Stack::pop() {
    stack_point--;
}


double Stack::top() {
    std::cout << "Top: " << data[stack_point - 1] << "\n";
    return data[stack_point - 1];
}

double Stack::get(unsigned int n) {
    unsigned int shift = std::min(n, stack_point - 1);
    std::cout << "Get(" << n << "): " << data[stack_point - 1 - shift] << "\n";
    return data[stack_point - 1 - shift];
}


unsigned int Stack::get_size() const {
    std::cout << "Get size: " << size << "\n";
    return size;
}


unsigned int Stack::get_stack_point() const {
    std::cout << "Get stack point: " << stack_point << "\n";
    return stack_point;
}


void Stack::output(bool inf) {
    if (inf) {
        std::cout << "Size: " << size << "\n";
        std::cout << "Stack point: " << stack_point << "\n";
    }
    std::cout << "Stack: ";
    for (unsigned int idx = 0; idx < stack_point; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n\n";
}


int main() {
    std::cout << "\nA\n\n";
    Stack A;
    A.output(true);
    A.push(10.0);
    A.push(20.0);
    A.output();
    A.top();

    std::cout << "\nB\n\n";
    Stack B = Stack(5);
    B.push(0.1);
    B.push(1.2);
    B.push(2.3);
    B.push(3.4);
    B.push(4.5);
    B.push(5.6);
    B.output(true);
    B.get(3);

    std::cout << "\nC\n\n";
    Stack C(10);
    C.push(1);
    C.push(-2);
    C.push(3);
    C.push(-4);
    C.get_size();
    C.get_stack_point();
    C.output();
    C.pop();
    C.pop();
    C.output();

    return 0;
}
