#include <iostream>
#include <stdexcept>
#include <string>

class Dyn_array_exception: public std::logic_error
{
public:
    explicit Dyn_array_exception(const std::string& message):
            std::logic_error(message)
    {}
};

template <typename T>
class Dynamic_array {
public:
    Dynamic_array();
    explicit Dynamic_array(unsigned long int length);
    Dynamic_array(unsigned long int length, const T data[]);
    Dynamic_array(const Dynamic_array&);
    ~Dynamic_array();

    void shrink(unsigned int constriction);
    void expand(unsigned int extension);

    Dynamic_array& operator=(const Dynamic_array&);
    // TODO: конструктор перемещения и оператор перемещающего присваивания

    T& operator[](unsigned long int num);
    bool operator==(const Dynamic_array&);
    bool operator!=(const Dynamic_array& other) {return !(this == other);}

    unsigned long int get_length() const {return length;}
    void print();

    void push_head(T elem);
    void push_tail(T elem);
    void pop_head();
    void pop_tail();

private:
    unsigned long int length;
    T* data;

    void clear();
};

template <typename T>
Dynamic_array<T>::Dynamic_array():
    length(0)
{
    this->data = nullptr;
}

template <typename T>
Dynamic_array<T>::Dynamic_array(unsigned long int length):
    length(length)
{
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = 0;
    }
}

template <typename T>
Dynamic_array<T>::Dynamic_array(const unsigned long int length, const T data[]):
    length(length / sizeof data[0])
{
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = data[idx];
    }
}

template<typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array& other):
        length(other.length)
{
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = other.data[idx];
    }
}

/* template<typename T>
Dynamic_array<T>::Dynamic_array(Dynamic_array&& other) noexcept:
    length(other.length)
{
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = other.data[idx];
    }
    delete[] other.data;
} */

template<typename T>
Dynamic_array<T> &Dynamic_array<T>::operator=(const Dynamic_array& other) {
    if (this == &other) {
        return *this;
    }
    Dynamic_array temp(other);
    std::swap(this->length, temp.length);
    std::swap(this->data, temp.data);
    return *this;
}

/* template<typename T>
Dynamic_array<T> &Dynamic_array<T>::operator=(Dynamic_array&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    swap(other);
    return *this;
} */

template <typename T>
Dynamic_array<T>::~Dynamic_array() {
    delete[] this->data;
}

template <typename T>
void Dynamic_array<T>::print() {
    for (size_t idx = 0; idx < this->length; idx++) {
        std::cout << this->data[idx] << '\t';
    }
    std::cout << std::endl;
}

template <typename T>
void Dynamic_array<T>::shrink(unsigned int constriction) {
    if (constriction >= this->length) {clear(); return;}
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length -= constriction;
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = temp[idx];
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::expand(unsigned int extension) {
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length += extension;
    this->data = new T[this->length];
    for (size_t idx = 0; idx < (this->length - extension); idx++) {
        this->data[idx] = temp[idx];
    }
    for (size_t idx = (this->length - extension); idx < this->length; idx++) {
        this->data[idx] = 0;
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::push_head(T element) {
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length++;
    this->data = new T[this->length];
    this->data[0] = element;
    for (size_t idx = 1; idx < this->length; idx++) {
        this->data[idx] = temp[idx - 1];
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::push_tail(T element) {
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length++;
    this->data = new T[this->length];
    for (size_t idx = 0; idx < (this->length - 1); idx++) {
        this->data[idx] = temp[idx];
    }
    this->data[this->length - 1] = element;
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::pop_head() {
    if (this->length == 1) {clear(); return;}
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length--;
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = temp[idx + 1];
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::pop_tail() {
    if (this->length == 1) {clear(); return;}
    T *temp;
    temp = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        temp[idx] = this->data[idx];
    }
    delete[] this->data;
    this->length--;
    this->data = new T[this->length];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = temp[idx];
    }
    delete[] temp;
}

template<typename T>
T &Dynamic_array<T>::operator[](unsigned long int num) {
    if (num >= this->length) {
        throw Dyn_array_exception("Array out of bounds!");
    }
    return data[num];
}

template<typename T>
bool Dynamic_array<T>::operator==(const Dynamic_array& other) {
    if (this == &other) {
        return true;
    }
    if (this->length != other.length) {
        return false;
    }
    for (size_t idx = 0; idx < this->length; idx++) {
        if (std::abs(this->data[idx] - other.data[idx]) > 0.000001) {
            return false;
        }
    }
    return true;
}

template<typename T>
void Dynamic_array<T>::clear() {
    this->length = 0;
    delete[] this->data;
    this->data = nullptr;
}

int main() {
    Dynamic_array<double> test;
    test.expand(10);
    for (size_t idx = 0; idx < 10; idx++) {
        test[idx] = (double)idx;
    }
    test.print();
    Dynamic_array<double> test2(test);
    test2.shrink(7);
    test2.print();
    test2.pop_tail();
    test2.pop_head();
    test2.print();
    double array[5] = {5, 4, 3, 2, 1};
    Dynamic_array<double> test3(sizeof array, array);
    test3.print();
    test3.push_head(6);
    test3.push_tail(0);
    test3.print();
    Dynamic_array<double> test4(4);
    printf("Length of the dynamic massive is %lu\n", test4.get_length());
    test4[5];
    return 0;
}
