#include <stdio.h>

const int STARTUP_CAPITAL = 1000000;
const double DEPOSIT_RATE_ANNUAL = 0.02;
const double DEPOSIT_RATE_ANNUAL_NEW = 0.03;
const int YEARS = 20;
const int YEARS_NEW = 4;

const int UTILITIES_PAYMENT_A = 40000;
const int SPENDING_A = 10000;

const int FIRST_PAYMENT = 300000;
const int UTILITIES_PAYMENT_B = 10000;
const int SPENDING_B = 10000;
const int MONTHLY_PAYMENT = 55165;


int main() {
    double aliceCapital = (double) STARTUP_CAPITAL;
    double bobCapital = STARTUP_CAPITAL - FIRST_PAYMENT;
    double alicePercents;
    double bobPercents;
    double bobFinalCapital;
    double FLAT_COST = 8000000;
    int SALARY = 150000;

    printf("%12s %12s %13s\n", "Capital on ", "Alice", "Bob");
    for (int i = 1; i <= (YEARS_NEW * 12)-1; i++) {
        if (i%36==0){
            SALARY=(int)SALARY*0.95;
        }
        alicePercents = aliceCapital * DEPOSIT_RATE_ANNUAL / 12;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - SPENDING_A);
        bobPercents = bobCapital * DEPOSIT_RATE_ANNUAL / 12;
        bobCapital += bobPercents + (SALARY - UTILITIES_PAYMENT_B - SPENDING_B - MONTHLY_PAYMENT);
        if (i % 12 == 0) {
            bobCapital-=FLAT_COST*0.001;
            printf("%4d year %18.2f %15.2f", i/12, aliceCapital, bobCapital+FLAT_COST); printf("\t0.02\n");
        }
    }
    for (int j = YEARS_NEW * 12; j <= YEARS * 12; j++) {
        if (j%36==0){
            SALARY=(int)SALARY*0.95;
        }
        alicePercents = aliceCapital * DEPOSIT_RATE_ANNUAL_NEW / 12;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - SPENDING_A);
        bobPercents = bobCapital * DEPOSIT_RATE_ANNUAL_NEW / 12;
        bobCapital += (unsigned long long int )(bobPercents + (SALARY - UTILITIES_PAYMENT_B - SPENDING_B - MONTHLY_PAYMENT));
        if (j%60 == 0){
            FLAT_COST=(unsigned long long int)FLAT_COST*1.5;
        }

        if (j % 12 == 0) {
            bobCapital-=FLAT_COST*0.001;
            printf("%4d year %18.2f %15.2f", j / 12, aliceCapital, bobCapital+FLAT_COST); printf("\t0.03\n");
        }

    }

    bobFinalCapital = bobCapital + FLAT_COST;

}
//добавил увеличение стоимости квартиры каждые 5 лет в 1.5 раза строка 43
//добавил налог на недвижку 0.1 процента каждый год у боба строки 34 и 47
//добавил что каждые 3 года получка становится 0.95 от предыдущей строки 30 и 43