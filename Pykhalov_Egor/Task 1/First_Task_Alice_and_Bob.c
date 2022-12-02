#include <stdio.h>
#include <math.h>  // Подключаем библиотеку для математических операций

struct Person {
    int capital;
    int expenses;
    int income;
    double payment;
    double deposit;
};

int first_payment = 300 * 1000 * 100;  // Объявляем переменные * 100 - так как копейки
int timeline = 20;
int change_time = 3;

double credit_rate = 0.12;
double deposit_rate = 0.06;
double new_deposit_rate = 0.4;

void init_Alice(struct Person *person) {
    person->capital = 100 * 1000 * 1000;
    person->expenses = 100 * 40 * 1000;
    person->income = 100 * 150 * 1000;
    person->deposit = person->capital;
}

void init_Bob(struct Person *person) {
    person->capital = 100 * 1000 * 1000;
    person->expenses = 100 * 10 * 1000;
    person->income = 100 * 150 * 1000;
    person->deposit = person->capital - first_payment;
    printf("Alice's start deposit: %lf\n", person->deposit);  // DEBUG
    printf("Bob's start deposit: %lf\n", person->deposit);  // DEBUG
}

void start_info(struct Person *alice, struct Person *bob){  // Выводим начальную информацию
        printf( "\n"
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
                "Period: %d\n",

                bob->capital,
                first_payment,
                bob->expenses,
                bob->income,
                alice->capital,
                alice->expenses,
                alice->income,
                timeline);
}

void monthly_rate(double *rate_old){  // Функция преобразования годового процента в месячный
    *rate_old = pow(*rate_old + 1, 1.0 / 12.0) - 1;
    printf("Monthly credit rate: %lf\n", *rate_old);  // DEBUG
}

int flat_price(){  // Вычисляем стоимость квартиры
    int flat_price = first_payment * 10;
    return flat_price;
}

void flat_payment (struct Person *alice, struct Person *bob, int price){  // Высчитываем аннуитентный ежемесячный платеж по формуле
    alice->payment = 0;
    bob->payment = (price * credit_rate) / (1.0 - pow((1.0 + credit_rate), (-timeline * 12.0)));
    printf("Monthly payment: %lf\n", bob->payment);  // DEBUG
}

void output(struct Person *alice, struct Person *bob){  // Вывод информации
    printf ("\n\nAlice's final deposit sum: %lf ", alice->deposit);
    printf("\nBob's final deposit sum: %lf", bob->deposit + flat_price());
    printf("\nDifference is (Alice - Bob): %lf Rubles\n", (alice->deposit - bob->deposit + flat_price()) * 100);
}

void bank_account_income_pp(struct Person *person) {  // Начисления по проценту
     person->deposit += person->deposit * deposit_rate;
}

void salary(struct Person *person) {  // Зачисление зп
    person->deposit += person->income;
}

void home_bills(struct Person *person) {  // Оплата ЖКХ
    person->deposit -= person->expenses;
}

void mortgage_payment(struct Person *person) {  // Плата по ипотеке
    person->deposit -= person->payment;
}

void simulation() {  // Функция симуляции
    struct Person Alice;
    struct Person Bob;

    struct Person *A = &Alice;
    struct Person *B = &Bob;

    init_Alice(&Alice);
    init_Bob(&Bob);

    start_info(&Alice, &Bob);

    monthly_rate(&credit_rate);
    monthly_rate(&deposit_rate);
    monthly_rate(&new_deposit_rate);

    flat_payment(&Alice, &Bob, flat_price());

    for(int year = 1; year < timeline; year++) {
        for(int month = 1; month <= 12; month++) {
            bank_account_income_pp(&Alice);
            bank_account_income_pp(&Bob);

            salary(A);
            salary(&Bob);

            home_bills(&Alice);
            home_bills(&Bob);

            mortgage_payment(&Alice);
            mortgage_payment(&Bob);

            if(year == change_time && month == 1) {
                deposit_rate = new_deposit_rate;
            }
        }
    }
    output(&Alice, &Bob);
}

int main() {
    simulation();
}
