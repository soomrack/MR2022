#include "DArrayTest.h"



template<typename T>
void DArrayTest<T>::overload_test() {
    std::cout << "Testing overload:\n";
    int flag_counter = 0;
    DArray<T> dArray1(DArrayTest::test_list);
    std::cout << "Test value\t True value\tflag \n";
    for (int id = 0; id < dArray1.get_size(); ++id) { // цикл увеличивает все значения массива на 1 и проверяет соответствие
        ++dArray1[id];
        int flag = 0;
        if(dArray1[id] != DArrayTest::true_array0[id]) {
            flag = 1;
            ++flag_counter;
        }
        std::cout << dArray1[id] << "\t \t " << true_array0[id] << "\t\t"<< flag << "\n";
    }
    std::cout << "Flag counter value = " << flag_counter << "\n\n";
}


template<typename T>
void DArrayTest<T>::resize_test() {
    std::cout << "Testing resize method (size decreased):\n";
    int flag_counter = 0;
    DArray<T> dArray1(DArrayTest::test_list); // проверка уменьшения размера массива
    dArray1.resize(dArray1.get_size() - 1);
    std::cout << "Test value \t True value \tflag \n";
    for (int id = 0; id < dArray1.get_size(); ++id) { // проверяет соответствие значений массива
        int flag = 0;
        if(dArray1[id] != DArrayTest::true_array1[id]) {
            flag = 1;
            ++flag_counter;
        }
        std::cout << dArray1[id] << "\t \t " << true_array1[id] << "\t\t"<< flag << "\n";
    }
    std::cout << "Flag counter value = " << flag_counter << "\n\n";
    std::cout << "Testing resize method (size increased):\n";
    flag_counter = 0;
    DArray<T> dArray2(DArrayTest::test_list); // проверка увеличения размера массива
    dArray2.resize(dArray2.get_size() + 1);
    dArray2[dArray2.get_size() - 1] = 5;
    std::cout << "Test value \t True value \tflag \n";
    for (int id = 0; id < dArray2.get_size(); ++id) { // проверяет соответствие значений массива
        int flag = 0;
        if(dArray2[id] != DArrayTest::true_array2[id]) {
            flag = 1;
            ++flag_counter;
        }
        std::cout << dArray2[id] << "\t \t " << true_array2[id] << "\t\t"<< flag << "\n";
    }
    std::cout << "Flag counter value = " << flag_counter << "\n\n";
}




template<typename T>
void DArrayTest<T>::full_test() {
    DArrayTest<T>::overload_test();
    DArrayTest<T>::resize_test();
}


template class DArrayTest<int>;
template class DArrayTest<double>;
template class DArrayTest<float>;