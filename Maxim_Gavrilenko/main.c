#include <stdio.h>
#include <malloc.h>
unsigned int years = 20;
int annual_contrib = 60 * 1000 * 100;
int first_contrib = 300 * 1000;


typedef struct person {
    const char* name;
    unsigned long long bank;
    unsigned long long revenue;
    unsigned long spending;
    unsigned long long house;
    double rate;
    double tax;
}person;


void init_Alice(person* Alice)
{
    Alice->name = "Alice";
    Alice->bank = 1000 * 1000 * 100;
    Alice->revenue = 150 * 1000 * 100;
    Alice->house = 0;
    Alice->spending = 40 * 1000 * 100;
    Alice->rate = 0.08;
}


void init_Bob(person* Bob)
{
    Bob->name = "Bob";
    Bob->tax = 0.001;
    Bob->bank = 1000 * 1000 * 100 - first_contrib;
    Bob->revenue = 150 * 1000 * 100;
    Bob->house = 7000 * 1000 * 100;
    Bob->spending = (long long)(10 * 1000 * 100 + annual_contrib + (double)(Bob)->house * Bob->tax/12);
    Bob->rate = 0.08;
}


void month_pay (person* buyer) {
    buyer->bank = (unsigned long long)((double)(((buyer->bank) - buyer-> spending + buyer -> revenue))*
            (1.f+ buyer->rate/12));
}


void live_changes_Alice(person* A, const unsigned int year) { // Через 10 лет упала зарплата
    if (year == 10) {
        A->revenue = 130 * 1000 * 100;
    }
    if (year == 7) {
        A->rate = 0.11;
    }
}

void live_changes_Bob(person* B, const unsigned int year) {
    if (year % 5 == 0)
        B->house = (B->house * 3 / 2);
    if (B->house / 100 < 50000 * 1000 && B->house / 100 > 20000 * 1000)
        B->tax = 0.0015;
    if (year == 12)
        B->rate = 0.1;
    B->spending = (long long)((double)(10* 1000 * 100 + annual_contrib +(double)(B)->house * B->tax/12));
}


void output ( person* client, unsigned int year) {
    printf("%s\n",client ->name);
    printf("current year - %d\n", year);
    printf("bank_capital: %llu rubles and %llu cents\n", client->bank/100, client-> bank % 100);
    printf("house_cost:%llu rubles and %llu cents\n", client->house/100, client-> house % 100);
    printf("bank_rate:%f\n", client->rate);
    printf("income: %llu and %llu cents\n", client->revenue/100, client-> revenue % 100);
}

void print_report ( person* A,  person* B) {
    if (B->bank + B->house > A->bank)
        printf("Bob more profitable than Alice on %llu rubles!\n", ((B->bank + B->house) - A->bank) / 100);
    else
        printf("Alice more profitable than Bob on %llu rubles!\n", (A->bank - (B->bank + B->house)) / 100);
}


void simulation () {
    person Alice;
    person Bob;
    init_Alice(&Alice);
    init_Bob(&Bob);
    for (unsigned int year = 1; year <= years; year++) {
        live_changes_Alice(&Alice,year);
        live_changes_Bob(&Bob,year);
        for (unsigned int month = 1; month <= 12; month++) {
            month_pay(&Alice);
            month_pay(&Bob);
        }
        output(&Alice,year);
        output(&Bob,year);
        print_report(&Alice,&Bob);
    }
}


void main (){
    simulation();
}