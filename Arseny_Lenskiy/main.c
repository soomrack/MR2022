#include <stdio.h>


//const
unsigned long long int a_bank = 1000000*100;
unsigned long long int b_bank = 1000000*100;
int vklad = 300000*100;
int plateg = 26056*100;
char years = 20;


//Struct
struct Human {
    unsigned long long int month_cash; //чистые деньги после вылпат
    double month_percent; //процент на который умножаем вклад кадждый месяц
    unsigned long long int month_deposit; //Деньги которые мы получаем после каждый месяц
    unsigned long long int month_waste; //Деньги которые уходят на выплаты
    unsigned long long int start_cash; // Начальный капитал
    int doxod; // ЗП
    int percent; // Процент по вкладу
};

struct Human Alice;
struct Human Bob;


void init_Bob(struct Human *init_Bob);
void init_Alice(struct Human *init_Alice);
void event(int year);
void add_bank_percents(struct Human *man);
void add_doxod(struct Human *man);
void remove_wastes(struct Human *man);
void remove_month_payment(struct Human *man);
void deposit(struct Human *man);
void print_client_line(unsigned long long int man_year_cash);
void print_out(unsigned long long int Bob_year_cash, unsigned long long int Alice_year_cash, int year);
void simulation();

void init_Bob(struct Human *init_Bob) {

    // BOB IPOTEKA
    init_Bob->start_cash = b_bank - vklad;
    init_Bob->month_deposit = init_Bob->start_cash;
    init_Bob->month_cash = 0;
    init_Bob->doxod = 150000 * 100;
    init_Bob->month_waste = 10000 * 100;
    init_Bob->percent = 8;
}

void init_Alice(struct Human *init_Alice) {

    // Alice vklad
    init_Alice->start_cash = a_bank;
    init_Alice->month_deposit = init_Alice->start_cash;
    init_Alice->month_cash = 0;
    init_Alice->doxod = 150000 * 100;
    init_Alice->month_waste = 40000 * 100;
    init_Alice->percent = 8;
}

void event(int year) {
    if (year==6) {
        Bob.percent=7;
        Alice.percent=7;
    }
}

void add_bank_percents(struct Human *man) {
    man->month_percent = ((double)(man->percent * 0.01 / 12));
    man->month_deposit += (unsigned long long int)(man->month_percent * (double)(man->month_deposit));
}

void add_doxod(struct Human *man){
    man->month_cash += man->doxod;
}

void remove_wastes(struct Human *man) {
    man->month_cash -= man->month_waste;
}

void remove_month_payment(struct Human *man){
    man->month_cash -= plateg;
}

void deposit(struct Human *man){
    man->month_deposit += man->month_cash;
    man->month_cash = 0;
}

void print_client_line(unsigned long long int year_cash) {
    unsigned long long int rub = year_cash / 100;
    int kop = (int)(year_cash % 100);
    printf("%0.2llu Rub %0.2d Kop       ", rub,kop);
}

void print_out(unsigned long long int Bob_year_cash, unsigned long long int Alice_year_cash, int year) {
    if(year == 0){
        printf("%s                     %s                     Year \n", "Bob", "Alice");
    }

    print_client_line(Bob_year_cash);

    print_client_line(Alice_year_cash);

    printf("%0.2d \n", year + 1);
}


void simulation() {
    for (int year = 0; year < years; year++) {
        event(year);
        for (int mon = 0; mon < 12; mon++) {
            // BOB
            add_bank_percents(&Bob);
            add_doxod(&Bob);
            remove_wastes(&Bob);
            remove_month_payment(&Bob);
            deposit(&Bob);
            // ALICE
            add_bank_percents(&Alice);
            add_doxod(&Alice);
            remove_wastes(&Alice);
            deposit(&Alice);
        }

        print_out(Bob.month_deposit + vklad, Alice.month_deposit, year);
    }
}

int main() {

    init_Bob(&Bob);
    init_Alice(&Alice);

    simulation();
    return 0;

}