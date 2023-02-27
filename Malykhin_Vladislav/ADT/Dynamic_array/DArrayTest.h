#ifndef MR2022_DARRAYTEST_H
#define MR2022_DARRAYTEST_H

#include <vector>
#include "DArray.h"


template<typename T>
class DArrayTest {
private:
    inline static std::vector<T> test_vector = {2, 8, 1, 3};
    inline static std::vector<T> true_vector0 = {3, 9, 2, 4};
    inline static std::vector<T> true_vector1 = {2, 8, 1};
    inline static std::vector<T> true_vector2 = {2, 8, 1, 3, 5};
public:
    static void set_test();
    static void resize_test();
    static void full_test();
};


#endif //MR2022_DARRAYTEST_H
