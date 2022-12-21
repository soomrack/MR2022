#include <stdio.h>
#include <stdlib.h>

const int start_year = 2005;

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
    Alice.current_year = start_year;
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
    Bob.current_year = start_year;
    return Bob;
}


//struct Client init_john(){
//    struct Client John;
//    John.name = "John";
//    John.bank = 1000 * 1000 * 100;  // Все денежные величины в копейках
//    John.income = 150 * 1000 * 100;
//    John.expenses = 10 * 1000 * 100 + 60 * 1000 * 100;
//    John.flat_cost = 7000 * 1000 * 100;
//    John.deposit = 0.08;
//    John.current_year = start_year;
//    return John;
//}


void monthly_payment(struct Client* client){
    client->bank = (unsigned long long int) ((double) (client->bank + client->income - client->expenses) *
                   (1.f + client->deposit / 12));
}

void simulate(struct Client* data, struct Client* client_array, int client_num, int years){
    for (int year = 0; year < years; year++){
        switch (year) {

            case 0:
                client_array[1].bank -= 300 * 1000 * 100;  // Боб платит первый взнос за квартиру
                break;
            case 5:
                client_array[0].income += 10 * 1000 * 100;  // Алисе повысили зарплату
                break;
            case 9:
                client_array[1].income += 30 * 1000 * 100; // Бобу повысили зарплату
                break;
            case 12:
                client_array[0].deposit = 0.05;  // у Алисы и Боба понизили процентную ставку по накоплению
                client_array[1].deposit = 0.06;
                break;
            default: break;
        }

        for (int month = 1; month <= 12; month++) {
            for (int idx = 0; idx < client_num; idx++){
                monthly_payment(&client_array[idx]);
            }
        }

        for (int i = 0; i < client_num; i++){
            client_array[i].current_year++;
            data[year * client_num + i] = client_array[i];
        }
    }
}

void print_report(struct Client* data, int client_num, int years){
    for (int i = 0; i < years * client_num; i++){
        printf("%s's actives at the end of year %d: %lli roubles and %i cents\n",
               data[i].name,
               data[i].current_year,
               (long long int)((data[i].bank + data[i].flat_cost) / 100),
               (int)((data[i].bank + data[i].flat_cost) % 100));
    }
}

void entry_point(){
    int years = 20;
    int client_num = 3;
    struct Client* data = (struct Client*) malloc(sizeof(struct Client) * (years + 1) * client_num);
    struct Client* client_array = (struct Client*) malloc(sizeof(struct Client) * client_num);
    client_array[0] = init_alice();
    client_array[1] = init_bob();
    //client_array[2] = init_john();

    simulate(data, client_array, client_num, years);
    print_report(data, client_num, years);
}

int main(){
    entry_point();
    return 0;
}