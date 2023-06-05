#include <iostream>
#include <stdexcept>
#include <string>

const unsigned int BASE_SIZE = 10;
const unsigned int BASE_BUFFER = 3;

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
    explicit Dynamic_array(unsigned long int length, unsigned int buffer);
    Dynamic_array(unsigned long int length, const T data[]);
    Dynamic_array(unsigned long int length, const T data[], unsigned int
    buffer);
    Dynamic_array(const Dynamic_array&);
    ~Dynamic_array();

    void shrink(unsigned int constriction);
    void expand(unsigned int extension);
    void shrink_buffer(unsigned int constriction);
    void expand_buffer(unsigned int extension);

    Dynamic_array& operator=(const Dynamic_array&);

    T& operator[](unsigned long int num);
    bool operator==(const Dynamic_array&);
    bool operator!=(const Dynamic_array& other) {return !(this == other);}

    void push_tail(T elem);
    void pop_tail();

    unsigned long int get_length() const {return length;}
    unsigned long int get_capacity() const {return capacity;}
    unsigned long int get_buffer() const {return buffer;}
    void print();

private:
    unsigned long int capacity;
    unsigned int buffer;
    unsigned long int length;
    T* data;

    void clear();
};

template <typename T>
Dynamic_array<T>::Dynamic_array():
    length(0),
    buffer(BASE_BUFFER),
    capacity(BASE_SIZE + BASE_BUFFER)
{
    this->data = new T[capacity];
}

template <typename T>
Dynamic_array<T>::Dynamic_array(unsigned long int length):
    length(0),
    buffer(BASE_BUFFER),
    capacity(length + BASE_BUFFER)
{
    this->data = new T[capacity];
}

template <typename T>
Dynamic_array<T>::Dynamic_array(unsigned long int length, unsigned int buffer):
    length(0),
    buffer(buffer),
    capacity(length + buffer)
{
    this->data = new T[capacity];
}

template <typename T>
Dynamic_array<T>::Dynamic_array(const unsigned long int length, const T data[]):
    length(length / sizeof data[0]),
    buffer(BASE_BUFFER)
{
    capacity = this->length + buffer;
    this->data = new T[capacity];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = data[idx];
    }
}

template <typename T>
Dynamic_array<T>::Dynamic_array(const unsigned long int length, const T
data[], unsigned int buffer):
    length(length / sizeof data[0]),
    buffer(buffer)
{
    capacity = this->length + buffer;
    this->data = new T[capacity];
    for (size_t idx = 0; idx < this->length; idx++) {
        this->data[idx] = data[idx];
    }
}

template<typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array& other):
        length(other.length),
        buffer(other.buffer),
        capacity(other.capacity)
{
    this->data = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        this->data[idx] = other.data[idx];
    }
}

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

template <typename T>
Dynamic_array<T>::~Dynamic_array() {
    clear();
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
    if (constriction > (capacity - length))
        throw Dyn_array_exception("Dynamic array is too short to shrink!");
    T *temp;
    temp = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        temp[idx] = data[idx];
    }
    delete[] data;
    capacity -= constriction;
    data = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        data[idx] = temp[idx];
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::expand(unsigned int extension) {
    T *temp;
    temp = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        temp[idx] = data[idx];
    }
    delete[] data;
    capacity += extension;
    length += extension;
    data = new T[capacity];
    for (size_t idx = 0; idx < (length - extension); idx++) {
        data[idx] = temp[idx];
    }
    for (size_t idx = (length - extension); idx < length; idx++) {
        data[idx] = 0;
    }
    delete[] temp;
}

template<typename T>
void Dynamic_array<T>::shrink_buffer(unsigned int constriction) {
    if ((constriction > (capacity - length)) || (constriction > buffer))
        throw Dyn_array_exception("Array buffer is too short to shrink!");
    T *temp;
    temp = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        temp[idx] = data[idx];
    }
    delete[] data;
    capacity -= constriction;
    buffer -= constriction;
    data = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        data[idx] = temp[idx];
    }
    delete[] temp;
}

template<typename T>
void Dynamic_array<T>::expand_buffer(unsigned int extension) {
    T *temp;
    temp = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        temp[idx] = data[idx];
    }
    delete[] data;
    capacity += extension;
    buffer += extension;
    data = new T[capacity];
    for (size_t idx = 0; idx < length; idx++) {
        data[idx] = temp[idx];
    }
    delete[] temp;
}

template <typename T>
void Dynamic_array<T>::push_tail(T element) {
    if (length == capacity)
        throw Dyn_array_exception("Dynamic array is overflow");
    data[length++] = element;
}

template <typename T>
void Dynamic_array<T>::pop_tail() {
    if (!length) throw Dyn_array_exception("Array is empty");
    data[length--] = 0;
}

template<typename T>
T &Dynamic_array<T>::operator[](unsigned long int num) {
    if (!length) throw Dyn_array_exception("Array is empty");
    if (num >= capacity) {
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
    length = 0;
    buffer = 0;
    capacity = 0;
    delete[] this->data;
}

int main() {
    int array[5] = {5, 4, 3, 2, 1};
    int array_2[5] = {1, 2, 3, 4, 5};
    Dynamic_array<int> test;
    Dynamic_array<int> test_2(5);
    Dynamic_array<int> test_3(5, 1);
    Dynamic_array<int> test_4(sizeof array, array);
    Dynamic_array<int> test_5(sizeof array_2, array_2, 2);
    test.push_tail(14);
    test.expand(3);
    test.print();
    test_4.expand_buffer(1);
    printf("Capacity of the array is %lu\n", test_4.get_capacity());
    printf("Length of the array is %lu\n", test_4.get_length());
    printf("Size of the array's buffer is %lu\n", test_4.get_buffer());
    test_5.print();
    test_5.pop_tail();
    test_5.shrink(2);
    test_5.print();
    test_5.shrink_buffer(2);
    return 0;
}
