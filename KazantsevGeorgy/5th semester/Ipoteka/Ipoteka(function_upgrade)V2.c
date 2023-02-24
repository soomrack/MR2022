#include <stdio.h>
#include "malloc.h"

const int TOTAL_MOUNTHS = 12 * 20;

struct Client{
    char *name;
    unsigned long long int bank_capital;
    unsigned long long int house_cost;
    double bank_deposit_rate;
    unsigned int mouthly_house_bills;
    unsigned long long int mouthly_mortgage_payment;
    unsigned long long int mounthly_income;
    unsigned long long int property_tax;
};

struct Client Alice, Bob;

void AliceInit(struct Client *alice) {
    alice->name = malloc(6);
    alice->name = "Alice";
    alice->bank_capital = 1000 * 1000 * 100;
    alice->house_cost = 0;
    alice->bank_deposit_rate = 0.08;
    alice->mouthly_mortgage_payment = 0;
    alice->mouthly_house_bills = 40 * 1000 * 100;
    alice->mounthly_income = 150 * 1000 * 100;
    alice->property_tax = 0;
}
void BobInit(struct Client *bob) {
    bob->name = malloc(6);
    bob->name = "Bob";
    bob->bank_capital = 700 * 1000 * 100;
    bob->house_cost = 7 * 1000 * 1000 * 100;
    bob->bank_deposit_rate = 0.08;
    bob->mouthly_mortgage_payment = 50 * 1000 * 100;
    bob->mouthly_house_bills = 10 * 1000 * 100;
    bob->mounthly_income = 120 * 1000 * 100;
    bob->property_tax = 5 * 1000 * 100;
}


void full_output(struct Client *client) {
    printf("%s ", client->name);
    printf("bank_capital: %llu ", client->bank_capital/100 + client->house_cost - client->property_tax);
    printf(" house_cost:%llu", client->house_cost/100);
    printf(" bank_rate:%.2f ", client->bank_deposit_rate);
    printf(" income: %llu\n", client->mounthly_income/100);
}
//весь капитал вкладывается под проценты
void bank_deposit_income(struct Client *client) {
    client->bank_capital += (unsigned long long int)(client->bank_deposit_rate/12 * client->bank_capital);
}
//функция вычитает из капитала месячные траты
void mounthly_wasting_money(struct Client *client) {
    client->bank_capital -= (client->mouthly_house_bills + client->mouthly_mortgage_payment);
}
//функция добавляет к капиталу зп
void mounthly_income_money(struct Client *client) {
    client->bank_capital += client->mounthly_income;
}
void increase_bank_rate(struct Client *client) {
    client->bank_deposit_rate = 0.10;
}
void increase_flat_cost(struct Client *client) {
    client->house_cost += client->house_cost * 0.1;
}
void decrease_mountly_income(struct Client *client) {
    client->mounthly_income -= 30 * 1000 * 100;
}
void simulation() {
    AliceInit(&Alice);
    BobInit(&Bob);

    for (int mounth = 1; mounth <= TOTAL_MOUNTHS; mounth++) {
        bank_deposit_income(&Alice);
        bank_deposit_income(&Bob);

        mounthly_wasting_money(&Alice);
        mounthly_wasting_money(&Bob);

        mounthly_income_money(&Alice);
        mounthly_income_money(&Bob);
        if (mounth == 12 * 3) {
            increase_bank_rate(&Alice);
            increase_bank_rate(&Bob);
        }
        if (mounth % 60 == 0) {
            increase_flat_cost(&Alice);
            increase_flat_cost(&Bob);
        }
        if (mounth == 10) {
            decrease_mountly_income(&Alice);
        }

        if (mounth % 12 == 0) {
            printf("years:%d;\n ", mounth/12);
            full_output(&Alice);
            full_output(&Bob);
        }
    }

}
int main() {
    simulation();
}