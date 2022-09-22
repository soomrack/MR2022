#include <stdio.h>
#include <math.h>
#include "malloc.h"

int term = 20 * 12;

double deposit_rate = 6;  // Процент годовых
double k_deposit_per_month = 0;

double credit_rate = 10;  // Процент по кредиту
double k_credit_per_month = 0;

double house_rotate = 2;  // Процент повышения стоимости жилья
double k_house_per_month = 0;

double house_tax = 2.5;  // Процент налогового изъятия с жилья
double k_house_tax_pm = 0;


struct person{

    char name[10];                          // Имя
    long int beginings;                     // Начальные сбережения
    long int credit;                        // Сумма кредиторской задолжности в банке
    long int first_pay;                     // Сумма первого платежа
    long int evry_month_pay;                // Сумма ежемесячного платежа по кредиту
    int loan_term;                          // Срок кредитования (в месяцах)
    long int house_spending;                // Ежемесячные затраты на жилье и пр.
    long int income;                        // Ежемесячный доход
    long int bank;                          // Счет в банке (на эту сумму начисляется процент (первая часть всех активов)
    long int house;                         // Стоимость купленного имущества (вторая часть всех активов)

};

struct person *people = NULL;
int size_of_people = 0;

void initialization();
void all_changes(int current_month);
void monthly_events();
void yearly_events();
void output(int current_year);

int main() {
    initialization();

    for (int month = 1; month <= term; month++){

        all_changes(month);
        monthly_events();

        if (month % 12 == 0){
            yearly_events();
            output(month / 12);
        }

    }
    return 0;
}


double k_per_month(double per_year){
    return 1 + per_year / 100 / 12;
}

void change_percent(int f, double *variable, double *k_variable, double new_count) {
    if (f) {
        *variable = new_count;
        *k_variable = k_per_month(new_count);
    }
    /*  В переменную f подается запрос вида: i == month
     *  где month - любое целое число.
     *  Это значит, что, когда наступит month_ый месяц, то переменная variable - какой-либо процент - изменится
     *  на новое new_count, а также будет перерасчитан ежемесячный коэффициент.
     */
}

void change_others(int f, long int *value, long int new_value){
    if (f){
        *value = new_value;
    }
}


void all_percents_per_month() {

    k_deposit_per_month = k_per_month(deposit_rate);
    k_credit_per_month = k_per_month(credit_rate);
    k_house_per_month = k_per_month(house_rotate);
    k_house_tax_pm = k_per_month(house_tax);

}


void initialization() {
    all_percents_per_month();

    struct person Alice = {"Alice",1000000, 0, 0, 0, 0, 40000, 150000, 0, 0};
    Alice.bank = Alice.beginings;
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Alice;
    size_of_people++;

    struct person Bob = {"Bob", 1000000, 8000000, 300000, 0, 20*12, 10000, 150000, 0, 0};
    Bob.bank = Bob.beginings - Bob.first_pay;
    Bob.house = Bob.credit;
    Bob.evry_month_pay =  ceil(Bob.credit * ((k_credit_per_month-1) + (k_credit_per_month-1) / (pow(k_credit_per_month,Bob.loan_term) - 1)));
    // расчет ежемесячного платежа осуществляется по формуле из интернета
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Bob;
    size_of_people++;

    struct person Carol = {"Carol", 500000, 0, 0, 0, 0, 30000, 180000, 0, 0};
    Carol.bank = Carol.beginings;
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Carol;
    size_of_people++;

}


void all_changes(int current_month) {

    change_percent(current_month == 3 * 12, &deposit_rate, &k_deposit_per_month, 8);
    change_percent(current_month == 5 * 12, &house_rotate, &k_house_per_month, 3);
    change_others(current_month == 10 * 12, &people[0].income, 200000);

}


void monthly_events(){
    for (int i = 0; i < size_of_people; i++){
        long int free_money = people[i].income - people[i].house_spending - people[i].evry_month_pay;
        people[i].credit = round(people[i].credit * k_credit_per_month);
        if (people[i].credit > people[i].evry_month_pay) {
            people[i].credit = people[i].credit - people[i].evry_month_pay;
        } else {
            free_money = free_money + people[i].evry_month_pay - people[i].credit;
            people[i].credit = 0;
        }
        people[i].bank = floor(people[i].bank * k_deposit_per_month) + free_money;
        people[i].house = floor(people[i].house * k_house_per_month);
    }

}


void yearly_events() {

    for (int i = 0; i < size_of_people; i++){
        people[i].bank -= ceil(people[i].house * (house_tax / 100));
    }

}


void output(int current_year) {

    printf("Year: %d\n", current_year);

    for (int i = 0; i < size_of_people; i++) {
        printf("\t%s's assets: %ld  (contribution: %ld, house: %ld)\n", people[i].name, people[i].bank + people[i].house, people[i].bank, people[i].house);
        if (people[i].evry_month_pay > 0) {

            if (people[i].credit > 0) {
                printf("\t\t%s has to pay off the loan: %ld \n", people[i].name, people[i].credit);
            } else {
                printf("\t\t%s has finished his loan!\n", people[i].name);
            }
        }

    }
}