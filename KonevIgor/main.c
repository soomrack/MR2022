#include <stdio.h>

// Задаем общие входные данные: начальный капитал, доход, ставка по вкладу
const int STARTUP_CAPITAL = 1000000;
const int SALARY = 150000;
const double DEPOSIT_RATE_ANNUAL_1ST = 0.03;
const double DEPOSIT_RATE_ANNUAL_2ND = 0.05;
const int TERM = 20;

// Задаем входные данные для Alice: оплата коммунальных услуг и прочие траты
const int UTILITIES_PAYMENT_A = 40000;
const int SPENDING_A = 20000;

//Задаем входные данные для Bob: первый платеж по ипотеке,
//оплата коммунальных услуг и прочие траты, стоимость квартиры, ежемесячный взнос
const int FIRST_PAYMENT = 300000;
const int UTILITIES_PAYMENT_B = 10000;
const int SPENDING_B = 15000;
const int FLAT_COST = 12000000;
const int MONTHLY_PAYMENT = 100000;

int main() {
    int aliceCapital = STARTUP_CAPITAL;
    int bobCapital =  (STARTUP_CAPITAL - FIRST_PAYMENT);
    float alicePercents;
    float bobPercents;
    float bobFinalCapital;
    double depositRateAnnual;
    printf("%12s %12s %13s\n", "Capital on ", "Alice", "Bob");
    for (int i = 1; i <= TERM * 12; i++) {
        if (i <= 36) {
            depositRateAnnual = DEPOSIT_RATE_ANNUAL_1ST;
        } else {
            depositRateAnnual = DEPOSIT_RATE_ANNUAL_2ND;
        }
        alicePercents = aliceCapital * depositRateAnnual / 12;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - SPENDING_A);
        bobPercents = bobCapital * depositRateAnnual / 12;
        bobCapital += bobPercents + (SALARY - UTILITIES_PAYMENT_B - SPENDING_B - MONTHLY_PAYMENT);
        if (i % 12 == 0) {
            printf("%4d year %18.2f %15.2f\n", i/12, aliceCapital, bobCapital);
        }
    }
    bobFinalCapital = bobCapital + FLAT_COST;
    printf("Final capital %14.2f %15.2f\n", aliceCapital, bobFinalCapital);
    if (aliceCapital > bobFinalCapital) {
        printf("Alice will have a %10.2f rubles more, then Bob", aliceCapital - bobFinalCapital);
    } else {
        printf("Bob will have a %10.2f rubles more, then Alice", bobFinalCapital - aliceCapital);
    }
}
