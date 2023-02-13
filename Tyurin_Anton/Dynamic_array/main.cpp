#include <iostream>

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
    static DM<T> push_head(T number);
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
DM<T> DM<T>::push_head(T number){
    DM<T> Parasite(*this);
    Array.size = Array.size + 1;
    delete[] Array.value;
    Array.value = new T[Array.size];
    for (unsigned int idx = 1; idx < Array.size; idx++){
        Array.value[idx] = Parasite.value[idx - 1];
    }
    Array.value[0] = number;
    delete[] Parasite.value;
return Array;
}

int main() {
    DM<double> ar(1,3);
    DM<double>::Arr_print(ar);
    //DM<double>::push_head(ar,2);
    DM<double>::Arr_print(ar);

    return 0;
};

// Надо написать get(узнать значение элемента), set(изменить значение элемента), resize (изменить размер массива)
