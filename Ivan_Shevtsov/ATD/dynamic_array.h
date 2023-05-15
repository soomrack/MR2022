#ifndef ATD_DYNAMIC_ARRAY_H
#define ATD_DYNAMIC_ARRAY_H
#include <iostream>

namespace DynArr_names {
    /**
    * @brief myDynamicArray container
    *
    * use try/catch for work with DynamicArray
    *
    * @class dynamic_array_exceptions has these exceptions(objects):
    *
    * @objects dynamic_array_exceptions OUT_OF_THE_RANGE("index out of the range");
    * @objects dynamic_array_exceptions ARRAY_EMPTY("array is empty");
    * @objects dynamic_array_exceptions FILL_EMPTY("can`t fill zero size array");
    * @objects dynamic_array_exceptions FILLED_WARNING("[WARNING] array is filled. Last value was added.
    *                                                   "If you want to add more value use resize(new_size).");
    */

    class dynamic_array_exceptions : public std::domain_error {
    public:
        dynamic_array_exceptions(const char *massage) : std::domain_error(massage) {}
    };

    template<typename T>
    class dynamic_array {
    private:
        unsigned size;
        T *data;
        unsigned filled_size;
    public:
        unsigned buf_size;

        dynamic_array();
        dynamic_array(const unsigned size, unsigned buf_size = 50);
        dynamic_array(const dynamic_array &other);
        dynamic_array(dynamic_array &&other) noexcept;

        ~dynamic_array();

        void push_back(const T value);
        void pop_back();
        dynamic_array &operator=(const dynamic_array &other);
        bool operator==(const dynamic_array &other);
        bool operator!=(dynamic_array &other);

        T &operator[](unsigned idx);
        void resize(unsigned new_size, unsigned new_buff_size = 50);

        int find(T element);  // return index first equal element
        void fill_random_int(int MAX_RANDOM_VALUE = 100);

        void show();
        int get_size();
    };

    template<typename T>
    dynamic_array<T>::dynamic_array() {
        size = 0;
        buf_size = 50;
        data = new T[size + buf_size];
        filled_size = 0;
    }

    template<typename T>
    dynamic_array<T>::dynamic_array(const unsigned size, unsigned buf_size) {
        this->size = size;
        this->buf_size = buf_size;
        data = new T[size + buf_size];
        filled_size = 0;
    }

    template<typename T>
    dynamic_array<T>::dynamic_array(const dynamic_array &other) {
        size = other.size;
        buf_size = other.buf_size;
        filled_size = other.filled_size;
        data = new T[size + buf_size];
        for (unsigned idx = 0; idx < (size + buf_size); idx++) {
            data[idx] = other.data[idx];
        }
    }

    template<typename T>
    dynamic_array<T>::dynamic_array(dynamic_array &&other) noexcept {
        size = other.size;
        buf_size = other.buf_size;
        data = other.data;
        filled_size = other.filled_size;

        other.filled_size = 0;
        other.buf_size = 0;
        other.size = 0;
        other.data = nullptr;
    }

    template<typename T>
    dynamic_array<T> &dynamic_array<T>::operator=(const dynamic_array &other) {
        if (other.data != nullptr) {
            delete[] this->data;
        }
        filled_size = other.filled_size;
        buf_size = other.buf_size;
        size = other.size;
        data = new T[size + buf_size];
        for (unsigned idx = 0; idx < (size + buf_size); idx++) {
            this->data[idx] = other.data[idx];
        }

        return *this;
    }

    template<typename T>
    bool dynamic_array<T>::operator==(const dynamic_array &other) {
        if (other.size != size or other.filled_size != filled_size)
            return false;
        if (other.data == nullptr && data == nullptr)
            return true;

        for (unsigned idx = 0; idx < size; idx++) {
            if (other.data[idx] != data[idx])
                return false;
        }
        return true;
    }

    template<typename T>
    bool dynamic_array<T>::operator!=(dynamic_array &other) {
        return !(other == *this);
    }

    template<typename T>
    T &dynamic_array<T>::operator[](unsigned idx) {
        if (data == nullptr) {
            dynamic_array_exceptions ARRAY_EMPTY("array is empty");
            throw ARRAY_EMPTY;
        }
        if (idx > size + buf_size) {
            dynamic_array_exceptions OUT_OF_THE_RANGE("index out of the range");
            throw OUT_OF_THE_RANGE;
        }

        return data[idx];
    }

    template<typename T>
    int dynamic_array<T>::find(T element) {
        for (unsigned idx = 0; idx < size; idx++)
            if (data[idx] == element)
                return idx;
        return -1;
    }

    template<typename T>
    void dynamic_array<T>::fill_random_int(int MAX_RANDOM_VALUE) {
        if (typeid(T) != typeid(int)){
            dynamic_array_exceptions FILL_EMPTY("type fill error");
        }
        if (size == 0) {
            dynamic_array_exceptions FILL_EMPTY("can`t fill zero size array");
            throw FILL_EMPTY;
        } else {
#ifndef DEBUG
            srand(time(0));
#endif
#ifdef DEBUG
            srand(42);
#endif
            for (unsigned idx = 0; idx < size; idx++) {
                data[idx] = rand() % (MAX_RANDOM_VALUE + 1);
            }
            filled_size = size;
        }
    }

    template<typename T>
    void dynamic_array<T>::show() {
        if (size == 0)
            std::cout << "array is empty" << std::endl;

        else {
            for (unsigned idx = 0; idx < filled_size; idx++) {
                std::cout << data[idx] << "\t";
            }
            std::cout << "\n";
        }
    }

    template<typename T>
    void dynamic_array<T>::push_back(const T value) {
        if (filled_size == size + buf_size) {
            T *tmp_arr = new T[size + buf_size + buf_size];
            for (unsigned idx = 0; idx < size; idx++) {
                tmp_arr[idx] = data[idx];
            }
            tmp_arr[size] = value;
            delete[] data;
            data = tmp_arr;
            dynamic_array_exceptions FILLED_WARNING("[WARNING] array is filled. Last value was added. "
                                                    "If you want to add more value use resize(new_size).");
            throw FILLED_WARNING;
        } else {
            data[filled_size] = value;


        }
        size++;
        filled_size++;
    }

    template<typename T>
    void dynamic_array<T>::pop_back() {
        if (filled_size == size + buf_size) {
            T *tmp_arr = new T[size - 1];
            for (unsigned idx = 0; idx < size - 1; idx++) {
                tmp_arr[idx] = data[idx];
            }
            filled_size--;

            delete[] data;
            data = tmp_arr;
        } else {
            filled_size--;
        }

    }

    template<typename T>
    int dynamic_array<T>::get_size() {
        return size;
    }

    template<typename T>
    dynamic_array<T>::~dynamic_array() {
        filled_size = 0;
        buf_size = 0;
        size = 0;
        if (data != nullptr) {
            delete[] data;
        }
    }

    template<typename T>
    void dynamic_array<T>::resize(unsigned new_size, unsigned new_buff_size) {
        size = new_size;
        buf_size = new_buff_size;
        if (data != nullptr) {
            delete[] data;
        }
        data = new T[size + buf_size];
    }


}
#endif //ATD_DYNAMIC_ARRAY_H
