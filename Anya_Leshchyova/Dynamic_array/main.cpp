#include <iostream>
#include <algorithm>

#include <exception>

double E =0.00000001;

static unsigned int RESERVE = 2;  //Запас пустого места в массиве

class DynamicArrayException {
public:
    int kod_mistake;
    DynamicArrayException();
    DynamicArrayException(int kod_mistake);
    void set_mistake (int kod_mistake);
};

DynamicArrayException Overflow=(1);
DynamicArrayException Underflow=(2);

DynamicArrayException:: DynamicArrayException(){
    kod_mistake = 999;
}

DynamicArrayException:: DynamicArrayException(int kod){
    kod_mistake = kod;
}


void DynamicArrayException::set_mistake (int error){
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

class DynamicArray {
protected:
    unsigned int size;
    double* line;
    int sp;




public:

    DynamicArray();
    DynamicArray( const unsigned int number);
    DynamicArray(const DynamicArray& A);
    DynamicArray(DynamicArray&& A);
    ~DynamicArray();



    void print();

    void pop (double);
    void push (double, unsigned int);
    void push (double);
    unsigned int search (double);
    inline bool is_full ();
    inline bool is_empty ();



    DynamicArray& operator=(const DynamicArray &x);
};


DynamicArray::DynamicArray() {
    size = RESERVE;
    line = new double[ size ];
    sp = -1;
}


DynamicArray::DynamicArray(const unsigned int number) {
    size = number + RESERVE;
    line = new double[size];
    sp = -1;
}



DynamicArray& DynamicArray::operator=(const DynamicArray &x) {
    if (this == &x) return *this;
    if (!line) delete[] line;
    size = x.size;
    this->line = new double[size + RESERVE];
    for (unsigned int number = 0; number < size + RESERVE; number++){
        line[number] = x.line[number];
        }
}


DynamicArray::DynamicArray(const DynamicArray& x) {
    size = x.size;
    line = new double[size  + RESERVE];
    for (unsigned int number = 0; number < x.size + RESERVE; number++){
        line[number] = x.line[number];
    }
}


DynamicArray::DynamicArray(DynamicArray &&x) {
    size = x.size;
    line = x.line;
    x.size = 0;
    x.line = nullptr;
}


DynamicArray::~DynamicArray() {
    delete[] line;
}
inline bool DynamicArray:: is_empty (){
    return sp == -1;
}

inline bool DynamicArray:: is_full (){
    return sp == size - 1;
}


/*
void DynamicArray::push(double X, unsigned int  place) {

   if (is_full());
  double help, help2 = line[place];
  for (unsigned int num_1 = place +1 ; num_1 < (size); num_1 ++) {
        help = line[num_1];
        line[num_1] = help2;
        help2 = help;
    }
    line[place] = X;
}
*/


void DynamicArray::push(double item, unsigned int  place) {
    line[place] = item;
}


void DynamicArray::push(double item) {
    if (is_full()) {
        try{ throw Overflow;}
        catch (DynamicArrayException error){ error.set_mistake(1);}
    }
    line[++sp] = item;
}


unsigned int DynamicArray:: search (double item){
    for (unsigned int number = 0; number <= sp  ; number ++){
        if (  abs(line[number] - item) < E ){
            return number;
        }
    }
    return size + 10;
}


void DynamicArray:: pop (double item) {
    if (is_empty()) {
        try{ throw Underflow;}
        catch (DynamicArrayException error){ error.set_mistake(2);}
    }
    unsigned int place = search(item);
    if ( place > size) return;
    double help, help2= line[place+1];
    for (unsigned int num_1 = place+1  ; num_1 <= (sp); num_1 ++) {
        help = line[num_1+1];
        line[num_1-1] = help2;
        help2 = help;
    }
    sp--;
}


void DynamicArray::print (){
    for (unsigned int number = 0; number <= sp; number++){
        std::cout << line[number] << "  ";
    }
    std::cout << "\n";
}

int main() {
    DynamicArray A = DynamicArray{4};

    A.push(111.00);
    A.push(2.00);
    A.push(3.00);
    A.push(44.00);
    A.push(555.00);
    A.push(6.00);
    A.print();


    A.push(4.00, 3);
    A.push(5.00, 4);
    A.push(1.00, 0);
    A.print();

    A.pop (1.00);
    A.pop (4.00);
    A.pop (6.00);
    A.print();

    A.pop (6.00);
    A.pop (1.00);
    A.pop (4.00);
    A.pop (3.00);
    A.print();

    A.push(6.00);
    A.push(7.00);
    A.push(8.00);
    A.push(9.00);
    A.print();

    A.push(999.00);
    return 0;
}
