#include <stdio.h>
#include <math.h>
#include "malloc.h"

int period = 20 * 12;

double deposit_rate = 6.0;  // Процент годовых
double k_deposit_per_month = 0;

double credit_rate = 10.0;  // Процент по кредиту
double k_credit_per_month = 0;

double house_rotate = 2.0;  // Процент повышения стоимости жилья
double k_house_per_month = 0;

double house_tax = 2.5;  // Процент налогового изъятия с жилья
double k_house_tax_pm = 0;


struct person{

    char *name;                                           // Имя
    unsigned long long int beginings;                     // Начальные сбережения
    unsigned long long int credit;                        // Сумма кредиторской задолжности в банке
    unsigned int loan_term;                               // Срок кредитования (в месяцах)
    unsigned long long int first_fee;                     // Сумма первого платежа
    unsigned long long int evry_month_pay;                // Сумма ежемесячного платежа по кредиту
    unsigned long long int income;                        // Ежемесячный доход
    unsigned long long int house_spending;                // Ежемесячные затраты на жилье и пр.
    unsigned long long int bank;                          // Счет в банке (на эту сумму начисляется процент (первая часть всех активов)  balance, count
    unsigned long long int house;                         // Стоимость купленного имущества (вторая часть всех активов)

};

struct person *people = NULL;
int size_of_people = 0;


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
    // события перенести в то место, где что-то конкретно отображается
}

void change_others(int f, unsigned long long int *value, unsigned long long int new_value){
    if (f){
        *value = new_value;
    }
}

unsigned int annuetet_pay(struct person man){
    return ceil(man.credit * ((k_credit_per_month-1) + (k_credit_per_month-1) / (pow(k_credit_per_month,man.loan_term) - 1)));
}

void initialization() {
    k_deposit_per_month = k_per_month(deposit_rate);
    k_credit_per_month = k_per_month(credit_rate);
    k_house_per_month = k_per_month(house_rotate);
    k_house_tax_pm = k_per_month(house_tax);

    struct person Alice;
    Alice.name = "Alice";
    Alice.beginings = 1 * 1000 * 1000 * 100;
    Alice.credit = 0;
    Alice.loan_term = 0;
    Alice.first_fee = 0;
    Alice.evry_month_pay = 0;
    Alice.income = 150 * 1000 * 100;
    Alice.house_spending = 40 * 1000 * 100;
    Alice.bank = Alice.beginings;
    Alice.house = 0;
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Alice;
    size_of_people++;

    struct person Bob;
    Bob.name = "Bob";
    Bob.beginings = 1 * 1000 * 1000 * 100;
    Bob.credit = 8 * 1000 * 1000 * 100;
    Bob.first_fee = 300 * 1000 * 100;
    Bob.loan_term = 20 * 12;
    Bob.evry_month_pay = annuetet_pay(Bob);
    Bob.income = 150 * 1000 * 100;
    Bob.house_spending = 10 * 1000 * 100;
    Bob.bank = Bob.beginings - Bob.first_fee;
    Bob.house = Bob.credit;
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Bob;
    size_of_people++;

    struct person Carol;
    Carol.name = "Carol";
    Carol.beginings = 100 * 1000 * 100;
    Carol.credit = 0;
    Carol.first_fee = 0;
    Carol.loan_term = 0;
    Carol.evry_month_pay = 0;
    Carol.income = 100 * 1000 * 100;
    Carol.house_spending = 30 * 1000 * 100;
    Carol.bank = Carol.beginings;
    Carol.house = 0;
    people = (struct person*) realloc(people, (size_of_people + 1) * sizeof(struct person));
    people[size_of_people] = Carol;
    size_of_people++;

}

void all_changes (unsigned int current_month){

    change_percent(current_month == 3 * 12, &deposit_rate, &k_deposit_per_month, 8.0);
    change_percent(current_month == 5 * 12, &house_rotate, &k_house_per_month, 3.0);
    change_others(current_month == 10 * 12, &people[0].income, 200 * 1000 * 100);

}

void monthly_events(unsigned int current_month){

    all_changes(current_month);

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

char * vid(unsigned long long int arg){
    char * rez;
    unsigned long long int temp = arg;
    unsigned int len_arg = 0;
    do{
        len_arg ++;
        temp /= 10;
    } while (temp != 0);
    len_arg += len_arg / 3;
    rez = (char *) malloc((1 + len_arg) * sizeof(char));
    temp = arg;
    for (int i = len_arg - 1; i >= 0; i--){
        if (i == len_arg - 3){
            rez[i] = ',';
        } else if (((len_arg - i - 7) % 4 == 0) && (i < len_arg - 5)) {
            rez[i] = '\'';
        } else {
            rez[i] = temp % 10 + 48;
            temp /= 10;
        }
    }
    rez[len_arg] = '\0';
    return rez;
}

void output(int current_year) {

    printf("Year: %d\n", current_year);

    for (int i = 0; i < size_of_people; i++) {
        printf("\t%s's assets: %s  (contribution: %s, house: %s)\n",
               people[i].name,
               vid(people[i].bank + people[i].house),
               vid(people[i].bank),
               vid(people[i].house));
        if (people[i].evry_month_pay > 0) {

            if (people[i].credit > 0) {
                printf("\t\t%s has to pay off the loan: %s \n",
                       people[i].name, vid(people[i].credit));
            } else {
                printf("\t\t%s has finished his loan!\n", people[i].name);
            }
        }

    }
}

void results(){
    printf("\n\nAs a result: \n");
    if (size_of_people > 0){
        struct person winner_sum = people[0];
        struct person winner_house = people[0];

        for (int i = 1; i < size_of_people; i++){
            if (people[i].bank > winner_sum.bank){
                winner_sum = people[i];
            }
            if (people[i].house > winner_house.house){
                winner_house = people[i];
            }
        }

        if (winner_sum.name != winner_house.name){
            printf("\t\t%s earned the biggest cash, but %s has the most expensive house",
                   winner_sum.name, winner_house.name);
        } else {
            printf("\t\t%s has the biggest fortune and the most expensive house", winner_sum.name);
        }
    } else {
        printf("\t\tOps, there was no competition!");
    }

}


int main() {
    initialization();

    for (int month = 1; month <= period; month++){

        monthly_events(month);

        if (month % 12 == 0){
            yearly_events();
            int current_year = month / 12;
            output(current_year);
        }

    }
    results();
    return 0;
}