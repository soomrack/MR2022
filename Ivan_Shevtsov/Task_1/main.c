#include <stdio.h>
#include <math.h>

double mortgage_pay();
double deposit(int sum, int time_month, int add, double rate);

const int months = 20 * 12; //time bound

const int start_capital = 1000 * 100000; //money in kopeks
const int flat_beg = 0.8 * start_capital; //first mortgage pay (minimal value depend on flat_price)
const int flat_rent = 45 * 100000;
const int expenses  = 40 * 100000;
const int flat_price = 8 * 1000 * 100000;

const double mortgage_rate = 0.109 / 12; //monthly
const double inflation = 0.05 /12;


struct person {
    long long int capital;
    int income;
    double deposit_rate;
} person;

struct person Alice = {start_capital,  150 * 100000,0.07 / 12};
struct person Bob   = {start_capital,  150 * 100000,0.07 / 12};


double Alice_count() {
    Alice.income -= flat_rent + expenses;
    Alice.capital = deposit(Alice.capital, months, Alice.income, Alice.deposit_rate);
    return Alice.capital;
}

double Bob_count() {
    mortgage_pay();
    Bob.capital -= flat_beg;
    Bob.income -= mortgage_pay() + expenses;
    Bob.capital = deposit(Bob.capital, months, Bob.income, Bob.deposit_rate);
    return Bob.capital;
}

void output_results() {
    printf("Alice: %d \n", Alice.capital);
    printf("Bob: %d \n", Bob.capital);
}

void time_line() {

    double new_flat_price = deposit(flat_price, months, 0, inflation);
    printf("For %d months Alice managed to earn %1.lf thousand in the warehouse \n",  months, round(Alice_count() / 100000));
    printf("And Bob earned %1.lf thousand on deposit, while his apartment was studying with inflation adjusted to %1.lf millions \n\n",
           round(Bob_count() / 100000), round(new_flat_price / 100000000));
    long long int Alice_sum = Alice.capital;
    long long int Bob_sum = Bob.capital + new_flat_price;
    printf("Alice sum = %1.lf millions\n Bob sum = %1.lf millions\n", round(Alice_sum / 100000000), round(Bob_sum / 100000000));


}


double deposit(int sum, int time_month, int add, double rate) {
    double deposit = sum * (1 + rate);
    for (int month = 1; month <= time_month - 1; month++) {
        deposit = (deposit + add) * (1 + rate);
        if (month == 5 * 12){
            Alice.income += 20 * 100000; // income upgrade in 5 year
            Bob.income   += 20 * 100000;
        }
        if (month == 12 * 12){
            Alice.deposit_rate = 0.05 / 12; // deposit rate downgrade in 12 year
            Bob.deposit_rate   = 0.05 / 12;
        }
    }
    return deposit;
}


double mortgage_pay() {
    double mortgage_pay = ((flat_price - flat_beg) * mortgage_rate) / (1 - pow((1 + mortgage_rate),-months));
    return mortgage_pay;
}


int main() {
    time_line();
    return 1;
}
