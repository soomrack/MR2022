#include <stdio.h>

int main( ) {
    unsigned long long int bank_a = 100000000; //начальный капитал А
    unsigned long long int nach_b = 100000000; //начальный капитал B
    int pv_b = 30000000; //первый взнос В
    unsigned long long int dox_A = 15000000; //Доход каждого
    unsigned long long int dox_B = 12000000;
    int trat_a = 4000000; //Траты А
    int trat_b = 1000000; //Траты В
    unsigned long long int plat_b = 5000000; //Платеж по ипотеке В
    int flat = 700000000; //стоимость квартиры
    double stavka = 0.08; //Ставка по вкладу
    unsigned long long int itog_a; //Итог А
    unsigned long long int itog_b; //Итог В

    unsigned long long int bank_b = nach_b - pv_b;
    for (int year = 1; year <= 20; year++) {
        if (year == 10) { //падение доходов обоих из...
            dox_A -= 1500000;//
        }//
        if (year >= 3) {
            stavka = 0.10; //увеличение ставки по вкладу с 4 года
        }
        if (year % 5 == 0) {
            flat = flat * 1.1;
        }
        for (int month = 1; month <= 12; month++) {
            bank_a = (unsigned long long int) ((bank_a + dox_A - trat_a) * (1.f + stavka / 12)); //учет налога на недвижимость
            bank_b = (unsigned long long int) ((bank_b + dox_B - trat_b - plat_b) * (1.f + stavka / 12) - 5000000); // учет налога на недвижимость
        }
        itog_a = bank_a;
        itog_b = (bank_b + flat);
        printf("stavka %.2f flat_cost:%dk", stavka, flat/100000);
        printf(" %dyear: alice's salary:%lluk bob's salary:%lluk ", year, dox_A/100000, dox_B/100000);
        printf("Alice = %llu.%llu ", (unsigned long long int) itog_a / 100, (unsigned long long int) itog_a % 100);
        printf("Bob = %llu.%llu\n", (unsigned long long int) itog_b / 100, (unsigned long long int) itog_b % 100);
    }
    return 0;
}