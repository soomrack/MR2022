#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

const int TOTAL_MONTH = 12*20;


struct Client {
    char *name;
    unsigned long long int bank_account; //copeiki
    unsigned long long int house_value; //copeiki
    double bank_deposit_percent; //procent po depozitu
    unsigned long long int monthly_house_bills; //komunalka v copeikah
    unsigned long long int monthly_mortgage_payments; //oplata ipoteki
    unsigned long long int monthly_arenda_payments; //рента
    unsigned long long int income;
    unsigned long long int salary;
    unsigned long long int first_payment;
};


void init_Alice(struct Client *alice){
    alice->name = malloc(6);
    alice->name = "Alice";
    alice->bank_account = 1000 * 1000 * 100;
    alice->bank_deposit_percent = 0.08;
    alice->monthly_arenda_payments = 40 * 1000 * 100;
    alice->monthly_mortgage_payments = 0;
    alice->salary = 150 * 1000 * 100;
    alice->monthly_house_bills = 10 * 1000 * 100;
    alice->house_value = 0;
    alice->first_payment = 0;
}


void init_Bob(struct Client *bob){
    bob->name = malloc(6);
    bob->name = "Bob";
    bob->bank_account = 1000 * 1000 * 100;
    bob->bank_deposit_percent = 0.08;
    bob->monthly_arenda_payments = 40 * 1000 * 100;
    bob->monthly_mortgage_payments = 30 * 1000 * 100;
    bob->salary = 150 * 1000 * 100;
    bob->monthly_house_bills = 10 * 1000 * 100;
    bob->house_value = 7 * 1000 * 1000 * 100;
    bob->first_payment = 300 * 1000 * 100;
}


void first_payment(struct Client *client){
    client->bank_account -= client->first_payment;
}


void salary_income(struct Client *client){
    client->bank_account += client->salary;
}


void house_bills(struct Client *client){
    client->bank_account -= client->monthly_house_bills;
}


void arenda(struct Client *client){
    client->bank_account -= client->monthly_arenda_payments;
}


void mortgage(struct Client *client){
    client->bank_account -= client->monthly_mortgage_payments;
}


void bank_deposit_income(struct Client *client){
    client->bank_account = (unsigned long long int)(1.0 + client->bank_deposit_percent/12.0)*client->bank_account;
}


void deposit_increase(struct Client *client){
    client->bank_deposit_percent += 0.02;
}


void salary_decrease(struct Client *client){
    client->salary /= (unsigned long int) 1.05;
}


void house_value_increase(struct Client *client){
    client->house_value *= (unsigned long long int) 1.2;
}


void print_result(struct Client *client){
    printf("Name: %s\n", client->name);
    printf("Bank account: %llu,", client->bank_account/100);
    printf("%llu\n", client->bank_account%100);
}


void simulation (){
    struct Client alice;
    struct Client bob;
    init_Alice(&alice);
    init_Bob(&bob);

    for (int month = 1; month <= TOTAL_MONTH; month ++){
        salary_income(&alice);
        salary_income(&bob);

        house_bills(&alice);
        house_bills(&bob);

        arenda(&alice);
        arenda(&bob);

        mortgage(&alice);
        mortgage(&bob);

        bank_deposit_income(&alice);
        bank_deposit_income(&bob);

        if (month % 36 == 0){
            deposit_increase(&alice);
            deposit_increase(&bob);

            salary_decrease(&alice);
            salary_decrease(&bob);
        }

        if (month % 60 == 0){
            house_value_increase(&alice);
            house_value_increase(&bob);
        }

        if (month % 12 == 0){
            print_result(&alice);
            print_result(&bob);
            printf("%d year\n", month/12);
        }
    }

}


int main() {
    simulation();
    return 0;
}