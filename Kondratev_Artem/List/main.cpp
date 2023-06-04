#include "List.h"


typedef struct Matrix {
    int a;
    char b;
} Matrix;


int main() {
    List<int> A;
    A.push(0);
    A.push(1);
    A.push(2);
    A.push(3);
    A.push(4);
    A.push(5);
    A.print();
    A.pop();
    A.print();

    List<Matrix> B;
    Matrix m;
    m.a = 6;
    m.b = 5;
    B.push(m);
    B.push(m);
    B.push(m, 0);
    B.pop();

    ListIterator<int> iter(&A, A[2]);
    iter.find(4);
    iter.pushNext(19);
    A.print();

    return 0;
}