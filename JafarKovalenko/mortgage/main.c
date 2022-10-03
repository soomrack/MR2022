#include <stdio.h>
#include <math.h>

struct Human{
    unsigned int initial_capital;
    unsigned int income;
    unsigned int monthly_spending;
    unsigned int first_payment;
    unsigned int mortgage_payment;
    unsigned long long now_money;
};

const unsigned int APART_PRICE = 5000 * 1000 * 100; // стоимость квартиры в коп
const double APART_RATE = 0.1; // год ставка по ипотеке в процентах
const int YEAR = 20; // срок в годах
double bank_rate = 0.08; // год ставка в банке в процентах

unsigned int to_calc_mortgage_payment(unsigned int price, unsigned int first_pay, double rate, int time){
    double month_rate = rate / 12;
    unsigned month_pay = (int)(((price - first_pay) * month_rate) / (1 - pow((1 + month_rate), (time * -12))));
    return month_pay;
}

void alice_init(struct Human *alice){
    alice->initial_capital = 1000 * 1000 * 100; // в коп
    alice->income = 150 * 1000 * 100; // в коп
    alice->monthly_spending =   40000 * 100; // в коп
    alice->first_payment = 0;
    alice->mortgage_payment = 0;
    alice->now_money = alice->initial_capital;
}

void bob_init(struct Human *bob){
    bob->initial_capital = 1000 * 1000 * 100; // в коп
    bob->income = 150 * 1000 * 100; // в коп
    bob->monthly_spending =   10000 * 100; // в коп
    bob->first_payment = (unsigned int) (APART_PRICE * 0.15);
    bob->mortgage_payment = to_calc_mortgage_payment(APART_PRICE, bob->first_payment, APART_RATE, YEAR);
    bob->now_money = bob->initial_capital - bob->first_payment;
}

void pass_month_alice(struct Human *alice){
    alice->now_money = (unsigned long long) ((double) (alice->now_money + alice->income - alice->monthly_spending) * (1 + bank_rate / 12));
}

void pass_month_bob(struct Human *bob){
    bob->now_money = (unsigned long long) ((double) (bob->now_money + bob->income - bob->monthly_spending - bob->mortgage_payment) * (1 + bank_rate / 12));
}

void print_result(struct Human *alice, struct Human *bob){
    unsigned long long alice_rub = alice->now_money / 100;
    unsigned long long bob_rub = bob->now_money / 100;

    unsigned long long alice_kop = alice->now_money % 100;
    unsigned long long bob_kop = bob->now_money % 100;

    printf("\n%d years later...\n", YEAR);
    printf("Alice saved: %llu.%llu rub\n", alice_rub, alice_kop);
    printf("Bob saved: %llu.%llu rub + his own apartment", bob_rub, bob_kop);
}

void create_accident(int month, struct Human *alice, struct Human *bob){
    switch (month) {
        case 5 * 12: {
            bank_rate += 0.02;
            printf("After 5 years the bank rate increased by 2%\n");
        }
            break;
        case 10 * 12: {
            alice->income -= 20 * 1000 * 100;
            bob->income -= 20 * 1000 * 100;
            printf("After 10 years salary has decreased\n");
        }
            break;
    }
}

void simulation(){
    struct Human alice;
    struct Human bob;

    alice_init(&alice);
    bob_init(&bob);

    for (int month = 1; month < YEAR * 12 + 1; month++) {
        create_accident(month, &alice, &bob);

        pass_month_alice(&alice);
        pass_month_bob(&bob);
    }

    print_result(&alice, &bob);
}

int main() {
    simulation();
}
