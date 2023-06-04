#ifndef MR2022_DARRAYTEST_H
#define MR2022_DARRAYTEST_H

#include <list>
#include <array>
#include "DArray.h"


template<typename T>
class DArrayTest {
private:
    inline static std::list<T> test_list = {2, 8, 1, 3};
    inline static std::array<T,4> true_array0 = {3, 9, 2, 4};
    inline static std::array<T, 3> true_array1 = {2, 8, 1};
    inline static std::array<T, 5> true_array2 = {2, 8, 1, 3, 5};

public:
    static void overload_test();
    static void resize_test();
    static void full_test();
};


#endif //MR2022_DARRAYTEST_H
