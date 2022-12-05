#include <stdio.h>
#include <math.h>

const int start_capital = 1000 * 1000 * 100;  // Начальный капитал в копейках
const long int flat_price = 8000*1000 * 100;
const int first_payment = flat_price / 10;
const int rent = 50 * 1000 * 100;
const int time_experiment = 20 * 12;

const double stavka_vklad = 0.08 / 12.0 + 1.0;  // Ставка в месяц
const double stavka_hypothec = 0.12 / 12.0;
const double influation = 0.05 / 12.0 + 1.0;


struct person {
    int zp;
    int spend;
    long long int cash;
} person;


struct person Alice = { 150 * 1000 * 100,40 * 1000 * 100,start_capital};
struct person Bob = { 150 * 1000 * 100,40 * 1000 * 100,start_capital};


double hypothec_payment () {
    double hypothec_payment = ((flat_price - start_capital) * stavka_hypothec) /
            (1 - pow((1 + stavka_hypothec), - time_experiment));
    return hypothec_payment;
}


long long int simulation () {
    Bob.cash = start_capital - first_payment;
    double payment = hypothec_payment();
    long long int flat_price_dynamic = flat_price;
    for (int month=0; month <= time_experiment; month++) {
        Alice.cash = Alice.cash * stavka_vklad + Alice.zp - rent - Alice.spend;
        Bob.cash = Bob.cash * stavka_vklad + Bob.zp - payment - Bob.spend;
        if (month == 120) {
            Alice.zp = Alice.zp + 10 * 1000 * 100;  // Через 10 лет Алису повысили в должности, а её зарплата увличилась на 10К
            Bob.zp = Bob.zp - 10 * 1000 * 100;  // Через 10 лет Боба понизили в должности, а его зарплата уменьшилась на 10К
        }
        if (month == 180) {
            Alice.spend = Alice.spend + 8 * 1000 * 100;  // Через 15 лет Алиса завела собаку, её затраты увеличились на 8К
            Bob.zp = 165 * 1000 * 100;  // Через 15 лет Боб нашел новую работу с зарплатой на 15К больше изначальной
        }
        flat_price_dynamic = flat_price_dynamic *  influation;
    }
    return flat_price_dynamic;
}


void result(long long int flat){
    printf("Alice cash = %lld \n", Alice.cash/100);
    printf("Bob cash + flat price = %lld \n", (Bob.cash + flat)/100);
    printf("Flat price = %.lld", flat/100);
}


int main() {
    long long int flat_price_experiment = simulation();
    result(flat_price_experiment);
    return 0;
}
