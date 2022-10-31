#include <stdio.h>
#include <math.h>

const int start_capital=1000*1000*100;  // НАчальный капитал в копейках
const int flat_price=8000*1000*100;
const int first_payment=flat_price/10;
const int rent=50*1000*100;
const int time_konechn=20*12;
const double stavka_vklad=0.08/12.0+1.0;  // Ставка в месяц
const double stavka_ipoteka=0.12/12.0+1.0;
const double influation=0.05/12.0+1.0;

struct person {
    int zp;
    int spend;
    long long int cash;
} person;


struct person Alice = { 150*1000*100,40*1000*100,start_capital};
struct person Bob = { 150*1000*100,40*1000*100,start_capital};


double ipoteka_payment () {
    double ipoteka_payment = ((flat_price - start_capital) * stavka_ipoteka) / (1 - pow((1 + ipoteka_payment),-time_konechn));
    return ipoteka_payment;
}


void simulation () {
    Bob.cash=start_capital-first_payment;
    double payment= ipoteka_payment();
    for (int month=0;month<=time_konechn;month++) {
        Alice.cash = Alice.cash * stavka_vklad + Alice.zp - rent - Alice.spend;
        Bob.cash = Bob.cash * stavka_vklad + Bob.zp - payment - Bob.spend;
    }
}









int main() {
    simulation();
    printf("%lld",Alice.cash);
    return 0;
}
