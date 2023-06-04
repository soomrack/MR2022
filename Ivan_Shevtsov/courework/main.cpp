#include <iostream>

//Алгоритм Дейкстры, A*, Lee - использовать умные указатели, попробовать вообще не использовать сырых указателей
class Dijkstras_alg{
private:

public:


};


int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10};
    int a = 5;
    int* pa = &a;

    std::cout <<"value: " << *pa << " ref: " << (&pa) << " pointer: " << pa << std::endl;
    return 0;
}
