#include <stdio.h>


 typedef struct Person {
     long long kapital, perviyVznos, ezhVznos, rashody, stoimostKv, dohod, stavkaVklada, stavkaIpoteki;
} Person;
long long X , Y = 900000000, Z = 5, A = 12 , mounths = 12, years = 20;

int main() {
    X = Y/12/20;
    Person Alice = {
           100000000, 0, 0, 4000000, Y, 15000000, Z,0
   };
     Person Bob = {
            100000000, 30000000, X, 4000000, Y, 15000000, Z,A
    };
    Bob.kapital -= Bob.perviyVznos;
    Bob.stoimostKv -= Bob.perviyVznos;
    printf("Alice %.2lf Bob %.2lf difference %.2lf \n",Alice.kapital/100.0, (Bob.kapital + 900000000)/100.0, (Bob.kapital + 900000000 - Alice.kapital)/100.0);
    for(int year = 0; year < years; year++) {
        for (int mounth = 0; mounth < mounths; mounth++) {
            Alice.kapital += (Alice.dohod - Alice.rashody) * (1 + 0.01 * Alice.stavkaVklada / 12);
            Bob.kapital += (Bob.dohod - Bob.rashody - (Bob.ezhVznos + Bob.stoimostKv * 0.01 * Bob.stavkaIpoteki / 12)) * (1 + 0.01 * Bob.stavkaVklada / 12);
            Bob.stoimostKv -= Bob.ezhVznos;
        }
        printf("Alice %.2lf Bob %.2lf difference %.2lf \n",Alice.kapital/100.0, (Bob.kapital + 900000000)/100.0, (Bob.kapital + 900000000 - Alice.kapital)/100.0);
    }
}