#include <stdio.h>
#include <math.h>  // Библиотека для математических операций

struct Person {  // Структура (класс) человека
    int capital;
    int expenses;
    int income;
    double payment;
    double deposit;
};

int first_payment = 300000 * 100;  // Объявление переменных (денежные величины в копейках)
int flat_price = 3000000 * 100;
int timeline = 20;
int change_time = 5;

double credit_rate = 0.12;
double deposit_rate = 0.06;
double new_deposit_rate = 0.05;

void init_Alice(struct Person *person) {  // Функция для извлечения структурных переменных Alice
    person->capital = 1000000 * 100;
    person->expenses = 40000 * 100;
    person->income = 150000 * 100;
    person->deposit = person->capital;
}

void init_Bob(struct Person *person) {  // Функция для извлечения структурных переменных Bob
    person->capital = 1000000 * 100;
    person->expenses = 10000 * 100;
    person->income = 150000 * 100;
    person->deposit = person->capital - first_payment;
}

void input (struct Person *alice, struct Person *bob){  // Функция для вывода начальной информации
    printf ("\nPeriod: %d years (%d months)\n"
            "\nAlice\nCapital: %d\nDeposit: %.0lf\nFirst payment: - \nMonthly expenses: %d\nMonthly income: %d\n"
            "\nBob\nCapital: %d\nDeposit: %.0lf\nFirst payment: %d\nMonthly expenses: %d\nMonthly income: %d\n\n",
            timeline, 12 * timeline,
            alice->capital, alice->deposit, alice->expenses, alice->income,
            bob->capital, bob->deposit, first_payment, bob->expenses, bob->income);
}

void monthly_rate(double *rate){  // Функция для преобразования годового процента в месячный
    *rate = pow(*rate + 1, 1.0 / 12.0) - 1;
    printf("%lf\n", *rate);
}

void flat_payment (struct Person *alice, struct Person *bob, int price){
                                        // Функция для вычисления аннуитентного ежемесячого платежа по формуле
    alice->payment = 0;
    bob->payment = (price * credit_rate) / (1.0 - pow((1.0 + credit_rate), (-timeline * 12.0)));
    printf("\nMonthly payment: %.0lf\n", bob->payment);
}

void deposit_operations(struct Person *person) {  // Функция для вычисления операций с депозитом
    person->deposit += person->deposit * deposit_rate;  // Капитализация вклада
    person->deposit += person->income;  // Зачисление ЗП
    person->deposit -= person->expenses;   // Оплата проживания
    person->deposit -= person->payment;  // Плата по ипотеке
}

void output(struct Person *alice, struct Person *bob){  // Вывод информации
    printf ("\nAlice's final deposit sum after buying a flat: %.0lf ", alice->deposit - flat_price);
    printf("\nBob's final deposit sum: %.0lf", bob->deposit);
    printf("\nDifference between Alice and Bob: %.0lf\n", alice->deposit - flat_price - bob->deposit);
}

void simulation() {  // Функция симуляции
    struct Person Alice;
    struct Person Bob;

    struct Person *A = &Alice;
    struct Person *B = &Bob;

    init_Alice(A);
    init_Bob(B);

    input(A, B);

    printf("Monthly credit rate: ");
    monthly_rate(&credit_rate);
    printf("Monthly deposit rate: ");
    monthly_rate(&deposit_rate);
    printf("Monthly new deposit rate: ");
    monthly_rate(&new_deposit_rate);

    printf("\nPrice of a flat: %d", flat_price);
    flat_payment(A, B, flat_price);

    for(int year = 1; year < timeline; year++) {
        for(int month = 1; month <= 12; month++) {
            deposit_operations(A);
            deposit_operations(B);
            if(year == change_time && month == 1) {
                deposit_rate = new_deposit_rate;
            }
        }
    }
    output(&Alice, &Bob);
}

int main() {
    simulation();
    return 0;
}
