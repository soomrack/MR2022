#include <iostream>
#include <cstring>

template<typename T>
class DM {
protected:
    unsigned int size;
    T *value;
public:
    DM(T X, unsigned int n);
    DM(const DM<T> &copy);
    ~DM();
    static void Arr_print(const DM<T> &Array);
    T get(unsigned int id);
    void set(unsigned int id, T number);
    void resize(unsigned int newsize);
};

template<typename T>  // Конструктор создания массива
DM<T>::DM(T X, unsigned int n){
    size = n;
    value = new T[size];
    for (unsigned int idx = 0; idx < size; idx ++){
        value[idx] = X;
    }
}

template<typename T>
void DM<T>::Arr_print(const DM<T> &Array){
    for (unsigned int idx = 0; idx < Array.size; idx++){
        std::cout << Array.value[idx] << ' ';
    }
    std::cout << std::endl;
}

template<typename T>
DM<T>::DM(const DM<T> &copy) {
    size = copy.size;
    value = new T[size];
    memcpy(value, copy.value, sizeof(T) * size);
}

template<typename T>
DM<T>::~DM() {
    delete[] value;
}

template<typename T>
T DM<T>::get(unsigned int id){
    return value[id];
}

template<typename T>
void DM<T>::set(unsigned int id, T number){
    value[id] = number;
}

template<typename T>
void DM<T>::resize(unsigned int newsize){
    size = newsize;
    T *Parasite = value;
    value = new T[size];
    value = Parasite;
}

int main() {
    DM<double> ar(1,3);
    DM<double>::Arr_print(ar);
    double Aim = ar.get(2);
    std::cout << Aim << std::endl;

    ar.set(2,3.21);
    double Aim1 = ar.get(2);
    std::cout << Aim1 << std::endl;

    DM<double>::Arr_print(ar);

    ar.resize(5);
    DM<double>::Arr_print(ar);

    return 0;
};

// Надо написать get(узнать значение элемента), set(изменить значение элемента), resize (изменить размер массива)
