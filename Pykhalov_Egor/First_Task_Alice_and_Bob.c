#include <stdio.h>
#include <math.h>                                                           //Подключаем библиотеку для математических операций

#define IF_ADD 1

struct person {
    int capital;
    int expenses;
    int income;
    double deposit;
};

struct person Alice = {1000000, 40000, 150000};
struct person Bob = {1000000, 10000, 150000};


int
    first_payment = 300000,                                             //Объявляем целичисленные переменные
    time=20,
    change_time = 3,
    b;

double
    credit_rate = 0.12,
    deposit_rate = 0.06,
    deposit_rate_addition = 0.06;



    double monthly_rate(double arg){
        double new_rate = pow(arg+1, 1.0/12.0) - 1;
        printf("Monthly rate: %lf\n", new_rate);
        return new_rate;
    }


    void start_info(){
        printf( "\n"                                                     //Выводим начальную информацию
                "Bob\n"
                "\n"
                "Capital: %d\n"
                "First payment: %d\n"
                "Expenses: %d\n"
                "Monthly income: %d\n"
                "\n"
                "Alice\n"
                "\n"
                "Capital: %d\n"
                "First payment: - \n"
                "Expenses: %d\n"
                "Income: %d\n"
                "\n"
                "Period: %d\n"

                ,Bob.capital, first_payment, Bob.expenses, Bob.income, Alice.capital, Alice.expenses, Alice.income, time );
    }


    int flat(int first_pay){
        int price = first_pay*10;
        printf("Full price of the flat: %d\n", price);
        return price;
    }


    double payment (int price, double rate, double t){                        //Высчитываем аннуитентный ежемесячный платеж по формуле
        double month_pay = (price*rate)/(1.0-pow((1.0+rate),(-t*12.0)));
        printf("Monthly payment: %lf\n", month_pay);
        return month_pay;
    }


    void deposit(){
        Alice.deposit = Alice.capital;                                          //Начальные суммы вкладов у Боба и Элис соответственно
        printf("Alice's start deposit: %lf\n", Alice.deposit);
        Bob.deposit = Bob.capital - first_payment;
        printf("Bob's start deposit: %lf\n", Bob.deposit);
    }


    double deposit_sum(char* name, int if_add, int time_change,  double deposit, double rate, int income, int expenses, double payment, double rate_addition){
        if (if_add)
        {
            for (int i=1; i<=time_change*12; i++)
            {
                deposit = deposit + deposit * rate;
                deposit = deposit + income - payment - expenses;
                printf("%s's Deposit: %lf After %d Month\n",name, deposit, i);
            }
            rate = monthly_rate(rate+rate_addition);
            printf("Rate was raised': %lf\n", rate);
            for (int a=1; a<=((time-time_change)*12); a++)
            {
                deposit = deposit + deposit * rate;
                deposit = deposit + income - payment - expenses;
                printf("%s's Deposit: %lf After %d Month\n",name, deposit, a);
            }
        }
        else
        {
            for (b = 1; b <= time * 12; b++)
            {
                printf("%s -s Deposit: %lf After %d Month\n",name, deposit, b);
                deposit = deposit + deposit * rate;
                deposit = deposit + income - payment - expenses;
            }
        }

        return deposit;
    }


int main() {
    start_info();

    credit_rate = monthly_rate(credit_rate);
    deposit_rate = monthly_rate(deposit_rate);

    int flat_price = flat(first_payment);
    double monthly_payment = payment(flat_price, credit_rate, time);

    deposit();
    double final_bob = deposit_sum("Bob", IF_ADD, change_time, Bob.deposit, deposit_rate, Bob.income, Bob.expenses, monthly_payment, deposit_rate_addition);
    double final_alice = deposit_sum("Alice", IF_ADD, change_time, Alice.deposit, deposit_rate, Alice.income, Alice.expenses, 0, deposit_rate_addition);

    printf ("\n\nAlice's final deposit sum: %lf ", final_alice);
    printf("\n\nBob's final deposit sum: %lf\n", flat_price+final_bob);

    return 0;
}
