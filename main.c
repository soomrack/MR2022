#include <stdio.h>
#include <math.h>

#define N 1000000
#define D 150000
#define Y 20

int main() {

    int A = N, B = N, i, Akv = 40000, Bkv = 10000, M = 12 * Y;
    double x, y, z = 10, zM, Z, st;

    Z = 1 + z/100;
    st = 1/12;

    zM = pow(Z, st);

    printf("%lf, %lf", Z, st);

    return 0;
}