#include <stdio.h>
#include <math.h>

const int start_cash = 1000000; // FIRST INPUT IN BANK
const int first_input = 450000; // BOB'S INPUT IN FLAT
const int flat_price = 3000000; // FLAT'S PRICE
const int salary = 150000; // SALARY FOR BOTH
const float month_cash = 25957; // BOB'S MONTHLY WASTE ON FLAT
float year_percent = 7; // BANK'S PERCENT
const int period = 20; // Years
const int alice_prices = 40000; // ALICE'S MONTHLY WASTE
const int bob_prices = 10000; // BOB'S MONTHLY WASTE

//float bob_money;
//float alice_money;

void print_out(double bob_year, double alice_year, int year);

int main() {
    float bob_month;
    float alice_month;

    // BOB START
    double bob_year = (float)start_cash + (float)flat_price - (float)first_input;
    double bob_bank = (float)start_cash - (float)first_input;

    // ALICE START
    double alice_year = (float)start_cash;
    double alice_bank = (float)start_cash;

    // BOB IPOTEKA
    bob_month = (float)salary - (float)bob_prices - month_cash;

    // ALICE BANK
    alice_month = (float)salary - (float)alice_prices;

    printf("Bob                  Alice               Year");
    printf("\n");

    // По прошествии 5-ти лет вклад изменился в большую сторону



    int i;
    for (i = 0; i < period; i++) {

        if (i == 4) {
            year_percent = 8;
        }

        // ALICE YEAR
        double just_perc_alice = alice_bank * 0.01 * year_percent + 12 * alice_month;
        alice_bank += just_perc_alice;
        alice_year += alice_month * 12 + just_perc_alice;

        // BOB YEAR
        double just_perc_bob = bob_bank * 0.01 * year_percent + 12 * bob_month;
        bob_bank += just_perc_bob;
        bob_year += 12 * bob_month + just_perc_bob;

        // RESULTS

        print_out(bob_year, alice_year, i);
    }

    return 0;
}

void print_out(double bob_year, double alice_year, int year) {
    double bob_rub;
    double bob_kop = modf(bob_year, &bob_rub) * 100;
    printf("%0.2d", (int)bob_rub);
    printf(" Rub ");
    printf("%0.2d", (int)bob_kop);
    printf(" Kop");

    printf("    ");

    double alice_rub;
    double alice_kop = modf(alice_year, &alice_rub) * 100;
    printf("%0.2d", (int)alice_rub);
    printf(" Rub ");
    printf("%0.2d", (int)alice_kop);
    printf(" Kop");
    printf("        ");
    printf("%0.2d", year + 1);
    printf("\n");
}
