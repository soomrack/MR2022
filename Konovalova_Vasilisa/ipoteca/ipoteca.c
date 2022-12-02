#include <stdio.h>
#include "malloc.h"


const int capital = 1000000 * 100; // Первый вклад в банк
const int first_fee = 300000 * 100; // Первоначальный взнос для ипотеки
const int month_fee = 30000 * 100; // Ежемесячный взнос за квартиру
const int years = 20; // количество лет
const int flat = 3000000 * 100; // Цена квартиры


struct Client {
char *name;


unsigned long long int account;
unsigned int month_cash; // Деньги доступные в конце месяца (возможно положить на вклад)
int salary;
int routine_payment; // Траты на жизнь
int year_percent; // Проценты банка
};

struct Client Alice;
struct Client Bob;

void init_bob(struct Client *init_Bob);

void init_alice(struct Client *init_Alice);

void add_bank_percents(struct Client *client);

void salary_income(struct Client *client);

void remove_routine(struct Client *client);

void remove_month_fee(struct Client *client);

void deposit(struct Client *client);




void print_out(unsigned long long int bobs_cash, unsigned long long int alice_cash, int year);

void simulation();

void init_bob(struct Client *init_Bob) {
init_Bob->name = malloc(6);
init_Bob->name = "Bob";
init_Bob->account = capital - first_fee;
init_Bob->month_cash = 0;
init_Bob->salary = 50000 * 100;
init_Bob->routine_payment = 10000 * 100;


init_Bob->year_percent = 7;
}

void init_alice(struct Client *init_Alice) {
init_Alice->name = malloc(6);
init_Alice->name = "Alice";
init_Alice->account = capital;
init_Alice->month_cash = 0;
init_Alice->salary = 50000 * 100;
init_Alice->routine_payment = 40000 * 100;

init_Alice->year_percent = 7;
}


void add_bank_percents(struct Client *client) {
double month_percent = client->year_percent * 0.01 / 12;
client->month_cash += (unsigned int)((double)client->account * month_percent);
}

void salary_income(struct Client *client) {
client->month_cash += client->salary;
}

void remove_routine(struct Client *client) {
client->month_cash -= client->routine_payment;
}

void remove_month_fee(struct Client *client) {
client->month_cash -= month_fee;
}

void deposit(struct Client *client) {
client->account += client->month_cash;
client->month_cash = 0;
}

void print_out(unsigned long long int bobs_cash, unsigned long long int alice_cash, int year) {

    long long int amount_dif=bobs_cash-alice_cash;
    printf("Year: %d Bob has: %llu ,Alice has: %llu ",year+1,bobs_cash/100,alice_cash/100);
    if (amount_dif>0) {
        printf("%s`s strategy is better Difference in amount: %lld \n", Bob.name,amount_dif/100);
    }
    else if (amount_dif<0) {
        printf("%s`s strategy is better Difference in amount: %lld \n", Alice.name,amount_dif/100);
    }
    else {
        printf("Same results \n");
    }

}

void simulation() {
    for (int year = 0; year < years; year++) {

        for (int mon = 0; mon < 12; mon++) {
// BOB
            add_bank_percents(&Bob);
            salary_income(&Bob);
            remove_routine(&Bob);
            remove_month_fee(&Bob);
            deposit(&Bob);
// ALICE
            add_bank_percents(&Alice);
           salary_income(&Alice);
            remove_routine(&Alice);
            deposit(&Alice);
        }
        if (year+1==20) {
            Bob.account+=flat;
        }

        print_out(Bob.account , Alice.account, year);
    }
}

int main() {

    init_bob(&Bob);
    init_alice(&Alice);

    simulation();

    return 0;
}