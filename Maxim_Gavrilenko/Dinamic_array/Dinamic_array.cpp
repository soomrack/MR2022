#include <iostream>

class dynamic_array {
protected:
    unsigned int size;
    double* arr;


public:
    dynamic_array();
    dynamic_array(const unsigned int);
    dynamic_array(const dynamic_array& A);
    dynamic_array(dynamic_array&& A) noexcept;
    ~dynamic_array();

    void resize(unsigned int);
    void replace (double, double);
    void insert (double, int);
    bool search (double);
    unsigned int lenght();
    void print();
    dynamic_array& operator=(const dynamic_array& A);
};

dynamic_array::dynamic_array() {
    arr = nullptr;
    size = 0;
}

dynamic_array::dynamic_array(const unsigned int number) {
    size = number;
    arr = new double [size];
}

dynamic_array::dynamic_array(const dynamic_array &array) : size(array.size) {
    this->arr = new double [this->size];
    if (!arr) throw std::bad_alloc();
    memcpy(arr,array.arr,sizeof(double)*array.size);
}

dynamic_array::dynamic_array(dynamic_array&& array) noexcept : size(array.size), arr(array.arr) {
    array.size = 0;
    array.arr = nullptr;
}

dynamic_array::~dynamic_array() {
    size = 0;
    delete arr;
}

dynamic_array& dynamic_array::operator=(const dynamic_array& A) {
    if(this!=&A)
        if(!arr) delete arr;
    size = A.size;
    arr = new double [size];
    memcpy(arr,A.arr, size * sizeof(double));
    return *this;
}

bool dynamic_array::search(double num) {
    for(unsigned int i = 0; i < size; i++) {
        if (arr[i] == num) return true;
    }
    return false;
}

void dynamic_array::resize(unsigned int new_size) {
    auto* new_data = new double[new_size];
    memcpy(new_data,arr,sizeof(double) * new_size);
    size = new_size;
    delete arr;
    arr = new_data;
}

void dynamic_array::replace(double num, double den) {
    for (unsigned int i = 0; i < size; i++) {
        if (arr[i] == num) {
            arr[i] = den;
        }
    }
}

void dynamic_array::insert(double num, int place) {
    if (size == 0){
        arr = new double [size + 1];
        arr[size] = num;
        size++;
    }
    if (place >= size) return;
    double* temp = new double[size + 1];
    int shift = 0;
    for (unsigned int i = 0; i <= size ; i ++){
        if (i == place){
            shift = 1;
            temp[i] = num;
            break;
        }
        temp[i] = arr [i - shift];
    }
    arr = temp;
    size++;
}


void dynamic_array::print () {
    for (unsigned int number = 0; number < size; number++){
        std::cout << arr[number] << "  ";
    }
    std::cout << "\n";
}

unsigned int dynamic_array::lenght() {return size;}

int main() {
    dynamic_array A;
    A.insert(1.90, 1);
    A.insert(2.032, 0);
    A.insert(6.011, 1);
    A.insert(34.05, 1);
    A.insert(7.04, 3);
    A.insert(98.06, 0);
    A.insert(4.08, 5);
    A.print();
    std::cout << A.lenght() << std::endl;
    A.replace(1.90, 3);
    A.print();
    A.search(4.08) ? std::cout << "YES" : std::cout << "NO";
    std:: cout << std::endl;
    A.resize(4);
    A.print();
    A.resize(10);
    A.print();
    return 0;
}