#include <stdio.h>
#include <stdlib.h>

struct Client{
    char* name;
    unsigned long long int bank;  // Счет клиента (все денежные величины в копейках)
    unsigned long int income;
    unsigned long int expenses;
    unsigned long long int flat_cost;
    double deposit;
    int current_year;
};

struct Client init_alice(){
    struct Client Alice;
    Alice.name = "Alice";
    Alice.bank = 1000 * 1000 * 100;  // Все денежные величины в копейках
    Alice.income = 150 * 1000 * 100;
    Alice.expenses = 40 * 1000 * 100;
    Alice.flat_cost = 0;
    Alice.deposit = 0.08;
    Alice.current_year = 2005;
    return Alice;
}

struct Client init_bob(){
    struct Client Bob;
    Bob.name = "Bob";
    Bob.bank = 1000 * 1000 * 100;  // Все денежные величины в копейках
    Bob.income = 150 * 1000 * 100;
    Bob.expenses = 10 * 1000 * 100 + 60 * 1000 * 100;
    Bob.flat_cost = 7000 * 1000 * 100;
    Bob.deposit = 0.08;
    Bob.current_year = 2005;
    return Bob;
}

void monthly_payment(struct Client* client){
    client->bank = (unsigned long long int) ((double) (client->bank + client->income - client->expenses) *
                   (1.f + client->deposit / 12));
}

void simulate(struct Client* data, struct Client Alice, struct Client Bob, int years){
    for (int year = 0; year < years; year++){
        for (int month = 1; month <= 12; month++) {
            monthly_payment(&Alice);
            monthly_payment(&Bob);
        }
        Alice.current_year++;
        Bob.current_year++;
        data[year * 2] = Alice;
        data[year * 2 + 1] = Bob;
    }
}

void print_report(struct Client* data, int years){
    for (int i = 0; i < years * 2; i++){
        printf("%s's actives at the end of year %d: %lli roubles and %i cents\n",
               data[i].name,
               data[i].current_year,
               (long long int)((data[i].bank + data[i].flat_cost) / 100),
               (int)((data[i].bank + data[i].flat_cost) % 100));
    }
}

void entry_point(){
    int years = 20;
    struct Client* data = (struct Client*) malloc(sizeof(struct Client) * (years + 1) * 2);

    struct Client Alice = init_alice();
    struct Client Bob = init_bob();

    Bob.bank -= 30000000;  // Первый взнос Боба
    // TODO: Добавить функционал "событий в жизни", добавить туда начисление первого взноса

    simulate(data, Alice, Bob, years);
    print_report(data, years);
}

int main(){
    entry_point();
    return 0;
}