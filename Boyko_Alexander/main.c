#include <stdio.h>

// CONSTS
const int start_cash = 1000000 * 100; // FIRST INPUT IN BANK (KOP)
const int first_input = 450000 * 100; // BOB'S INPUT IN FLAT (KOP)
const int flat_price = 3000000 * 100; // FLAT'S PRICE (KOP)
const int salary = 150000 * 100; // SALARY FOR BOTH (KOP)
const int month_cash = 25957 * 100; // BOB'S MONTHLY WASTE ON FLAT (KOP)
const int period = 20; // YEARS
const int alice_prices = 40000 * 100; // ALICE'S MONTHLY WASTE (KOP)
const int bob_prices = 10000 * 100; // BOB'S MONTHLY WASTE (KOP)

int year_percent = 7; // BANK'S PERCENT

// VARIABLES FOR CYCLE
unsigned int bob_month_increase; // KOP
unsigned long long int bob_bank; // KOP
unsigned int alice_month_increase; // KOP
unsigned long long int alice_bank; // KOP

// PROCs AND FUNCs
void print_out(unsigned long long int bob_year, unsigned long long int alice_year, int year);
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
    bob_bank = start_cash - first_input;
    bob_month_increase = salary - bob_prices - month_cash;

    // ALICE START BANK
    alice_bank = start_cash;
    alice_month_increase = salary - alice_prices;
}

// YEAR CYCLE BLOCK
void year_cycle(){
    int i;
    for (i = 0; i < period; i++) {

        year_event(i);

        month_cycle(i);
    }
}

// MONTH CYCLE BLOCK
void month_cycle(int year){
    int j;
    for (j = 0; j < 12; j++) {

        // ALICE MONTH
        alice_bank = month_calc(alice_bank, alice_month_increase);

        // BOB MONTH
        bob_bank = month_calc(bob_bank, bob_month_increase);
    }

    // RESULTS
    print_out(bob_bank + flat_price, alice_bank, year);
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
        printf("Bob                     Alice                     Year \n");
    }

    // BOB'S RESULT
    unsigned long long int bob_rub = bob_year / 100;
    int bob_kop = (int)(bob_year % 100);
    printf("%0.2llu Rub %0.2d Kop       ", bob_rub,bob_kop);

    // ALICE"S RESULT
    unsigned long long int alice_rub = alice_year / 100;
    int alice_kop = (int)(alice_year % 100);
    printf("%0.2llu Rub %0.2d Kop       ", alice_rub,alice_kop);

    // YEAR OUTPUT
    printf("%0.2d \n", year + 1);
}
