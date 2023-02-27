#ifndef MR2022_DARRAYTEST_H
#define MR2022_DARRAYTEST_H

#include <vector>
#include "DArray.h"


template<typename T>
class DArrayTest {
private:
    inline static std::vector<T> vector1 = {2, 8, 1, 3};
    inline static std::vector<T> vector2 = {4, 9, 21, 13};
    inline static std::vector<T> vector3 = {2, 2, 2, 2};
public:
    void general_test();



};


#endif //MR2022_DARRAYTEST_H
