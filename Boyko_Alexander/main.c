#include <stdio.h>
#include "malloc.h"

// CONSTS
const int START_CASH = 1000000 * 100; // FIRST INPUT IN BANK (KOP)
const int FIRST_INPUT = 450000 * 100; // BOB'S INPUT IN FLAT (KOP)
const int FLAT_PRICE = 3000000 * 100; // FLAT'S PRICE (KOP)
const int SALARY = 150000 * 100; // SALARY FOR BOTH (KOP)
const int MONTH_CASH = 25957 * 100; // BOB'S MONTHLY WASTE ON FLAT (KOP)
const int PERIOD = 20; // YEARS
const int ALICE_WASTE = 40000 * 100; // ALICE'S MONTHLY WASTE (KOP)
const int BOB_WASTE = 10000 * 100; // BOB'S MONTHLY WASTE (KOP)

int year_percent = 7; // BANK'S PERCENT

struct Client {
    char *name;
    unsigned int month_increase; // KOP
    unsigned long long int bank; // KOP
};

struct Client Alice, Bob;

// PROCs AND FUNCs
void print_out(unsigned long long int bob_year, unsigned long long int alice_year, int year);
void print_res_string(unsigned long long int client_year);
void init();
unsigned long long int month_calc(unsigned long long int bank, unsigned int month_increase);
void year_cycle();
void month_cycle(int year);
void year_event(int year);

// MAIN FUNC
int main() {
    // VARs INITIALIZATION
    init();

    // CYCLE START
    year_cycle();

    return 0;
}

// INITIALIZATION BLOCK
void init(){
    // BOB START IPOTEKA
    Bob.name = malloc(6);
    Bob.name = "Bob";
    Bob.bank = START_CASH - FIRST_INPUT;
    Bob.month_increase = SALARY - BOB_WASTE - MONTH_CASH;

    // ALICE START BANK
    Alice.name = malloc(6);
    Alice.name = "Alice";
    Alice.bank = START_CASH;
    Alice.month_increase = SALARY - ALICE_WASTE;
}

// YEAR CYCLE BLOCK
void year_cycle(){
    int i;
    for (i = 0; i < PERIOD; i++) {
        // SOMETHING CHANGED
        year_event(i);

        month_cycle(i);
    }
}

// MONTH CYCLE BLOCK
void month_cycle(int year){
    int j;
    for (j = 0; j < 12; j++) {

        // ALICE MONTH
        Alice.bank = month_calc(Alice.bank, Alice.month_increase);

        // BOB MONTH
        Bob.bank = month_calc(Bob.bank, Bob.month_increase);
    }

    // RESULTS
    print_out(Bob.bank + FLAT_PRICE, Alice.bank, year);
}

// YEAR EVENT BLOCK
void year_event(int year){
    // PERCENT CHANGE AFTER 5 YEARS
    if (year == 4) {
        year_percent = 8;
    }
}

// CALCULATION FOR MONTH BLOCK
unsigned long long int month_calc(unsigned long long int bank, unsigned int month_increase){
    bank = (unsigned long long int)((long double)(bank + month_increase) * (1.f + year_percent * 0.01 / 12));
    return bank;
}

// OUTPUT BLOCK
void print_out(unsigned long long int bob_year, unsigned long long int alice_year, int year) {
    // TABLE HEAD
    if(year == 0){
        printf("%s                     %s                     Year \n",Bob.name,Alice.name);
    }

    // BOB'S RESULT
    print_res_string(bob_year);

    // ALICE"S RESULT
    print_res_string(alice_year);

    // YEAR OUTPUT
    printf("%0.2d \n", year + 1);
}

// INDIVIDUAL OUTPUT BLOCK
void print_res_string(unsigned long long int client_year) {
    unsigned long long int client_rub = client_year / 100;
    int client_kop = (int)(client_year % 100);
    printf("%0.2llu Rub %0.2d Kop       ", client_rub,client_kop);
}


