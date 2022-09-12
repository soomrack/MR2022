#include <stdio.h>
#include <math.h>

struct human{
    unsigned int firstPay; // первоначальный взнос
    unsigned int monthPay; //ежемесячный взнос
    unsigned int monthSpend; // ежемесячные траты
    unsigned long long int nowMoney; // текущие средства
};

const unsigned int initMoney = 1000000 * 100; // начальный капитал в коп
const unsigned int apartPrice = 5000000 * 100; // стоимость квартиры в коп
const unsigned int income = 150000 * 100; // доход в коп
const double fbankRate = 0.08; // год ставка в банке первые 3 года
const double sbankRate = 0.1; // год ставка в банке следующие года
const double apartRate = 0.1; // год ставка по ипотеке
const int year = 20; // срок в годах

int toCalcMonthPay(unsigned int price, unsigned int firstPay, double rate, int time) {
    double monthRate = rate / 12;
    int monthPay = ((price - firstPay) * monthRate) / (1 - pow((1 + monthRate),(time * -12)));
    return monthPay;
}

int main() {
    struct human Alice;
    Alice.nowMoney = initMoney;
    Alice.monthSpend = 40000 * 100;

    struct human Bob;
    Bob.firstPay = (unsigned int) (0.15 * apartPrice);
    Bob.nowMoney = initMoney - Bob.firstPay;
    Bob.monthPay = toCalcMonthPay(apartPrice, Bob.firstPay, apartRate, year);
    Bob.monthSpend = 10000 * 100;

    for (int i = 1; i < year * 12 + 1; i++){
        if (i < 37) {
            Alice.nowMoney = (unsigned long long int) ((double) (Alice.nowMoney + income - Alice.monthSpend) *
                                                       (1 + fbankRate / 12));
            Bob.nowMoney = (unsigned long long int) ((double) (Bob.nowMoney + income - Bob.monthSpend - Bob.monthPay) *
                                                     (1 + fbankRate / 12));
        } else{
            Alice.nowMoney = (unsigned long long int) ((double) (Alice.nowMoney + income - Alice.monthSpend) *
                                                       (1 + sbankRate / 12));
            Bob.nowMoney = (unsigned long long int) ((double) (Bob.nowMoney + income - Bob.monthSpend - Bob.monthPay) *
                                                     (1 + sbankRate / 12));
        }
        if ((i % 60) == 0){
            printf(" | %d years ", (i / 12));
            printf(" | Alice: %d.%d", Alice.nowMoney / 100, Alice.nowMoney % 100);
            printf(" | Bob: %d.%d\n", Bob.nowMoney / 100, Bob.nowMoney % 100);
        }
    }

    printf("\nAfter 20 years:\nAlice: %d.%d rub\n", Alice.nowMoney / 100, Alice.nowMoney % 100);
    printf("Bob: %d.%d rub + the apartment\n", Bob.nowMoney / 100, Bob.nowMoney % 100);
    printf("Alice is richer than Bob of %d.%d rub", (Alice.nowMoney - Bob.nowMoney) / 100, (Alice.nowMoney - Bob.nowMoney) % 100);

    return 0;
}
