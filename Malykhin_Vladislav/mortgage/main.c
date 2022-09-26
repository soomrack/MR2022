#include <stdio.h>


 typedef struct Person {
     long long kapital, perviy_vznos, ezh_vznos, rashody, stoimost_kv, dohod, dolg;
     unsigned int  stavka_vklada, stavka_ipoteki;
} Person;

int const MONTHS = 12, YEARS = 20, FIRST_PRICE = 9*1000*1000*100, FIRST_STAVKA_VKLADA = 5, FIRST_STAVKA_IPOTEKI = 12; //все вычисления происходят в копейках
int const EZH_VZNOS_PURE = FIRST_STAVKA_IPOTEKI / 12 / 20; //значение ежемесячного взнооса без процентов


void tax (Person *person){
    person->kapital -= 0.005 * person->stoimost_kv;
}


void stavkaVkladaRise( Person *person ){
    person->stavka_vklada += 2;
}


void priceRise(Person *person){
    person->kapital -= person->stoimost_kv;
    person->stoimost_kv = (long long)(person->stoimost_kv * 1.5);
    person->kapital += person->stoimost_kv;
}


void dohodFall(Person *person) {
    person->dohod -= 30*100*1000;
}


void obrabotchikYear (int year, Person *person ){
    if (year == 2) stavkaVkladaRise( person );
    if (year == 4) priceRise( person );
    if (year == 6) dohodFall( person );
}


void rashodyDohody ( Person *person ){
    person->kapital += person->dohod - person->rashody;
}


void ipotekaPayment( Person *person ){
    person->kapital -= (person->ezh_vznos + person->dolg * 0.01 * person->stavka_ipoteki / 12);
    person->dolg -= person->ezh_vznos;
}


void vkladIncome( Person *person ) {
    person->kapital *= (double)(1 + 0.01 * person->stavka_vklada / 12);
}


void obrabotchikMonth ( Person *person ){
    rashodyDohody (person);
    ipotekaPayment (person);
    vkladIncome (person);
}


void personPrint ( Person person ){
    printf("%.2lf  \t",(person.kapital + person.stoimost_kv) / 100.0);
}

void diffPrint ( Person person1, Person person2 ){
    printf("difference:%.2lf \n",(person1.kapital - person2.stoimost_kv) / 100.0);
}


int main() {
    Person Alice = {
           1000*1000*100, 0, 0, 4*1000*1000, FIRST_PRICE, 150*1000*100, 0,FIRST_STAVKA_VKLADA,0,
   };
     Person Bob = {
            1000*1000*100, 300*1000*100, EZH_VZNOS_PURE, 4*1000*1000, FIRST_PRICE, 150*1000*100, 0,FIRST_STAVKA_VKLADA,FIRST_STAVKA_IPOTEKI
    };
    Bob.kapital -= Bob.perviy_vznos; //платёж первого взноса
    Bob.dolg += Bob.stoimost_kv - Bob.perviy_vznos;
    printf("year:0\tAlice:"); //вывод
    personPrint(Alice);
    printf("Bob:");
    personPrint(Bob);
    diffPrint(Alice,Bob);
    for (int year = 0; year < YEARS; year++) { //годовая итерация
        for (int month = 0; month < MONTHS; month++) { //месячная итерация
            obrabotchikMonth(&Alice);
            obrabotchikMonth(&Bob);
        }
        obrabotchikYear ( year,  &Alice );
        obrabotchikYear ( year,  &Bob );
        tax(&Bob);
        printf("year:%d\tAlice:",year + 1); //вывод
        personPrint(Alice);
        printf("Bob:");
        personPrint(Bob);
        diffPrint(Alice,Bob);
    }
}