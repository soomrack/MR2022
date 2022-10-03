#include <stdio.h>
#include <stdlib.h>

const int Months = 20 * 12;  // Эксперимент длится 20 лет = 240 месяцев

struct Holder {  // Все цены в копейках
    char *name;
    unsigned long long account;  // Счет
    unsigned long long account_history[240];  // История изменния счета
    unsigned long long salary;  // Зарплата
    unsigned long long utility;  // Коммунальные платежи
    unsigned long long rent;  // Арендная плата
    unsigned long long apartments;  // Цена квартиры
    unsigned long long mortage_payment;  // Плата по ипотеке
    unsigned long long mortage_down_payment;  // Первоначальный взнос по ипотеке
    double deposit_interest;  // Процент по вкладу
    double mortage_percentage;  // Процент по ипотеке
};

void init_Alice(struct Holder *Alice) {
    Alice->name = malloc(5);
    Alice->name = "Alice";
    Alice->account = 1000000 * 100;  // Начальные сбережения
    Alice->deposit_interest = 0.07 / 12.0;
    Alice->salary = 150000 * 100;
    Alice->utility = 10000 * 100;
    Alice->rent = 30000 * 100;
    Alice->apartments = 0;  // Алиса не покупает квартиру
};

void init_Bob(struct Holder *Bob) {
    Bob->name = malloc(3);
    Bob->name = "Bob";
    Bob->account = 700000 * 100;
    Bob->deposit_interest = 0.07/12;
    Bob->salary = 150000 * 100;
    Bob->utility = 10000 * 100;
    Bob->mortage_down_payment = 300000*100;  // Первоначальный взнос
    Bob->apartments = 7000000*100;
    Bob->mortage_percentage = 0.1/12;
};

void save_account_history(struct Holder *holder, const year) {
    holder->account_history[year - 1] = holder->account;
}

void mortgage_calculation(struct Holder *holder) {
    holder->mortage_payment = (holder->apartments - holder->mortage_down_payment) / (12 * 20) * (1.0 + holder->mortage_percentage);

}
//  Цена на квартиру постоянно растет
void apartment_grow(struct Holder *holder) {
    holder->apartments *= 1.0001;
}

void salary_income(struct Holder *holder) {
    holder->account += holder->salary;
}

void utility_payment(struct Holder *holder) {
    holder->account -= holder->utility;
}

void rent_payment(struct Holder *holder) {
    holder->account -= holder->rent;
}

void mortgage_pay(struct Holder *holder) {
    holder->account -= holder->mortage_payment;
}

void interest_payment(struct Holder *holder) {
    holder->account *= (1.0 + holder->deposit_interest);
}  // Остаток средств на счете каждый месяц, который уходит на вклад с учетом процентов

void print_report(struct Holder *holder) {
    printf("%s\n", holder->name);
    for (int year = 0; year < 20; ++year) {
        printf("%d: %llu\n", year + 1, holder->account_history[year] + holder->apartments);
    }
    printf("\n");
}

void print_comparison(struct Holder *holder1, struct Holder *holder2) {
    printf("Total (%s): %llu\n", holder1->name, holder1->account);
    printf("Total (%s): %llu\n", holder2->name, holder2->account + holder2->apartments);

    if (holder1->account > holder2->account + holder2->apartments) {
        printf("%s is wealthier than %s", holder1->name, holder2->name);
    } else if (holder1->account < holder2->account + holder2->apartments) {
        printf("%s is wealthier than %s", holder2->name, holder1->name);
    } else {
        printf("Alice and Bob are equally wealthy");

    }
}

void simulation() {
    struct Holder Alice, Bob;

    init_Alice(&Alice);
    init_Bob(&Bob);

    mortgage_calculation(&Bob);

    for (int month = 1; month <= Months; ++month) {
        salary_income(&Alice);
        salary_income(&Bob);

        utility_payment(&Alice);
        utility_payment(&Bob);

        rent_payment(&Alice);

        mortgage_pay(&Bob);

        interest_payment(&Alice);
        interest_payment(&Bob);

        apartment_grow(&Bob);

        //  На 5 году увеличивается процент на вкладе
        if (month >= 12 * 5) {
            Alice.deposit_interest = 0.08/12.0;
            Bob.deposit_interest = 0.08/12.0;
        }

        // На 10 году цена квартиры резко увеличивается
        if (month == 12 * 10) {
            Bob.apartments *= 1.6;
        }

        if (month % 12 == 0) {
            save_account_history(&Alice, (int)month / 12.0);
            save_account_history(&Bob, (int)month / 12.0);
        }

    }

    print_report(&Alice);
    print_report(&Bob);
    print_comparison(&Alice, &Bob);
}

void main() {
    simulation();
}
