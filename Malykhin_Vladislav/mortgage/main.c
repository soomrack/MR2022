#include <stdio.h>


 typedef struct Person {
     long long kapital, perviyVznos, ezhVznos, rashody, stoimostKv, dohod, dolg;
     int  stavkaVklada, stavkaIpoteki;
} Person;

int Y = 900000000, Z = 5, A = 12 , mounths = 12, years = 20; //все вычисления происходят в копейках

int tax(long long a){
    int b;
    b = (long long int)(a * 0.005);
    return b;
}

long long priceRise(long long a){
    long long b = 0;
    b += (long long int)(0.5 * a);
    return b;
}

int main() {
   int X = Y/12/20; //значение ежемесячного взнооса;
    Person Alice = {
           10000000, 0, 0, 4000000, Y, 15000000, 0,Z,0,
   };
     Person Bob = {
            100000000, 30000000, X, 4000000, Y, 15000000, 0,Z,A
    };
    Bob.kapital -= Bob.perviyVznos; //платёж первого взноса
    Bob.dolg += Bob.stoimostKv - Bob.perviyVznos;
    printf("year:0  \t Alice:%.2lf \t Bob:%.2lf \t difference %.2lf \n",(double) Alice.kapital / 100.0,(double) (Bob.kapital + 900000000) / 100.0, (double) (Bob.kapital + 900000000 - Alice.kapital) / 100.0);
    for (int year = 0; year < years; year++) { //годовая итерация
        for (int mounth = 0; mounth < mounths; mounth++) { //месячная итерация
            Alice.kapital +=  (long long)((double)(Alice.dohod - Alice.rashody) * (double)(1 + 0.01 * Alice.stavkaVklada / 12));
            Bob.kapital += (long long )((double)(Bob.dohod - Bob.rashody - (Bob.ezhVznos + Bob.dolg * 0.01 * Bob.stavkaIpoteki / 12)) * (double)(1 + 0.01 * Bob.stavkaVklada / 12));
            Bob.dolg -= Bob.ezhVznos;
        }
        if ( year == 2){ // повышение годовой ставки
            Alice.stavkaVklada += 2;
            Bob.stavkaVklada += 2;
        }
        if(year == 4){ // повышение цен на недвижимость
            Bob.stoimostKv += priceRise(Bob.stoimostKv);
            Bob.kapital += priceRise(Bob.stoimostKv);
        }
        if(year == 6){ //падение дохода
            Alice.dohod -=3000000;
            Bob.dohod -= 3000000;
        }
        Bob.kapital-= tax(Bob.stoimostKv);
        printf("year:%d  \t Alice:%.2lf \t Bob:%.2lf \t difference:%.2lf \n",year+1, (double) Alice.kapital/100.0, (double) (Bob.kapital + 900000000) / 100.0, (double) (Bob.kapital + 900000000 - Alice.kapital) / 100.0); //вывод
    }
}