#include <stdio.h>


struct Buyer {

    int start_capital;  //  копейки
    int salary;  //  копейки
    int communal_service;  //  копейки
    int taxes;  //  копейки

    int apartment_price;  //  копейки
    int first_payment;  //  копейки
    short mortgage_year;
    double mortgage_percent;  //  в долях
    int mortgage_month_payment;  //  копейки

    int deposit_payment;  //  копейки
    double deposit_percent;  //  в долях
    long long int deposit_balance;  //  копейки

    long long int balance;  //  копейки
    long int rest;  //  копейки

};


void alice_init(struct Buyer *alice, int apartment_price, int salary, int alice_communal_service,
                int deposit_payment, double deposit_percent, int start_capital) {

    alice->apartment_price = apartment_price;

    alice->start_capital = start_capital;
    alice->salary = salary;
    alice->communal_service = alice_communal_service;

    alice->deposit_payment = deposit_payment;
    alice->deposit_percent = deposit_percent;

}


void bob_init(struct Buyer *bob, int apartment_price, int salary, int first_payment, int bob_communal_service,
        short mortgage_year, double mortgage_percent, int deposit_payment, double deposit_percent, int start_capital) {

    bob->apartment_price = apartment_price;

    bob->start_capital = start_capital;
    bob->salary = salary;
    bob->communal_service = bob_communal_service;

    bob->first_payment = first_payment;
    bob->mortgage_year = mortgage_year;
    bob->mortgage_percent = mortgage_percent;

    bob->deposit_payment = deposit_payment;
    bob->deposit_percent = deposit_percent;

    bob->balance = bob->start_capital - bob->first_payment + bob->apartment_price;
    bob->rest = bob->apartment_price - bob->first_payment;

}


void input_data(struct Buyer *alice, struct Buyer *bob) {

    int apartment_price = (int)(9000000.32 * 100);  //  копейки

    int start_capital = (int)(1000000.15 * 100);  //  копейки
    int salary = (int)(150000.56 * 100);  //  копейки

    int first_payment = (int)(300000.08 * 100);  //  копейки
    short mortgage_year = 22;
    double mortgage_percent = 1.0;

    int deposit_payment = (int)(70000.16 * 100);  //  копейки
    double deposit_percent = 0.2 / 100;  //  в долях

    int alice_communal_service = (int)(40000.02 * 100);  //  копейки
    int bob_communal_service = (int)(10000.04 * 100);  //  копейки

    alice_init(alice, apartment_price, salary, alice_communal_service,
    deposit_payment, deposit_percent, start_capital);

    bob_init(bob, apartment_price, salary, first_payment, bob_communal_service,
    mortgage_year, mortgage_percent, deposit_payment, deposit_percent, start_capital);

}


int specific_rounding(double parameter) {

    if(parameter - (int)parameter > 0)
        parameter = (int)parameter + 1;

    return (int)parameter;

}


void taxes(struct Buyer *bob) {

    const double taxes_percent = 0.1;
    double taxes = bob->apartment_price * taxes_percent / 100;
    bob->taxes = specific_rounding(taxes);

}


int mortgage_month_payment_foo(struct Buyer *bob) {

    double mortgage_month_fixed_payment = (double)(bob->apartment_price - bob->first_payment)/(bob->mortgage_year * 12);
    int rounded_mortgage_month_fixed_payment = specific_rounding(mortgage_month_fixed_payment);

    double mortgage_month_dynamic_payment = (double)bob->rest * bob->mortgage_percent / 100;
    int rounded_mortgage_month_dynamic_payment = specific_rounding(mortgage_month_dynamic_payment);

    bob->mortgage_month_payment = rounded_mortgage_month_fixed_payment + rounded_mortgage_month_dynamic_payment;
    bob->rest -= rounded_mortgage_month_fixed_payment;

}


void changing_balance(struct Buyer *buyer) {

    int income = buyer->salary;
    int expenses = buyer->deposit_payment + buyer->communal_service + buyer->mortgage_month_payment + buyer->taxes;
    buyer->balance += income - expenses;

}


void changing_deposit_balance(struct Buyer *buyer, short month) {

    buyer->deposit_balance += buyer->deposit_payment;

    if(month == 12) {

        double deposit_balance = (double)buyer->deposit_balance * (1 + buyer->deposit_percent / 100);
        buyer->deposit_balance = specific_rounding(deposit_balance);

    }

}


void output_data(struct Buyer *alice, struct Buyer *bob, short year) {

    unsigned long long int alice_actives = alice->balance + alice->deposit_balance;
    double alice_actives_rub = (double)alice_actives / 100;

    unsigned long long int bob_actives = bob->balance + bob->deposit_balance;
    double bob_actives_rub = (double)bob_actives / 100;

    double difference = alice_actives_rub - bob_actives_rub;

    printf("year %2d: ", year);
    printf("%14.2f%14.2f ", alice_actives_rub, bob_actives_rub);
    printf("  dif = %14.2f\n", difference);

}


void apartment_price_increasing(struct Buyer *buyer, const double apartment_increase_percent) {

    buyer->balance -= buyer->apartment_price;
    double apartment_price = buyer->apartment_price * (1 + apartment_increase_percent / 100);
    buyer->apartment_price = specific_rounding(apartment_price);
    buyer->balance += buyer->apartment_price;

}


void life_changes(struct Buyer *alice, struct Buyer *bob, short year) {

    if(year == 3)
        bob->mortgage_percent = 1.2;

    if(year == 5)
        apartment_price_increasing(bob, 8.0);

    if(year == 7)
        alice->salary = 25000000;

}


void simulation() {

    struct Buyer alice;

    struct Buyer bob;

    input_data(&alice, &bob);

    for(short year = 1; year <= bob.mortgage_year; year++) {

        life_changes(&alice, &bob, year);

        for(short month = 1; month <= 12; month++) {

            mortgage_month_payment_foo(&bob);
            taxes(&bob);

            changing_balance(&alice);
            changing_balance(&bob);

            changing_deposit_balance(&alice, month);
            changing_deposit_balance(&bob, month);

        }

        output_data(&alice, &bob, year);

    }

}


int main() {

    simulation();

    return 0;
}