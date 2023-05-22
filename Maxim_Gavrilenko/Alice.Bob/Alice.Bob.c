#include <stdio.h>

int main() {
    unsigned long long int bank_a = 100000000, bank_b = 100000000, rubles_a, cents_a,
    rubles_b, cents_b;
    int first_cont = 70000000; // Первоначальный взнос
    int a_utilities = 4000000; // Коммунальные услуги Alice
    int b_utilities = 1000000; // Коммунальные услуги Bob
    long long int room = 6000000; // Стоимость квартиры в рублях
    int month_cont = 5000000; // Ежемесячный платеж
    double rate = 0.07; // Ставка банка первые три года
    int revenue_a = 15000000, revenue_b = 15000000;
    double tax = 0.001;


    bank_b -= first_cont; // Остаток на вкладе Боба
    for (unsigned int year = 1; year <= 20; year++) {
        if (year % 5 == 0) {
            room = (long long int) (room * 1.5);
            if (room < 50000000 & room > 20000000)
                tax = 0.0015;
        }
        if (year == 10) { // Новая зарплата для Alice
            printf("\n\nPrint new revenue for Alice");
            scanf("%d%", &revenue_a);
            revenue_a = revenue_a * 100;
        }
        if (year == 14) { // Новая зарплата для Bob
            printf("\n\nPrint new revenue for Bob");
            scanf("%d", &revenue_b);
            revenue_b = revenue_b * 100;
        }
        for (unsigned int month = 1; month <= 12; month++) {
            if (year == 4) {
                rate = 0.1; // Ставка банка через три года
            }
            bank_a = (unsigned long long int) ((bank_a + revenue_a - a_utilities) * (1.f + rate / 12));
            bank_b = (unsigned long long int) ((bank_b + revenue_b - b_utilities - month_cont - room * tax) *
                                               (1.f + rate / 12));
        }
        rubles_a = bank_a / 100;
        cents_a = bank_a % 100;
        rubles_b = bank_b / 100;
        cents_b = bank_b % 100;

        printf("\nroom - %llu rubles\n", room);
        printf("tax - %.1f%\n", tax * 100);
        printf("current year - %d\n", year);
        printf("current rate - %.2f\n", rate);
        printf("Alice actives at the end of year - %llu.%llu%llu rubles\n", rubles_a, cents_a / 10, cents_a % 10);
        printf("Bob actives at the end of year - %llu.%llu%llu rubles\n", rubles_b + room, cents_b / 10,
               cents_b % 10);

        if (rubles_b + room > rubles_a) {
            if (cents_b < cents_a) {
                rubles_b -= 1;
                cents_b += 100;
            }
            printf("Bob more profitable than Alice on %llu.%llu rubles!\n", ((rubles_b + room) - rubles_a),
                   cents_b - cents_a);
        }
        else
        {
            if (cents_a < cents_b) {
                rubles_a -= 1;
                cents_a += 100;
            }
            printf("Alice more profitable than Bob on %llu.%llu rubles!\n", (rubles_a - (rubles_b + room)),
                   cents_a - cents_b);
        }
    }
    return 0;
}