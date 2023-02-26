#include "List.h"


typedef struct Matrix {
    int a;
    char b;
} Matrix;


int main() {
    List<int> A;
    A.append(0);
    A.append(1);
    A.append(2);
    A.append(3);
    A.append(4);
    A.append(5);
    A.print();
    A.pop(0);
    A.print();

    List<Matrix> B;
    Matrix m;
    m.a = 6;
    m.b = 5;
    B.append(m);
    B.append(m);
    B.append(m, 0);

    return 0;
}