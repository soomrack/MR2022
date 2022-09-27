#include <stdio.h>
#include <math.h>
#include <stdlib.h>

    const int months = 20 * 12; //эксперимент длится 20 лет = 240 месяцев

    struct Holder {
        char *name;
        unsigned long long account; //счет
        unsigned long long account_history[240];//история изменния счета
        unsigned long long deposit; //сумма на депозит
        unsigned long long salary; //зарплата
        unsigned long long utility; //коссунальные платежи
        unsigned long long rent; //арендная плата
        unsigned long long apartments; //цена квартиры
        unsigned long long mortage_payment; //плата по ипотеке
        unsigned long long mortage_down_payment; //первоначальный взнос по ипотеке
        double deposit_interest; //процент по вкладу
        double mortage_percentage; // процент по ипотеке
    };

    void Alice_money(struct Holder *Alice) {
        Alice.name = malloc(5);
        Alice.name = "Alice";
        Alice.account = 1000000 * 100; //начальные сбережения
        Alice.deposit_interest = 0.07;
        Alice.salary = 150000 * 100;
        Alice.utility = 10000 * 100;
        Alice.rent = 30000 * 100;
        Alice.apartments = 0; //Алиса не покупает квартиру
    };

    void init_Bob(struct Holder *Bob) {
        Bob.name = malloc(3);
        Bob.name = "Bob";
        Bob.account = 1000000 * 100;
        Bob.deposit_interest = 0.07;
        Bob.salary = 150000 * 100;
        Bob.utility = 10000 * 100;
        Bob.mortage_down_payment = 300000; //Первоначальный взнос
        Bob.apartments = 7000000 * 100;
        Bob.mortage_percentage = 0.1;
        Bob.deposit = 700000*100;
    };

    void save_account_history(struct Holder *holder, int year) {
        holder.account_history[year - 1] = holder.deposit;
    }

    void deposit_fee(struct Holder *holder) {
        holder.account -= holder.deposit;
    }
    void mortgage_calculation(struct Holder *holder) {
        holder.mortage_payment = (holder.apartments-holder.mortage_down_payment) / (12 * 20) * (1 + holder.mortage_percentage);
    }

    void salary_income(struct Holder *holder) {
        holder.account += holder.salary;
    }

    void utility_payment(struct Holder *holder) {
        holder.account -= holder.utility;
    }

    void rent_payment(struct Holder *holder) {
        holder.account -= holder.rent;
    }

    void mortgage_pay(struct Holder *holder) {
        holder.account -= holder.mortage_payment;
    }

    void interest_payment(struct Holder *holder) {
        holder.deposit = (1 + holder.deposit_interest)*(holder.account+holder->deposit);
    } //Остаток средств на счете каждый месяц, который уходит на вклад с учетом процентов

    void print_report(struct Holder holder) {
        printf("%s\n", holder.name);
        for (int year = 0; year < 20; ++year) {
            printf("%d: %llu\n", year + 1, holder.account_history[year] + holder.apartments);
        }
        printf("\n");
    }

    void print_comparison(struct Holder holder1, struct Holder holder2) {
        printf("Total (%s): %llu\n", holder1.name, holder1.deposit);
        printf("Total (%s): %llu\n", holder2.name, holder2.deposit + holder2.apartments);

        if (holder1.deposit > holder2.deposit + holder2.apartments) {
            printf("%s wealthier than %s", holder1.name, holder2.name);
        } else if (holder1.deposit < holder2.deposit + holder2.apartment) {
            printf("%s wealthier than %s", holder2.name, holder2.name);
        } else {
            printf("Alice and Bob equally wealthy");

        }
    }

    void simulation() {
        struct Holder Alice, Bob;

        init_Alice(&Alice);
        init_Bob(&Bob);

        deposit_fee(&Bob);

        mortgage_calculation(&Bob);

        for (int i = 1; i <= months; ++i) {
            salary_income(&Alice);
            salary_income(&Bob);

            utility_payment(&Alice);
            utility_payment(&Bob);

            rent_payment(&Alice);

            mortgage_pay(&Bob);

            interest_payment(&Alice);
            interest_payment(&Bob);

            //на 5 году увеличивается процент на вкладе
            if (i == 12 * 5) {
                Alice.deposit_interest = 0.08;
                Bob.deposit_interest = 0.08;
            }

            // в 10 году цена квартиры резко увеличивается
            if (i == 12 * 10) {
                Bob.apartments*= 1.5;
            }

            if (i % 12 == 0) {
                save_account_history(&Alice, (int)i / 12);
                save_account_history(&Bob, (int)i / 12);
            }

        }

        print_report(Alice);
        print_report(Bob);
        print_comparison(Alice, Bob);
    }

    void main() {
        simulation();
    }
