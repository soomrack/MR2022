#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// класс динамического массива - шаблонный класс
template<class T>
class DynamicArray {
private:
    T *data_;               // тип данных, хранящихся в массиве
    size_t size_;           // кол-во элементов, помещённых в массив
    size_t capacity_;       // максимально допустимый размер массива
public:
    // конструктор без параметров
    DynamicArray() {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    };

    // конструктор с параметром (capacity)
    DynamicArray(int capacity) {
        if (capacity == 0) {
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            return;
        }
        size_ = 0;
        capacity_ = capacity;
        data_ = new T[capacity_];
    };

    // конструктор копирования
    DynamicArray(DynamicArray<T> &vector) {
        if (vector.capacity_ == 0) {
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
            return;
        }
        size_ = vector.size_;
        capacity_ = vector.capacity_;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = vector.data_[i];
        }
    };

    //деструктор
    ~DynamicArray() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    };

    // метод, возвращающий кол-во помещённых элементов в массив
    size_t size() {
        return size_;
    };

    // метод укорачивания максимально возможного количества элементов в массиве
    void shrink(int k) {
        if (capacity_ - k >= 0) {
            capacity_ -= k;
            if (capacity_ < size_) {
                size_ = capacity_;
            }
        } else {
            capacity_ = 0;
            size_ = 0;
        }

    };

    // метод увеличения максимального количества элементов в массиве
    void expand(int k) {
        T *temp = new T[size_];
        for (int i = 0; i < size_; ++i)
            temp[i] = data_[i];
        capacity_ += k;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = temp[i];
        }
    };

    // метод добавления элемента в конец массива
    // О(1), если capacity > size
    void push_tail(const T &item) {
        if (size_ == capacity_) {
            expand(capacity_ + 1);
        }
        data_[size_] = item;
        size_++;
    };

    // метод добавления элемента в начало массива
    void push_head(const T &item) {
        T *temp = new T[size_ + 1];
        temp[0] = item;
        for (int i = 0; i < size_; ++i)
            temp[i + 1] = data_[i];

        if (size_ == capacity_) {
            capacity_ += capacity_ + 1;
        }
        size_++;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = temp[i];
        }
    };

    //оператор индексирования
    T &operator[](const size_t index) {
        try {
            // если пытаемся достать что-то по индексу, превышающему кол-во элементов в массиве,
            // то генерируем исключение Invalid index
            if (index >= size_) {
                throw "Invalid index";
            }
        }
        catch (std::string error) {
            std::cerr << error;
            exit(-1);
        }
        return data_[index];
    };

    // оператор копирующего присваивания
    DynamicArray<T> &operator=(const DynamicArray &vector) {
        if (this == &vector) {
            return *this;
        }
        if (data_ != nullptr) {
            delete[] data_;
        }
        size_ = vector.size_;
        capacity_ = vector.capacity_;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = vector.data_[i];
        }
        return *this;
    };

    void print(std::ostream &out) const {
        for (size_t i = 0; i < size_; i++)
            out << data_[i] << '\t';
    };
};

#endif
