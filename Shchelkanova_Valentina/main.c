#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    const int months = 20 * 12;

    struct Holder {
        char *name;
        unsigned long long account, account_history[
                20 * 12], deposit, salary, utility, rent, apartments, mortage_payment; //копейки
        double deposit_interest, mortage_percentage;
    };

    void init_Alice(struct Holder *Alice) {
        Alice->name = malloc(5);
        Alice->name = "Alice";
        Alice->account = 1000000 * 100;
        Alice->deposit_interest = 0.07;
        Alice->sallary = 150000 * 100;
        Alice->utility = 10000 * 100;
        Alice->rent = 30000 * 100;
        Alice->apartments = 0;
    };

    void init_Bob(struct Holder *Bob) {
        Bob->name = malloc(3);
        Bob->name = "Bob";
        Bob->account = 1000000 * 100;
        Bob->deposit_interest = 0.07;
        Bob->sallary = 150000 * 100;
        Bob->utility = 10000 * 100;
        Bob->apartments = 7000000 * 100;
        Bob->mortage_percentage = 0.05;
        Bob->deposit = 100 * 1000 * 100;
    };

    void save_account_history(struct Holder *holder, int year) {
        holder->account_history[year - 1] = holder->account;
    }

    void deposit_fee(struct Holder *holder) {
        holder->account -= holder->deposit;
    }
    void mortgage_calculation(struct Holder *holder) {
        holder->mortage_payment = (holder->apartments - holder->deposit) / (12 * 20) * (1 + holder->mortage_percentage);
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
        holder->account *= 1 + holder->deposit_interest;
    }

    void print_report(struct Holder holder) {
        printf("%s\n", client.name);
        for (int year = 0; year < 20; ++year) {
            printf("%d: %llu\n", year + 1, client.account_history[year] + client.apartment);
        }
        printf("\n");
    }

    void print_comparison(struct Holder holder1, struct Holder holder2) {
        printf("Total (%s): %llu\n", holder1.name, holder1.account);
        printf("Total (%s): %llu\n", holder2.name, holder2.account + holder2.apartment);

        if (holder1.account > holder2.account + holder2.apartment) {
            printf("%s has more money", holder1.name);
        } else if (holder1.account < holder2.account + holder2.apartment) {
            printf("%s has more money", holder2.name);
        } else {
            printf("Alice and Bob have same amount of money");

        }
    }

    return 0;
}