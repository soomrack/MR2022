#include <stdio.h>


 typedef struct Person {
     long long kapital, perviyVznos, ezhVznos, rashody, stoimostKv, dohod, dolg;
     int  stavkaVklada, stavkaIpoteki;
} Person;

int X , Y = 900000000, Z = 5, A = 12 , mounths = 12, years = 20;

int tax(long long a){
    int b;
    b = a * 0.005;
    return b;
}

long long priceRise(long long a){
    long long b = 0;
    b += 0.5*a;
    return b;
}

int main() {
    X = Y/12/20;
    Person Alice = {
           100000000, 0, 0, 4000000, Y, 15000000, 0,Z,0,
   };
     Person Bob = {
            100000000, 30000000, X, 4000000, Y, 15000000, 0,Z,A
    };
    Bob.kapital -= Bob.perviyVznos;
    Bob.dolg += Bob.stoimostKv - Bob.perviyVznos;
    printf("year 0 Alice %.2lf Bob %.2lf difference %.2lf \n",(double) Alice.kapital/100.0,(double) (Bob.kapital + 900000000)/100.0, (double) (Bob.kapital + 900000000 - Alice.kapital)/100.0);
    for(int year = 0; year < years; year++) {
        for (int mounth = 0; mounth < mounths; mounth++) {
            Alice.kapital += (long long) ((Alice.dohod - Alice.rashody) * (1 + 0.01 * Alice.stavkaVklada / 12));
            Bob.kapital += (long long) ((Bob.dohod - Bob.rashody - (Bob.ezhVznos + Bob.dolg * 0.01 * Bob.stavkaIpoteki / 12)) * (1 + 0.01 * Bob.stavkaVklada / 12));
            Bob.dolg -= Bob.ezhVznos;
        }
        if ( year == 2){
            Alice.stavkaVklada += 2 + Alice.stavkaVklada;
            Bob.stavkaVklada += 2 + Bob.stavkaVklada;
        }
        if(year == 4){
            Bob.stoimostKv += priceRise(Bob.stoimostKv);
            Bob.kapital += priceRise(Bob.stoimostKv);
        }
        if(year == 6){
            Alice.dohod -=30000;
            Bob.dohod -= 30000;
        }
        Bob.kapital-= tax(Bob.stoimostKv);
        printf("year %d Alice %.2lf Bob %.2lf difference %.2lf \n",year+1, (double) Alice.kapital/100.0, (double) (Bob.kapital + 900000000)/100.0, (double) (Bob.kapital + 900000000 - Alice.kapital)/100.0);
    }
}