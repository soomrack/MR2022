#include <stdio.h>
char years = 20;
int annual_contrib = 60 * 1000 * 100;
int first_contrib = 300 * 1000;
struct person {
    unsigned long long bank;
    unsigned long long revenue;
    unsigned long spending;
    unsigned long long room;
    double rate;
    double tax;
};
void input_data(struct person* Alice, struct person* Bob)
{
    
    Alice->bank = 1000 * 1000 * 100;
    Alice->revenue = 150 * 1000 * 100;
    Alice->spending = 40 * 1000 * 100;
    Alice->rate = 0.08;
    Bob->tax = 0.001;
    Bob->bank = 1000 * 1000 * 100 - first_contrib;
    Bob->revenue = 150 * 1000 * 100;
    Bob->room = 7000 * 1000 * 100;
    Bob->spending = (long long)(10 * 1000 * 100 + annual_contrib + (double)(Bob)->room * Bob->tax/12);
    Bob->rate = 0.08;
}
void month_pay (struct person* buyer) {
    buyer->bank = (unsigned long long)((double)(((buyer->bank) - buyer-> spending + buyer -> revenue))*
            (1.f+ buyer->rate/12));
}
void changes(struct person* A, struct person* B, char year) {
    if (year % 5 == 0) {
        B->room = (B->room * 3 / 2);

    }
    if (B->room / 100 < 50000 * 1000 && B->room / 100 > 20000 * 1000) {
        B->tax = 0.0015;
    }

    if (year == 10) {
        A->revenue = 280 * 1000 * 100;
    }
    if (year == 12) {
        B->rate = 0.1;
    }
    B->spending = (long long)(10* 1000 * 100 +annual_contrib +(double)(B)->room * B->tax/12);
}
void output (struct person* A, struct person* B, char year) {
    printf("current year - %d\n", year);
    printf("Alice's actives at the end of year: %llu roubles and %d cents\n",
           (long long int) (A->bank / 100), (int) (A->bank % 100));
    printf("Bob's actives at the end of year: %llu roubles and %d cents\n",
           (long long int) ((B->bank + B->room) / 100), (int) ((B->bank % 100)));

    if (B->bank + B->room > A->bank)
        printf("Bob more profitable than Alice on %llu rubles!\n", ((B->bank + B->room) - A->bank) / 100);
    else
        printf("Alice more profitable than Bob on %llu rubles!\n", (A->bank - (B->bank + B->room)) / 100);
}

void body (struct person* Alice, struct person* Bob) {
    for (char year = 1; year <= years; year++) {
        changes(Alice,Bob,year);
        for (char month = 1; month <= 12; month++) {
            month_pay(Alice);
            month_pay(Bob);
        }
        output(Alice, Bob, year);
    }
}
void initialization () {
    struct person Alice;
    struct person Bob;
    input_data(&Alice,&Bob);
    body (&Alice,&Bob);
}
    int main() {
    initialization();
        return 0;
    }