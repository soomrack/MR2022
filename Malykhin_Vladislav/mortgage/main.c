#include <stdio.h> //вывод засунуть в ещё одну функцию, форматирование текста.


 typedef struct Person {
     unsigned long long int capital;
     unsigned long long int first_fee;
     unsigned long long int annual_fee;
     unsigned long long int expenses;
     unsigned long long int real_estate_price;
     unsigned long long int income;
     unsigned long long int debt;
     unsigned int  deposit_rate;
     unsigned int  mortgage_rate;
} Person;

unsigned int const YEARS = 20;
unsigned int const FIRST_PRICE = 9*1000*1000*100;//все вычисления происходят в копейках
unsigned int const START_CAPITAL = 1*1000*1000*100;
unsigned int const FIRST_FEE = 300*1000*100;
unsigned int const START_DEPOSIT_RATE = 5;
unsigned int const START_MORTGAGE_RATE = 12;
unsigned int const ANNUAL_FEE_PURE = (FIRST_PRICE - FIRST_FEE) / 12 / YEARS; //значение ежемесячного взнооса без процентов

void tax_payment(Person *person){
    person->capital -= 0.005 * person->real_estate_price;
}

void deposit_rate_rise(Person *person){
    person->deposit_rate += 2;
}

void price_rise(Person *person){
    person->real_estate_price = (unsigned long long int)(person->real_estate_price * 1.5);
}

void income_fall(Person *person) {
    person->income -= 30 * 1000 * 100;
}

void expenses_income(Person *person){
    person->capital += person->income - person->expenses;
}

void mortgage_payment(Person *person){
    if(person->debt > person->annual_fee){
    person->capital -= (person->annual_fee + person->debt * 0.01 * person->mortgage_rate / 12);
    person->debt -= person->annual_fee;
    }
    else{
        person->capital -= person->debt;
        person->debt = 0;
    }
}

void deposit_income(Person *person) {
    person->capital *= (long double)(1 + 0.01 * person->deposit_rate / 12);
}

void full_print(int year, Person alice,Person bob){
    printf("year:%d\tAlice:%.2lf  \tBob:%.2lf  \tdifference:%.2lf \n",year, (alice.capital + alice.real_estate_price)/ 100.0, (unsigned long long int)(bob.capital + bob.real_estate_price) / 100.0,(long long int)((alice.capital + alice.real_estate_price) - (bob.capital + bob.real_estate_price)) / 100.0);
}

int main() {
    Person Alice = {
            START_CAPITAL, 0, 0, 40*1000*100, 0, 150*1000*100, 0, START_DEPOSIT_RATE, 0,
   };
    Person Bob = {
            START_CAPITAL, FIRST_FEE, ANNUAL_FEE_PURE, 40*1000*100, FIRST_PRICE, 150*1000*100, 0, START_DEPOSIT_RATE, START_MORTGAGE_RATE
    };
    for (int year = 0; year <= YEARS; year++) { //годовая итерация
        for (int month = 0; month < 12; month++) { //месячная итерация
            if(year > 0) {
                expenses_income(&Alice);
                mortgage_payment(&Alice);
                deposit_income(&Alice);
                expenses_income(&Bob);
                mortgage_payment(&Bob);
                deposit_income(&Bob);
            }
        }
        switch (year) {
            case 0:
                Bob.capital -= Bob.first_fee; //платёж первого взноса
                Bob.debt += Bob.real_estate_price - Bob.first_fee;
                break;
            case 2:
                deposit_rate_rise(&Alice);
                deposit_rate_rise(&Bob);
                break;
            case 4:
                price_rise(&Alice);
                price_rise(&Bob);
                break;
            case 6:
                income_fall(&Alice);
                income_fall(&Bob);
                break;
        }
        tax_payment(&Bob);
        full_print(year,Alice,Bob);
    }
}