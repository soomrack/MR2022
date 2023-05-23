#ifndef MR2022_DYNAMIC_ARRAY_H
#define MR2022_DYNAMIC_ARRAY_H

#include <algorithm>
#include <cstring>
class ARRAY_EXCEPTION: public std::domain_error
{
public:
    explicit ARRAY_EXCEPTION(const char* const str): std::domain_error(str) {};
};

ARRAY_EXCEPTION BADALLOC("Memory is not allocated");
ARRAY_EXCEPTION OUTOFRANGE("Out of range");
ARRAY_EXCEPTION NOTFOUND("Value is not found in this scope");


template <typename T>
class dynamic_array {
protected:
    size_t capacity;                                            // емкость массива
    size_t size;                                                // текущий размер массива;
    T* data;                                                    // указатель на массив элементов
    size_t resize_array = 100;

public:
    

    dynamic_array();                                            // конструктор по умолчанию, который инициализирует поля data, capacity и size нулевыми значениями
    explicit dynamic_array(unsigned int);                       // конструктор с заданной емкостью 
    dynamic_array(const dynamic_array& A);                      // конструктор копирования
    dynamic_array(dynamic_array&& A) noexcept;                  // конструктор переноса
    ~dynamic_array();                                           // деструктор

    T& operator[](unsigned);                                     // оператор индексации, который возвращает ссылку на элемент массива по указанному индексу

    void resize(unsigned int);                                  // метод, который изменяет емкость массива
    void insert (T, unsigned int, size_t resize_array);         // метод, который вставляет элемент в массив по указанному индексу
    void append (T);                                            // метод, который добавляет элемент в конец массива
    void remove(unsigned int);                                  // // метод, который удаляет элемент из массива по указанному индексу
    int search(T);                                              // метод, который ищет элемент в массиве и возвращает его индекс

    unsigned int get_size() {return size;}                      // возвращает текущей размер массива
    unsigned int get_capacity() {return capacity;}              // возвращает полную емкость


};

template <typename T>
dynamic_array<T>::dynamic_array() {
    data = nullptr;
    capacity = 0;
    size = 0;
}

template <typename T>
dynamic_array<T>::dynamic_array(const unsigned int value) {
    capacity = value;
    size = 0;
    data = new T [capacity];
    if (!data) throw BADALLOC;
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &array) : capacity(array.capacity), size(array.size) {
    this->data = new T[this->size];
    if (!data) throw BADALLOC;
    memcpy(data,array.data,sizeof(T)*array.size);
}

template <typename T>
dynamic_array<T>::dynamic_array(dynamic_array&& array) noexcept : capacity(array.capacity), 
size(array.size), data(array.data) {
    array.size = 0;
    array.capacity = 0;
    array.data = nullptr;
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
    size = 0;
    capacity = 0;
    if (data) {
        delete data;
    }
    
}

template <typename T>
int dynamic_array<T>::search(T num) {
    for(unsigned int i = 0; i < size; i++) {
        if (data[i] == num) return i;
    }
    throw NOTFOUND;
}


template <typename T>
void dynamic_array<T>::insert(T value, unsigned int idx, size_t resize_array) {
    if (idx > capacity) throw OUTOFRANGE ;
    if (size == capacity) resize(capacity * resize_array); // В случае конца массива, емкость расширяется в два раза //
    std::copy(data + idx, data + size, data + idx + 1);
    data[idx] = value;
    size++;
}

template<typename T>
T& dynamic_array<T>::operator[](const unsigned int idx) {
    return data[idx];
}

template <typename T>
void dynamic_array<T>::resize(unsigned int new_size) {
    if (new_size < size) {
        size = new_size;
    }
    capacity = new_size;
    auto* new_data = new T[capacity];
    memcpy(new_data, data, sizeof(T) * size);
    delete data;
    data = new_data;
}

template<typename T>
void dynamic_array<T>::append(T new_data) {
	if(size >= capacity){
		resize(size+10);
	}
	data[size++] = new_data;
}

template<typename T>
void dynamic_array<T>::remove(unsigned int idx) {
	if(idx < 0){
		throw OUTOFRANGE;
	}
	size -= 1;
	memcpy(data + idx, data + idx + 1, (size - idx + 1) * sizeof(T));
}
#endif //MR2022_DYNAMIC_ARRAY_H
