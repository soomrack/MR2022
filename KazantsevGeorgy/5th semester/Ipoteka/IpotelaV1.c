#include <stdio.h>

const int STARTUP_CAPITAL = 1000000;
const int SALARY = 150000;
const double DEPOSIT_RATE_ANNUAL = 0.02;
const double DEPOSIT_RATE_ANNUAL_NEW = 0.03;
const int YEARS = 20;
const int YEARS_NEW = 3;

const int UTILITIES_PAYMENT_A = 40000;
const int SPENDING_A = 10000;

const int FIRST_PAYMENT = 300000;
const int UTILITIES_PAYMENT_B = 10000;
const int SPENDING_B = 10000;
const int FLAT_COST = 8000000;
const int MONTHLY_PAYMENT = 55165;


int main() {
    double aliceCapital = (double) STARTUP_CAPITAL;
    double bobCapital = STARTUP_CAPITAL - FIRST_PAYMENT;
    double alicePercents;
    double bobPercents;
    double bobFinalCapital;

    printf("%12s %12s %13s\n", "Capital on ", "Alice", "Bob");
    for (int i = 1; i <= YEARS_NEW * 12; i++) {
        alicePercents = aliceCapital * DEPOSIT_RATE_ANNUAL / 12;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - SPENDING_A);
        bobPercents = bobCapital * DEPOSIT_RATE_ANNUAL / 12;
        bobCapital += bobPercents + (SALARY - UTILITIES_PAYMENT_B - SPENDING_B - MONTHLY_PAYMENT);
        if (i % 12 == 0) {
            printf("%4d year %18.2f %15.2f", i/12, aliceCapital, bobCapital); printf("\t0.02\n");
        }
    }
    for (int j = (YEARS_NEW + 1) * 12; j <= YEARS * 12; j++) {
        alicePercents = aliceCapital * DEPOSIT_RATE_ANNUAL_NEW / 12;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - SPENDING_A);
        bobPercents = bobCapital * DEPOSIT_RATE_ANNUAL_NEW / 12;
        bobCapital += bobPercents + (SALARY - UTILITIES_PAYMENT_B - SPENDING_B - MONTHLY_PAYMENT);
        if (j % 12 == 0) {
            printf("%4d year %18.2f %15.2f", j / 12, aliceCapital, bobCapital); printf("\t0.03\n");
        }
    }

    bobFinalCapital = bobCapital + FLAT_COST;
   
}
