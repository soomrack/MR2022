#include <stdio.h>

const int TOTAL_MONTH = 20*12;

struct Client{
    char *name[10];
    unsigned long long int bank_account; //copeiki
    unsigned long long int house_value; //copeiki
    double bank_deposit_percent; //procent po depozitu
    unsigned long long int monthly_house_bills; //komunalka v copeikah
    unsigned long long int monthly_mortgage_payments; //oplata ipoteki
    unsigned long long int monthly_arenda_payments; //renta
}

void init_Alice (struct Client *alice){ //iticializacia Alicovih dannih
    alice->name =  "Alice";
    alice->bank_account = 1000*1000*100;
    alice->bank_deposit_percent = 0.08;
    alice->monthly_arenda_payments = 40*1000*100;
    alice->monthly_mortgage_payments = 0; //Alice dont pay ipoteka
}

void init_Bob (struct Client *bob){ //initializacia Bobovih dannih
    bob->name = "Bob";
    bob->bank_account = 1000*1000*100;
    bob->bank_deposit_percent = 0.08;
    bob->monthly_arenda_payments = 0; //Bob dont arend house
    bob->monthly_mortgage_payments = 30*1000*100;
}

void print_fill_report(struct Client client){
    printf("Name: %s\n", client.name);
    printf("Bank_account %llu\n", client.bank_account);
}

void bank_deposit_income(struct Client client){
    client.bank_account+=client.bank_deposit_percent/12*client.bank_account;
}

void deposit_monthly_payments(struct Client client){
    client.bank_account += (unsigned long long int)(client.bank_account*client.bank_deposit_percent)
}

void monthly_house_payments (struct Client client){
    client.bank_account-=client.monthly_arenda_payments;
    client.bank_account-= client.monthly_mortgage_payments;
}


int main() {
    return 0;
}
