#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <exception>

class Dynamic_array {
protected:
    unsigned int size;
    double* line;
    int sp;

public:

// Конструкторы и деструкторы класса
    Dynamic_array();  // условный конструктор ( с пустыми параметрами)
    Dynamic_array( const unsigned int number); // конструктор с одним параметром
    Dynamic_array(const Dynamic_array& A);  // оператор копирования
    Dynamic_array(Dynamic_array&& A);  // оператор переноса
    ~Dynamic_array();  // деструктор


// Методы
    void push_beginning_replace (double);
    void push_middle_replace (double, int);
    void print();
    void search_and_replace (double, double);
    Dynamic_array delet (double);
    bool isFull();
    void push_beginning_move (double);
    void push_middle_move (double, int);

    unsigned int getsize();

    double* getline();


    Dynamic_array& operator=(const Dynamic_array &x);
};

class Dynamic_array_Exception {
public:
    int kod_mistake;

    Dynamic_array_Exception();
    Dynamic_array_Exception(int kod_mistake);
    //~Matrix_Exception() ;

    void set_comment (int, double , int);
};
Dynamic_array_Exception comment;

//Операторы класса иcключений
Dynamic_array_Exception:: Dynamic_array_Exception(){
    kod_mistake = 999;
}


Dynamic_array_Exception:: Dynamic_array_Exception(int kod){
    kod_mistake = kod;
}


void Dynamic_array_Exception::set_comment (int comment, double push_delet, int place ){
    switch (comment) {
        case 1:
            std::cout << "\n"<< "       You added to the beginning with replacement "<< push_delet<< "\n";
            break;
        case 2:
            std::cout<< "\n" << "       You have added  with replacement "<< push_delet << " to the position "<<place<< "\n";
            break;
        case 3:
            std::cout<< "\n" << "       You added to the beginning with a shift "<<push_delet<< "\n";
            break;
        case 4:
            std::cout<< "\n" << "       You have added with a shift "<< push_delet << " to the position "<<place<< "\n";
            break;
        case 5:
            std::cout<< "\n" << "       You have found  "<<push_delet << " and replaced with "<<place<< "\n";
            break;
        case 6:
            std::cout<< "\n" << "       You deleted  "<<push_delet << "\n";
            break;
        default:
            std::cout << "       Unknown error \n";
    }
}








unsigned int Dynamic_array::getsize() {
    return (size);
}


double* Dynamic_array::getline(){
    return (line);
}
Dynamic_array::Dynamic_array() {
    size = 0;
    sp = 0;
    line = nullptr;

}


Dynamic_array& Dynamic_array::operator=(const Dynamic_array &x) {
    if (this != &x){
        if (!line)
            delete[] line;

        size = x.size;


        this->line = new double[size];
        for (unsigned int number = 0; number < size; number++){
            line[number] = x.line[number];
        }
    }

    return *this;
}


Dynamic_array::Dynamic_array(const unsigned int number) {
    size = number;
    line = new double[size];
    sp = - 1;

}


Dynamic_array::Dynamic_array(const Dynamic_array& x) {
    size = x.size;
    sp = x.sp;
    line = new double[size];
    for (unsigned int number = 0; number < x.size; number++){
        line[number] = x.line[number];
    }
}


Dynamic_array::Dynamic_array(Dynamic_array &&x) {
    size = x.size;
    line = x.line;
    sp = x.sp;
    x.sp = 0;
    x.size = 0;
    x.line = nullptr;
}


Dynamic_array::~Dynamic_array() {
    delete[] line;
}

void Dynamic_array:: push_beginning_replace (double X){
    if (isFull()) {
        std::cout  << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    line[++sp] = X;
    comment.set_comment(1,X, 0);

}


void Dynamic_array::push_middle_replace(double X, int place) {

    for ( unsigned int number = 0; number <= size; number ++) {
        if ( place == number) line[number] = X;
    }
    comment.set_comment(2,X, place);
}




bool Dynamic_array::isFull() {
    return sp == size - 1;

}
void Dynamic_array::print (){
    for (unsigned int number = 0; number < size; number++){
        std::cout << line[number] << "  ";
    }
    std::cout << "\n";
}

void Dynamic_array:: push_beginning_move (double X){
    double* help = new double[size];
    help[0] = X;
    for (unsigned int number = 0; number < size - 1; number ++){
        help[number+1] = line [number];
    }
    line = help;
    comment.set_comment(3,X, 0);
}


void Dynamic_array::push_middle_move(double X, int place) {
    if ( place >= size) return;
    double* help = new double[size];
    int t=0;
    for (unsigned int number = 0; number < size  ; number ++){
        if ( number == place ){
            t=1;
            help[number] = X;
            continue;
        }
        help[number ] = line [number-t];
    }
    line = help;
    comment.set_comment(4,X, place);
}

void Dynamic_array:: search_and_replace (double search, double replace){
    for (unsigned int number = 0; number <= size  ; number ++){
        if ( line[number] == search ){
            line[number] = replace;
            comment.set_comment(5,search, replace);
            return;
        }
    }

}

Dynamic_array Dynamic_array:: delet (double X) {
    Dynamic_array help = {size - 1};
    int t=0;
    for (unsigned int number = 0; number < size  ; number ++){
        if ( line[number] == X ){
            t=1;
        }
        help.line[number] = line [number+t];
    }
    comment.set_comment(6,X, 0);
    return help;


}


int main() {
    Dynamic_array A = {7};
    A.getline()[0]= 0.00;
    for (int i = 1; i < A.getsize(); i ++){
        A.getline()[i] = A.getline()[i-1] +1.00 ;
    }

    A.print();


    A.push_beginning_replace(77.00);
    A.push_middle_replace(111.00, 4);

    A.print();
    A.push_beginning_move(55.00);

    A.print();
    A.push_middle_move(222.00, 5);

    A.print();
    A.push_middle_move(45.00, 3);

    A.print();
    A.search_and_replace(1.00, 5.23);

    A.print();

    A.delet(45).print();





}