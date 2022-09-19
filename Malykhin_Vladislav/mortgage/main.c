#include <stdio.h>


 typedef struct Person {
     long long kapital, perviy_vznos, ezh_vznos, rashody, stoimost_kv, dohod, dolg;
     unsigned int  stavka_vklada, stavka_ipoteki;
} Person;
int const MONTHS = 12, YEARS = 20;
int Y = 9*1000*1000*100, Z = 5, A = 12; //все вычисления происходят в копейках

int tax(long long a){
    int b;
    b = (long long)(a * 0.005);
    return b;
}

long long priceRise(long long a){
    long long b;
    b = (long long)(a * 0.5);
    return b;
}

int main() {
   int X = Y / 12 / 20; //значение ежемесячного взнооса;
    Person Alice = {
           1000*1000*100, 0, 0, 4*1000*1000, Y, 150*1000*100, 0,Z,0,
   };
     Person Bob = {
            1000*1000*100, 300*1000*100, X, 4*1000*1000, Y, 150*1000*100, 0,Z,A
    };
    Bob.kapital -= Bob.perviy_vznos; //платёж первого взноса
    Bob.dolg += Bob.stoimost_kv - Bob.perviy_vznos;
    printf("year:0  \t Alice:%.2lf \t Bob:%.2lf \t difference %.2lf \n",(double) Alice.kapital / 100.0,(double) (Bob.kapital + 900000000) / 100.0, (double) (Bob.kapital + 900000000 - Alice.kapital) / 100.0);
    for (int year = 0; year < YEARS; year++) { //годовая итерация
        for (int month = 0; month < MONTHS; month++) { //месячная итерация
            Alice.kapital +=  (long long)((double)(Alice.dohod - Alice.rashody) * (double)(1 + 0.01 * Alice.stavka_vklada / 12));
            Bob.kapital += (long long )((double)(Bob.dohod - Bob.rashody - (Bob.ezh_vznos + Bob.dolg * 0.01 * Bob.stavka_ipoteki / 12)) * (double)(1 + 0.01 * Bob.stavka_vklada / 12));
            Bob.dolg -= Bob.ezh_vznos;
        }
        if ( year == 2){ // повышение годовой ставки
            Alice.stavka_vklada += 2;
            Bob.stavka_vklada += 2;
        }
        if(year == 4){ // повышение цен на недвижимость
            Bob.stoimost_kv += priceRise(Bob.stoimost_kv);
            Bob.kapital += priceRise(Bob.stoimost_kv);
        }
        if(year == 6){ //падение дохода
            Alice.dohod -= 3000000;
            Bob.dohod -= 3000000;
        }
        Bob.kapital -= tax(Bob.stoimost_kv);
        printf("year:%d  \t Alice:%.2lf \t Bob:%.2lf \t difference:%.2lf \n",year + 1, (double) Alice.kapital/100.0, (double) (Bob.kapital + 900000000) / 100.0, (double) (Bob.kapital + 900000000 - Alice.kapital) / 100.0); //вывод
    }
}