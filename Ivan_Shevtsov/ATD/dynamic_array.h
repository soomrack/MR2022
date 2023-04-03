#ifndef ATD_DYNAMIC_ARRAY_H
#define ATD_DYNAMIC_ARRAY_H

#include <iostream>

namespace DynArr_names {
    class dynamic_array_exceptions : public std::domain_error {
    public:
        dynamic_array_exceptions(const char *massage) : std::domain_error(massage) {}
    };

    dynamic_array_exceptions OUT_OF_THE_RANGE("index out of the range");
    dynamic_array_exceptions ARRAY_EMPTY("array is empty");
    dynamic_array_exceptions FILL_EMPTY("can`t fill zero size array");
    dynamic_array_exceptions FILLED_WARNING("[WARNING] array is filled. Last value was added. "
                                            "If you want to add more value use resize(new_size).");

    class dynamic_array {
    private:
        unsigned size;
        int *data;
        unsigned filled_size;
    public:
        unsigned buf_size;

        inline dynamic_array();
        dynamic_array(const unsigned size, unsigned buf_size = 50);
        dynamic_array(const dynamic_array &other);
        dynamic_array(dynamic_array &&other) noexcept ;
        ~dynamic_array();

        void push_back(const int value);
        void pop_back();

        dynamic_array &operator=(const dynamic_array &other);
        bool operator==(const dynamic_array &other);
        bool operator!=(dynamic_array &other);
        int &operator[](unsigned idx);

        void resize(unsigned new_size, unsigned new_buff_size = 50);
        int find(int element);  // return index first equal element
        void fill_random(int MAX_RANDOM_VALUE = 100);
        void show();
        int get_size();
    };
}

#endif //ATD_DYNAMIC_ARRAY_H
