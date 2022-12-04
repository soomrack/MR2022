#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int TOTAL_MONTH = 12 * 30;


struct Client {
    char* name;
    unsigned long long int bank_account; //в копейках
    unsigned long long int house_value; //в копейках
    double bank_deposit_percent; //процент по депозиту
    unsigned long long int monthly_house_bills; //жкх в копейках
    unsigned long long int monthly_mortgage_payments; //плата по ипотеке
    unsigned long long int monthly_rent_payments; //плата по ренте
    unsigned long long int salary; //зарплата
    unsigned long long int first_payment; //первый платеж по ипотеке
};


void init_Alice(struct Client* alice) {
    alice->name = "Alice";
    alice->bank_account = 1 * 1000 * 1000 * 100;
    alice->bank_deposit_percent = 0.08;
    alice->monthly_rent_payments = 31 * 1000 * 100;
    alice->monthly_mortgage_payments = 0;
    alice->salary = 150 * 1000 * 100;
    alice->monthly_house_bills = 10 * 1000 * 100;
    alice->house_value = 0;
    alice->first_payment = 0;
}


void init_Bob(struct Client* bob) {
    bob->name = "Bob";
    bob->bank_account = 1 * 1000 * 1000 * 100;
    bob->bank_deposit_percent = 0.08;
    bob->monthly_rent_payments = 0;
    bob->monthly_mortgage_payments = 30 * 1000 * 100;
    bob->salary = 150 * 1000 * 100;
    bob->monthly_house_bills = 10 * 1000 * 100;
    bob->house_value = 7 * 1000 * 1000 * 100;
    bob->first_payment = 300 * 1000 * 100;
}


void first_payment(struct Client* client) { //первый платеж
    client->bank_account -= client->first_payment;
}


void salary_income(struct Client* client) { //пришла з/п
    client->bank_account += client->salary;
}


void house_bills(struct Client* client) { //прочие расходы
    client->bank_account -= client->monthly_house_bills;
}


void rent(struct Client* client) { //рента
    client->bank_account -= client->monthly_rent_payments;
}


void mortgage(struct Client* client) { //плата по ипотеке
    client->bank_account -= client->monthly_mortgage_payments;
}


void bank_deposit_point(struct Client* client) { //начислили проценты
    client->bank_account = (unsigned long long int)((client->bank_deposit_percent / 12.0 + 1.0) * client->bank_account);
}


void deposit_increase(struct Client* client) { //ставка повысилась
    client->bank_deposit_percent += 0.02;
}


void salary_decrease(struct Client* client) { //получку урезали
    client->salary /= (unsigned long int) 1.05;
}


void house_value_increase(struct Client* client) { //повысиласть стоимость квартиры
    client->house_value *= (unsigned long long int) 1.2;
}


void output(struct Client* client1, struct Client* client2) {
    printf("Name: %s, Total: %llu.%llu\t", client1->name, client1->bank_account / 100, client1->bank_account % 100);
    printf("Name: %s, Total: %llu.%llu\n", client2->name, client2->bank_account / 100 + client2->house_value / 100, client2->bank_account % 100 + client2->house_value % 100);
    if (client1->bank_account > (client2->bank_account + client2->house_value)) {
        printf("%s plan is more profitable than %s\n", client1->name, client2->name);
    }
    else if ((client2->bank_account + client2->house_value) > client1->bank_account) {
        printf("%s plan is more profitable than %s\n", client2->name, client1->name);
    }
    else {
        printf("They are equally profitable\n");
    }
}


void simulation() {
    struct Client alice;
    struct Client bob;
    init_Alice(&alice);
    init_Bob(&bob);

    printf("0 year\n");
    first_payment(&alice);
    first_payment(&bob);
    output(&alice, &bob);

    for (int month = 1; month <= TOTAL_MONTH; month++) {

        
        if (month % 36 == 0) {
            deposit_increase(&alice);
            deposit_increase(&bob);

            salary_decrease(&alice);
            salary_decrease(&bob);
        }
        if (month % 60 == 0) {
            house_value_increase(&alice);
            house_value_increase(&bob);
        }

        salary_income(&alice);
        salary_income(&bob);

        house_bills(&alice);
        house_bills(&bob);

        rent(&alice);
       
        mortgage(&bob);

        bank_deposit_point(&alice);
        bank_deposit_point(&bob);

        if (month % 12 == 0) {
            printf("%d year\n", month / 12);
            output(&alice, &bob);
        }
    }
}


void main() {
    simulation();
}