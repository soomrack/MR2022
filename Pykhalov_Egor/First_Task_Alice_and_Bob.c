#include <stdio.h>
#include <math.h>  // Подключаем библиотеку для математических операций


struct Person {
    int capital;
    int expenses;
    int income;
    double payment;
    double deposit;
    double sum;
} Alice, Bob;


int first_payment = 100 * 300 * 1000;  // Объявляем переменные * 100 - так как копейки
int time=20;
int change_time = 3;


double credit_rate = 0.12;
double deposit_rate = 0.06;
double new_credit_rate = 0.18;

void person_alice_and_bob(){
    Alice.capital = 100 * 1000 * 1000;
    Alice.expenses = 100 * 40 * 1000;
    Alice.income = 100 * 150 * 1000;
    Alice.deposit = Alice.capital;

    Bob.capital = 100 * 1000 * 1000;
    Bob.expenses = 100 * 10 * 1000;
    Bob.income = 100 * 150 * 1000;
    Bob.deposit = Bob.capital - first_payment;
    printf("Alice's start deposit: %lf\n", Alice.deposit);  // DEBUG
    printf("Bob's start deposit: %lf\n", Bob.deposit);  // DEBUG
}

void start_info(){
        printf( "\n"  // Выводим начальную информацию
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

                ,Bob.capital,
                first_payment,
                Bob.expenses,
                Bob.income,
                Alice.capital,
                Alice.expenses,
                Alice.income,
                time );
}

void monthly_rate(){
    credit_rate = pow(credit_rate + 1, 1.0 / 12.0) - 1;
    printf("Monthly credit rate: %lf\n", credit_rate);  // DEBUG
    deposit_rate = pow(deposit_rate + 1, 1.0 / 12.0) - 1;
    printf("Monthly deposit rate: %lf\n", deposit_rate);  // DEBUG
    new_credit_rate = pow(new_credit_rate + 1, 1.0 / 12.0) - 1;
    printf("New Monthly credit rate: %lf\n", new_credit_rate);  // DEBUG
}

int flat_price(){  // Название отражает функцию, не смешивать функции
    int flat_price = first_payment * 10;
    return flat_price;
}

void flat_payment (int price){  // Слишком размытое название, одна перменная - не оч, пробелы вокруг знаков, Высчитываем аннуитентный ежемесячный платеж по формуле
    Alice.payment = 0;
    Bob.payment = (price * credit_rate) / (1.0 - pow((1.0 + credit_rate), (-time * 12.0)));
    printf("Monthly payment: %lf\n", Bob.payment);  // DEBUG
}

double deposit_calculation(char* namee, double depositt, double paymentt, double ratee, int incomee, int expensess, int ii){
    depositt += depositt * ratee;  // Разбить на функции, убрать вариативность
    depositt += incomee - paymentt - expensess;
    printf("%s's Deposit: %lf After %d Month\n",namee, depositt, ii);  // DEBUG
    return depositt;
}

void output(){
    printf ("\n\nAlice's final deposit sum: %lf ", Alice.sum);
    printf("\nBob's final deposit sum: %lf", Bob.sum + flat_price());
    printf("\nDifference is (Alice - Bob): %lf Rubles\n", (Alice.sum - Bob.sum + flat_price()) * 100);
}

double deposit_sum(char* name, double deposit, int income, int expenses, double payment){
    for (int i = 1; i <= time * 12; i++){
        deposit = deposit_calculation(name, deposit, payment, credit_rate, income, expenses, i);
    }
    printf("Rate was raised': %lf\n", new_credit_rate);// DEBUG
    for (int a = 1; a <= time - change_time * 12; a++){
        deposit = deposit_calculation(name, deposit, payment, new_credit_rate, income, expenses, a);
    }
    return deposit;
}

int main() {
    person_alice_and_bob();
    start_info();

    monthly_rate();
    flat_payment(flat_price());

    Bob.sum = deposit_sum("Bob", Bob.deposit, Bob.income, Bob.expenses, Bob.payment);
    Alice.sum = deposit_sum("Alice", Alice.deposit, Alice.income, Alice.expenses, Alice.payment);

    output();
}
