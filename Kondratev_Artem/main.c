#include <stdio.h>
#include <stdint.h>


struct Data {

    int apartment_price;

    int start_capital;
    int salary;

    int alice_communal_service;
    int bob_communal_service;

    int first_payment;
    short mortgage_year;
    double mortgage_percent;

    int deposit_payment;
    double deposit_percent;

    int mortgage_month_fixed_payment;

};


struct Buyer {

    int communal_service;
    uint64_t balance;
    uint64_t rest;
    uint64_t yw;

};


void alice_init(struct Data data, struct Buyer alice) {

    alice.balance = data.start_capital;

}


void bob_init(struct Data data, struct Buyer bob) {

    bob.balance = data.start_capital + data.apartment_price - data.first_payment;
    bob.rest = data.apartment_price - data.first_payment;
}


void input_data(struct Data data, struct Buyer alice, struct Buyer bob) {

    data.apartment_price = (int)(9000000.32 * 100);

    data.start_capital = (int)(1000000.15 * 100);
    data.salary = (int)(150000.56 * 100);

    data.first_payment = (int)(300000.08 * 100);
    data.mortgage_year = 22;
    data.mortgage_percent = 8.0 / 100;  //  в долях

    data.deposit_payment = (int)(70000.16 * 100);
    data.deposit_percent = 0.2 / 100;  //  в долях

    bob.communal_service = (int)(40000.14 * 100);
    alice.communal_service = (int)(10000.02 * 100);

}


int mortgage_month_payment(struct Data data, struct Buyer bob) {

    int mortgage_month_fixed_payment = (data.apartment_price - data.first_payment) / (data.mortgage_year * 12);
    if((data.apartment_price - data.first_payment) % (data.mortgage_year * 12) > 0)
        data.mortgage_month_fixed_payment += 1;

    double mortgage_month_dynamic_payment = (double)bob.rest * data.mortgage_percent;
    if (mortgage_month_dynamic_payment - (int)mortgage_month_dynamic_payment > 0)
        mortgage_month_dynamic_payment = (int)mortgage_month_dynamic_payment + 1;

    int mortgage_month_payment = mortgage_month_fixed_payment + (int)mortgage_month_dynamic_payment;

    return mortgage_month_payment;

}


void output_data(struct Buyer alice, struct Buyer bob, short year) {

    double alice_balance_rub = (double)alice.balance / 100;
    double bob_balance_rub = (double)bob.balance / 100;

    double difference = alice_balance_rub - bob_balance_rub;

    printf("year %2d: ", year);
    printf("%14.2f%14.2f ", alice_balance_rub, bob_balance_rub);
    printf("  dif = %14.2f\n", difference);

}


void simulation() {

    struct Data data;

    struct Buyer alice;
    alice_init(data, alice);

    struct Buyer bob;
    bob_init(data, bob);

    input_data(data, alice, bob);

    mortgage_month_fixed_payment(data);

    for(short year = 0; year <= data.mortgage_year; year++) {

        for(short month = 1; month <= 12; month++) {



        }

    }

}


int main() {
    int64_t deposit, year_payment, year_deposit;
    long double delta_deposit, month_payment, flat_taxes;



    for (int i = 1; i <= 22; i++)
    {
        /*if(i == 3)
            cr_percent = 13.0;

        if(i == 5)
            b_balance += 150000000;

        if(i == 7)
            salary = 5000000;*/

        year_payment = 0;
        year_deposit = 0;

        /*flat_taxes = flat_cost * 0.5 / 100;
        if(flat_taxes - (int)flat_taxes > 0)
            flat_taxes = (int)flat_taxes + 1;*/

        for(int j = 0; j < 12; j++)
        {
            month_payment = credit_payment + (double)rest * cr_percent / 100;
            if(month_payment - (int)month_payment > 0)
                month_payment = (int)month_payment + 1;

            year_payment += (int)month_payment;
            rest -= (int)month_payment;

            delta_deposit = month_deposit + (double)deposit * dep_percent / 100;
            if(delta_deposit - (int)delta_deposit > 0)
                delta_deposit = (int)delta_deposit + 1;
            deposit += (int)delta_deposit;
            year_deposit += (int)delta_deposit;
        }

        b_balance += (salary - b_com_pay - (int)flat_taxes) * 12 - year_payment + year_deposit;

        a_balance += (salary - a_com_pay) * 12 + year_deposit;



    }
    return 0;
    }
