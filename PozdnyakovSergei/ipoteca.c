#include <stdio.h>
#include <stdlib.h>

const int TOTAL_MONTH = 20 * 12;


struct Client {
    char *name;
    unsigned long long int bank_account; //copeiki
    unsigned long long int house_value; //copeiki
    double bank_deposit_percent; //procent po depozitu
    unsigned long long int monthly_house_bills; //komunalka v copeikah
    unsigned long long int monthly_mortgage_payments; //oplata ipoteki
    unsigned long long int monthly_arenda_payments; //рента
    unsigned long long int income;
};


void init_Alice (struct Client *alice){ //данные Alice
    alice->name = malloc(6);
    alice->name =  "Alice";
    alice->bank_account = 1000 * 1000 * 100;
    alice->bank_deposit_percent = 0.08; //8%
    alice->monthly_arenda_payments = 40 * 1000 * 100;
    alice->monthly_mortgage_payments = 0; //Alice не платит ипотеку
    alice->income = 150 * 1000 * 100; //получка
    alice->monthly_house_bills = 10 * 1000 * 100; //коммуналка
    alice->house_value = 0; //нет в собственности квартиры
}


void init_Bob (struct Client *bob){ //данные Боба
    bob->name = malloc(4);
    bob->name = "Bob";
    bob->bank_account = 1000 * 1000 * 100;
    bob->bank_deposit_percent = 0.08;
    bob->monthly_arenda_payments = 0; //Боб не арендует
    bob->monthly_mortgage_payments = 30 * 1000 * 100;
    bob->income = 150 * 1000 * 100; //получка
    bob->house_value = 7000 * 1000 * 100; //стоимость квартиры
    bob->monthly_house_bills = 10 * 1000 * 100; //коммуналка
}


void print_fill_report(struct Client client){
    printf("Name: %s\n", client.name);
    printf("Bank_account %llu\n", client.bank_account+client.house_value);
}


void bank_deposit_income(struct Client client){
    client.bank_account+=client.bank_deposit_percent/12*client.bank_account;
}


void deposit_monthly_payments(struct Client client){
    client.bank_account += (unsigned long long int)(client.bank_account*client.bank_deposit_percent);
}


void monthly_house_payments (struct Client client){
    client.bank_account-=client.monthly_arenda_payments;
    client.bank_account-= client.monthly_mortgage_payments;
}


void simulation () {
    struct Client alice;
    struct Client bob;
    init_Alice(&alice);
    init_Bob(&bob);
    for (int month = 0; month <= TOTAL_MONTH; month++) {
        bank_deposit_income(alice);
        bank_deposit_income(bob);
        deposit_monthly_payments(alice);
        deposit_monthly_payments(bob);
        monthly_house_payments(alice);
        monthly_house_payments(bob);

    }
}


int main() {
    simulation();
    return 0;
}
