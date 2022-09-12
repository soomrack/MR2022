#include <stdio.h>
#include <math.h>

struct person{

    long int beginings;
    long int credit;
    long int first_pay;
    long int evry_month_pay;
    long int house_spending;
    long int income;
    long int bank;
    long int house;

};

double k_per_month(double per_year){
    return 1 + per_year / 100 / 12;
}

void change_percent(int f, double *variable, double *k_variable, double new_count) {
    if (f) {
        *variable = new_count;
        *k_variable = k_per_month(new_count);
    }
    /*  В переменную f подается запрос вида: i % 12 == year
     *  где year - любое целое число.
     *  Это значит, что, когда наступит year_ый год, то переменная variable - какой-либо процент - изменится
     *  на новое new_count, а также будет перерасчитан ежемесячный коэффициент.
     */
}

void change_others(int f, long int *value, long int new_value){
    if (f){
        *value = new_value;
    }
}


int main() {
    int term = 20 * 12;
    double deposit_rate = 6;  /* Процент годовых */
    double k_deposit_per_month = k_per_month(deposit_rate);

    double credit_rate = 10; /* Процент по кредиту */
    double k_credit_per_month = k_per_month(credit_rate);

    double house_rotate = 2;
    double k_house_per_month = k_per_month(house_rotate);

    double house_tax = 5;      // налог на имущество, который съедает по 5% раз в год.

    //printf("%f, %f\n", k_deposit_per_month, k_credit_per_month);

    struct person Alice = {1000000, 0, 0, 0, 40000, 150000, 0, 0};
    Alice.bank = Alice.beginings;

    struct person Bob = {1000000, 8000000, 300000, 0, 10000, 150000, 0, 0};
    Bob.bank = Bob.beginings - Bob.first_pay;
    Bob.house = Bob.credit;
    Bob.evry_month_pay =  ceil(Bob.credit * ((k_credit_per_month-1) + (k_credit_per_month-1) / (pow(k_credit_per_month,term) - 1)));
                        // расчет ежемесячного платежа осуществляется по формуле из интернета.

    //printf("%d\n", Bob.evry_month_pay);

    for (int i = 1; i <= term; i++){
        change_percent( i / 12 == 3, &deposit_rate, &k_deposit_per_month, 8);
        change_percent(i / 12 == 5, &house_rotate, &k_house_per_month, 3);
        change_others(i / 12 == 10, &Alice.income, 200000);

        int free_money_a = Alice.income - Alice.house_spending;
        Alice.bank = floor(Alice.bank * k_deposit_per_month) + free_money_a;
        Alice.house = floor(Alice.house * k_house_per_month);

        int free_money_b = Bob.income - Bob.house_spending - Bob.evry_month_pay;
        Bob.credit = round(Bob.credit * k_credit_per_month);
        if (Bob.credit >= Bob.evry_month_pay){
            Bob.credit = Bob.credit - Bob.evry_month_pay;
        } else {
            free_money_b += Bob.evry_month_pay - Bob.credit;
            Bob.credit = 0;
        }
        Bob.bank = floor(Bob.bank * k_deposit_per_month) + free_money_b;
        Bob.house = floor(Bob.house * k_house_per_month);

        if (i % 12 == 0){
            Bob.house = floor(Bob.house * (1 - house_tax / 100));
            Alice.house = floor(Alice.house * (1 - house_tax / 100));

            printf("Year: %d\n", (int) i/12);
            printf("\tAlice's assets: %d  (contribution: %d, house: %d)\n", (int) Alice.bank + Alice.house, Alice.bank, Alice.house);
            printf("\tBob's assets: %d  (contribution: %d, house: %d)\n", (int) Bob.bank + Bob.house, Bob.bank, Bob.house);

            if (Bob.credit > 0){
                printf("\t\tBob has to pay off the loan: %d \n", Bob.credit);
            } else {
                printf("\t\tBob has finished his loan!\n");
            }
        }

    }
    return 0;
}
