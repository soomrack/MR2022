#include <stdio.h>

// CONSTS
const int START_CASH = 1000000 * 100; // FIRST INPUT IN BANK (KOP)
const int FIRST_INPUT = 450000 * 100; // BOB'S INPUT IN FLAT (KOP)
const int FLAT_PRICE = 3000000 * 100; // FLAT'S PRICE (KOP)
const int MONTH_PAY = 25957 * 100; // BOB'S MONTHLY WASTE ON FLAT (KOP)
const int PERIOD = 20; // YEARS

struct Client {
    unsigned long long int bank_account; // KOP
    unsigned int month_cash; // CASH THAT IS AVAILABLE UNTIL END OF THE MONTH (KOP)
    int salary; // KOP
    int waste; // MONTHLY WASTE (KOP)
    int year_percent; // BANK'S PERCENT
};

struct Client Alice;
struct Client Bob;

void init_bob(struct Client *init_Bob);

void init_alice(struct Client *init_Alice);

void year_event(int year);

void add_bank_percents(struct Client *client);

void add_salary(struct Client *client);

void remove_wastes(struct Client *client);

void remove_month_payment(struct Client *client);

void deposit(struct Client *client);

void print_client_line(unsigned long long int client_year_cash);

void print_out(unsigned long long int bob_year_cash, unsigned long long int alice_year_cash, int year);

void free_struct(struct Client* client);

void simulation();

void init_bob(struct Client *init_Bob) {
    // BOB IPOTEKA
    init_Bob->bank_account = START_CASH - FIRST_INPUT;
    init_Bob->month_cash = 0;
    init_Bob->salary = 150000 * 100;
    init_Bob->waste = 10000 * 100;
    init_Bob->year_percent = 7;
}

void init_alice(struct Client *init_Alice) {
    // ALICE SAVINGS
    init_Alice->bank_account = START_CASH;
    init_Alice->month_cash = 0;
    init_Alice->salary = 150000 * 100;
    init_Alice->waste = 40000 * 100;
    init_Alice->year_percent = 7;
}

void year_event(int year) {
    // PERCENT CHANGE AFTER 5 YEARS
    if (year == 4) {
        Bob.year_percent = 8;
        Alice.year_percent = 8;
    }
}

void add_bank_percents(struct Client *client) {
    double month_percent = client->year_percent * 0.01 / 12;
    client->month_cash += (unsigned int)((double)client->bank_account * month_percent);
}

void add_salary(struct Client *client) {
    client->month_cash += client->salary;
}

void remove_wastes(struct Client *client) {
    client->month_cash -= client->waste;
}

void remove_month_payment(struct Client *client) {
    client->month_cash -= MONTH_PAY;
}

void deposit(struct Client *client) {
    client->bank_account += client->month_cash;
    client->month_cash = 0;
}
// INDIVIDUAL OUTPUT BLOCK
void print_client_line(unsigned long long int client_year_cash) {
    unsigned long long int client_rub = client_year_cash / 100;
    int client_kop = (int)(client_year_cash % 100);
    printf("%0.2llu Rub %0.2d Kop       ", client_rub,client_kop);
}

void print_out(unsigned long long int bob_year_cash, unsigned long long int alice_year_cash, int year) {
    // TABLE HEAD
    if(year == 0){
        printf("%s                     %s                     Year \n", "Bob", "Alice");
    }

    print_client_line(bob_year_cash);

    print_client_line(alice_year_cash);

    printf("%0.2d \n", year + 1);
}


void simulation() {
    // YEAR CYCLE STARTS
    for (int year = 0; year < PERIOD; year++) {
        // SOMETHING CHANGED
        year_event(year);
        for (int mon = 0; mon < 12; mon++) {
            // BOB
            add_bank_percents(&Bob);
            add_salary(&Bob);
            remove_wastes(&Bob);
            remove_month_payment(&Bob);
            deposit(&Bob);
            // ALICE
            add_bank_percents(&Alice);
            add_salary(&Alice);
            remove_wastes(&Alice);
            deposit(&Alice);
        }

        print_out(Bob.bank_account + FLAT_PRICE, Alice.bank_account, year);
    }
}

int main() {

    init_bob(&Bob);
    init_alice(&Alice);

    simulation();
    return 0;
}