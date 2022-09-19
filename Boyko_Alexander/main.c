#include <stdio.h>

const int start_cash = 1000000 * 100; // FIRST INPUT IN BANK (KOP)
const int first_input = 450000 * 100; // BOB'S INPUT IN FLAT (KOP)
const int flat_price = 3000000 * 100; // FLAT'S PRICE (KOP)
const int salary = 150000 * 100; // SALARY FOR BOTH (KOP)
const int month_cash = 25957 * 100; // BOB'S MONTHLY WASTE ON FLAT (KOP)
int year_percent = 7; // BANK'S PERCENT
const int period = 20; // YEARS
const int alice_prices = 40000 * 100; // ALICE'S MONTHLY WASTE (KOP)
const int bob_prices = 10000 * 100; // BOB'S MONTHLY WASTE (KOP)

void print_out(unsigned long long int bob_year, unsigned long long int alice_year, int year);

int main() {

    // BOB START IPOTEKA
    unsigned int bob_month_increase;
    unsigned long long int bob_bank = start_cash - first_input;
    bob_month_increase = salary - bob_prices - month_cash;

    // ALICE START BANK
    unsigned int alice_month_increase;
    unsigned long long int alice_bank = start_cash;
    alice_month_increase = salary - alice_prices;

    // TABLE HEAD OUTPUT
    printf("Bob                     Alice                     Year \n");

    // YEAR CYCLE
    int i;
    for (i = 0; i < period; i++) {
        // PERCENT CHANGE AFTER 5 YEARS
        if (i == 4) {
            year_percent = 8;
        }
        // MONTH CYCLE
        int j;
        for (j = 0; j < 12; j++) {
            // ALICE MONTH
            alice_bank = (unsigned long long int)((long double)(alice_bank + alice_month_increase) * (1.f + year_percent * 0.01 / 12));
            // BOB MONTH
            bob_bank = (unsigned long long int)((long double)(bob_bank + bob_month_increase) * (1.f + year_percent * 0.01 / 12));
        }

        // RESULTS
        print_out(bob_bank + flat_price, alice_bank, i);
    }
    return 0;
}

// OUTPUT BLOCK
void print_out(unsigned long long int bob_year, unsigned long long int alice_year, int year) {
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
