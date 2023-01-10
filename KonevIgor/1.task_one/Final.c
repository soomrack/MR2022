#include <stdio.h>
#include <stdlib.h>

// Все переменные, обозначающие денежные средства, определены в копейках

// Задаем общие входные данные: ставки по вкладу, срок ипотеки
const int DEPOSIT_RATE_ANNUAL_1ST = 3; // процентов годовых
const int DEPOSIT_RATE_ANNUAL_2ND = 5;
const int TERM = 20; // лет

// Объявляем структуру клиента как тип данных
typedef struct Client {
    char *name;
    long long capital;
    int salary;
    int utilitiesExpense;
    int spending;
    long long flatCost;
    int firstPayment;
    int monthlyPayment;
} Client;

//Объявляем функции для реализации основного алгоритма
void initAlice (Client *Alice);
void initBob (Client *Bob);
void calcStartUpCapital (Client *Client);
void calcPercents (Client *Client, int loanRate);
void calcCapital (Client *Client);
void printMonthlyReport (int month, Client *Client1, Client *Client2);
void printFinalReport (Client *Client1, Client *Client2);
void incFlatCost (Client *Client);
void decSalary (Client *Client);
void incSalary (Client *Client);

void simulation() {
    Client alice;
    Client bob;
    initAlice(&alice);
    initBob(&bob);
    printf("%12s %15s %17s\n", "Capital on ", alice.name, bob.name);
    int depositRateAnnual = DEPOSIT_RATE_ANNUAL_1ST;
    calcStartUpCapital (&alice);
    calcStartUpCapital (&bob);

    for (int i = 1; i <= TERM * 12; i++) {

        // Рост цен на недвижимость
        if (i == 12 * 5){
            incFlatCost(&alice);
            incFlatCost(&bob);
        }
        // Падение и рост дохода
        if (i == 10 * 12){
            decSalary(&alice);
            decSalary(&bob);
        }
        if (i == 16 * 12){
            incSalary(&alice);
            incSalary(&bob);
        }
        // Повышение ставки по вкладу
        if (i == 3 * 12) {
            depositRateAnnual = DEPOSIT_RATE_ANNUAL_2ND;
        }

        calcPercents(&alice, depositRateAnnual);
        calcCapital(&alice);
        calcPercents(&bob, depositRateAnnual);
        calcCapital(&bob);
        printMonthlyReport(i, &alice, &bob);
    }

    printFinalReport(&alice, &bob);
}

int main() {
    simulation();
}

void initAlice (Client *Alice) {
    Alice->name = malloc(6);
    Alice->name = "Alice";
    Alice->capital = 1000 * 1000 * 100;
    Alice->salary = 150 * 1000 * 100;
    Alice->utilitiesExpense = 40 * 1000 * 100;
    Alice->spending = 20 * 1000 * 100;
    Alice->flatCost = 0;
    Alice->firstPayment = 0;
    Alice->monthlyPayment = 0;
}

void initBob (Client *Bob) {
    Bob->name = malloc(4);
    Bob->name = "Bob";
    Bob->capital = 1000 * 1000 * 100;
    Bob->salary = 150 * 1000 * 100;
    Bob->utilitiesExpense = 10 * 1000 * 100;
    Bob->spending = 15 * 1000 * 100;
    Bob->flatCost = 12 * 1000 * 1000 * 100;
    Bob->firstPayment = 300 * 1000 * 100;
    Bob->monthlyPayment = 100 * 1000 * 100;
}

void calcStartUpCapital (Client *Client) {
    Client->capital -= Client->firstPayment;
}

void calcPercents (Client *Client, int loanRate) {
    Client->capital += (Client->capital * loanRate / 1200);
}

void calcCapital (Client *Client) {
    Client->capital += (Client->salary - Client->utilitiesExpense -
            Client->spending - Client->monthlyPayment);
}

void printMonthlyReport (int month, Client *Client1, Client *Client2) {
    if (month % 12 == 0) {
        printf("%4d year %18lld,%lld %15lld,%lld\n",
               month/12, Client1->capital/100, Client1->capital%100,
               Client2->capital/100, Client1->capital%100);
    }
}

void printFinalReport (Client *Client1, Client *Client2) {
    printf("Final capital %14lld,%lld %15lld,%lld\n",
           (Client1->capital + Client1->flatCost)/100, (Client1->capital + Client1->flatCost)%100,
           (Client2->capital + Client2->flatCost)/100, (Client2->capital + Client2->flatCost)%100);
    if ((Client1->capital + Client1->flatCost) > (Client2->capital + Client2->flatCost)) {
        printf("%s will have a %lld,%lld rubles more, then %s\n", Client1->name,
               ((Client1->capital + Client1->flatCost) - (Client2->capital + Client2->flatCost)) / 100,
               ((Client1->capital + Client1->flatCost) - (Client2->capital +
               Client2->flatCost)) % 100, Client2->name);
    } else {
        printf("%s will have a %lld,%lld rubles more, then %s\n", Client2->name,
               ((Client2->capital + Client2->flatCost) - (Client1->capital + Client1->flatCost)) / 100,
               ((Client2->capital + Client2->flatCost) - (Client1->capital +
               Client1->flatCost)) % 100, Client1->name);
    }
}

void incFlatCost (Client *Client) {
    Client->flatCost = Client->flatCost * 15 / 10;
}

void decSalary (Client *Client) {
    Client->salary = Client->salary * 10 / 15;
}

void incSalary (Client *Client) {
    Client->salary = 150 * 1000 * 100;
}