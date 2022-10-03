#include <math.h>

struct human{
    unsigned int first_pay; // первоначальный взнос
    unsigned int month_pay; //ежемесячный взнос
    unsigned int month_spend; // ежемесячные траты
    unsigned long long now_money; // текущие средства
};

const unsigned int INITIAL_MONEY = 1000000 * 100; // начальный капитал в коп
const unsigned int APART_PRICE = 5000000 * 100; // стоимость квартиры в коп
const double APART_RATE = 0.1; // год ставка по ипотеке
const int YEAR = 20; // срок в годах
unsigned int income = 150000 * 100; // доход в коп
double bank_rate = 0.08; // год ставка в банке

int to_calc_month_pay(unsigned int price, unsigned int first_pay, double rate, int time) {
    double month_rate = rate / 12;
    int month_pay = (int)(((price - first_pay) * month_rate) / (1 - pow((1 + month_rate), (time * -12))));
    return month_pay;
}

void to_display_result(unsigned long long int money){
    unsigned long long rub = money / 100;
    unsigned long long kop = money % 100;
    printf("%llu.%llu", rub, kop);
}

int main() {
    struct human Alice;
    Alice.now_money = INITIAL_MONEY;
    Alice.month_spend = 40000 * 100;

    struct human Bob;
    Bob.first_pay = (unsigned int) (0.15 * APART_PRICE);
    Bob.now_money = INITIAL_MONEY - Bob.first_pay;
    Bob.month_pay = to_calc_month_pay(APART_PRICE, Bob.first_pay, APART_RATE, YEAR);
    Bob.month_spend = 10000 * 100;

    for (int i = 1; i < YEAR * 12 + 1; i++){
        Alice.now_money = (unsigned long long) ((double) (Alice.now_money + income - Alice.month_spend) * (1 + bank_rate / 12));
        Bob.now_money = (unsigned long long) ((double) (Bob.now_money + income - Bob.month_spend - Bob.month_pay) * (1 + bank_rate / 12));
        if (i == (3 * 12)) bank_rate += 0.02; // увеличение процента по вкладу спустя 3 года
        if (i == (10 * 12)) income -= 50000 * 100; // уменьшение додходов спустя 10 лет
        if ((i % 60) == 0){
            printf("\n| %d years ", (i / 12));
            printf(" | Alice:");
            to_display_result(Alice.now_money);
            printf(" | Bob:");
            to_display_result(Bob.now_money);
        }
    }

    printf("\n\nAfter 20 years:\nAlice: ");
    to_display_result(Alice.now_money);
    printf(" rub\nBob: ");
    to_display_result(Bob.now_money);
    printf(" rub + the apartment\nAlice is richer than Bob of %llu.%llu rub\n", (unsigned long long)((Alice.now_money - Bob.now_money) / 100),
           (unsigned long long) ((Alice.now_money - Bob.now_money) % 100));
    return 0;
}
