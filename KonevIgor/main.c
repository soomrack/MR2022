#include <stdio.h>

// Задаем общие входные данные: начальный капитал, доход, ставка по вкладу
const int STARTUP_CAPITAL = 100000000;
const int DEPOSIT_RATE_ANNUAL_1ST = 3;
const int DEPOSIT_RATE_ANNUAL_2ND = 5;
const int TERM = 20;

// Задаем входные данные для Alice: оплата коммунальных услуг и прочие траты
const int UTILITIES_PAYMENT_A = 4000000;
const int  ALICE_SPENDING = 2000000;

//Задаем входные данные для Bob: первый платеж по ипотеке,
//оплата коммунальных услуг и прочие траты, стоимость квартиры, ежемесячный взнос
const int FIRST_PAYMENT = 30000000;
const int UTILITIES_PAYMENT_B = 1000000;
const int BOB_SPENDING = 1500000;
const int MONTHLY_PAYMENT = 10000000;

int main() {
    int SALARY = 15000000;
    long long FLAT_COST = 1200000000;
    long long aliceCapital = STARTUP_CAPITAL;
    long long bobCapital =  (STARTUP_CAPITAL - FIRST_PAYMENT);
    int alicePercents;
    int bobPercents;
    long long bobFinalCapital;
    int depositRateAnnual;
    printf("%12s %15s %17s\n", "Capital on ", "Alice", "Bob");
    for (int i = 1; i <= TERM * 12; i++) {

       // Рост цен на недвижимость
      if (i == 12 * 5){
          FLAT_COST *= 1.5;
        }

      // Падение дохода
        if (i == 10 * 12){
          SALARY /= 1.5;
        }
        if (i == 16 * 12){
          SALARY = 15000000;
        }

        // Повышение ставки по вкладу
        if (i <= 36) {
            depositRateAnnual = DEPOSIT_RATE_ANNUAL_1ST;
        } else {
            depositRateAnnual = DEPOSIT_RATE_ANNUAL_2ND;
        }

        alicePercents = aliceCapital * depositRateAnnual / 1200;
        aliceCapital += alicePercents + (SALARY - UTILITIES_PAYMENT_A - ALICE_SPENDING);
        bobPercents = bobCapital * depositRateAnnual / 1200;
        bobCapital += bobPercents + (SALARY - UTILITIES_PAYMENT_B - BOB_SPENDING - MONTHLY_PAYMENT);
        if (i % 12 == 0) {
            printf("%4d year %18lld,%lld %15lld,%lld\n", i/12, aliceCapital/100, aliceCapital%100, bobCapital/100, bobCapital%100);
        }
    }
    bobFinalCapital = bobCapital + FLAT_COST;

    printf("Final capital %14lld,%lld %15lld,%lld\n", aliceCapital/100, aliceCapital%100, bobFinalCapital/100, bobFinalCapital%100);
    if (aliceCapital > bobFinalCapital) {
        printf("Alice will have a %lld,%lld rubles more, then Bob\n", (aliceCapital - bobFinalCapital) / 100, (aliceCapital - bobFinalCapital) % 100);
    } else {
        printf("Bob will have a %lld,%lld rubles more, then Alice\n", (bobFinalCapital - aliceCapital) / 100, (bobFinalCapital - aliceCapital) % 100);
    }
}
