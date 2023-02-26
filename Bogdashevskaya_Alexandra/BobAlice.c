#include <stdio.h>
#include <stdlib.h>

const int MAX_MONTH = 20 * 12;

struct Client {
	char* name;
	unsigned long long account, account_history[20 * 12], deposit, salary, utility,
		rent, flat, mortage_monthly; // копейки
	double interest_percentage, mortage_percentage; // 10% = 0.1

};

void init_Alice(struct Client* Alice) {
	Alice->name = "Alice";
	Alice->account = 1000 * 1000 * 100;
	Alice->interest_percentage = 0.023;
	Alice->salary = 150 * 1000 * 100;
	Alice->utility = 10 * 1000 * 100;
	Alice->rent = 30 * 1000 * 100;
	Alice->flat = 0;

}

void init_Bob(struct Client* Bob) {
	Bob->name = "Bob";
	Bob->account = 1000 * 1000 * 100;
	Bob->interest_percentage = 0.023;
	Bob->salary = 150 * 1000 * 100;
	Bob->utility = 10 * 1000 * 100;
	Bob->flat = 15 * 1000 * 1000 * 100;
	Bob->utility = 10 * 1000 * 100;
	Bob->mortage_percentage = 0.05;
	Bob->deposit = 100 * 1000 * 100;
}

void save_account_history(struct Client* client, int year) {
	client->account_history[year - 1] = client->account;
}

void deposit_payment(struct Client* client) {
	client->account -= client->deposit;
}

void mortgage_calculation(struct Client* client) {
	client->mortage_monthly = (client->flat - client->deposit) / (12 * 20) * (1 + client->mortage_percentage);
}

void salary_income(struct Client* client) {
	client->account += client->salary;
}

void utility_payment(struct Client* client) {
	client->account -= client->utility;
}

void rent_payment(struct Client* client) {
	client->account -= client->rent;
}

void mortgage_payment(struct Client* client) {
	client->account -= client->mortage_monthly;
}

void interest_payment(struct Client* client) {
	client->account *= 1 + client->interest_percentage;
}

void print_report(struct Client client) {
	printf("%s\n", client.name);
	for (int year = 0; year < 20; ++year) {
		printf("%d: %llu\n", year + 1, client.account_history[year] + client.flat);
	}
	printf("\n");
}

void print_comparison(struct Client client1, struct Client client2) {
	printf("Total (%s): %llu\n", client1.name, client1.account);
	printf("Total (%s): %llu\n", client2.name, client2.account + client2.flat);

	if (client1.account > client2.account + client2.flat) {
		printf("%s has more money", client1.name);
	}
	else if (client1.account < client2.account + client2.flat) {
		printf("%s has more money", client2.name);
	}
	else {
		printf("Alice and Bob have same amount of money");

	}
}
void free_name(struct Client* client) {
	free(client->name);
}

void simulation() {
	struct Client Alice, Bob;

	init_Alice(&Alice);
	init_Bob(&Bob);

	deposit_payment(&Bob);

	mortgage_calculation(&Bob);

	for (int i = 1; i <= MAX_MONTH; ++i) {
		salary_income(&Alice);
		salary_income(&Bob);

		utility_payment(&Alice);
		utility_payment(&Bob);

		rent_payment(&Alice);

		mortgage_payment(&Bob);

		interest_payment(&Alice);
		interest_payment(&Bob);

		//на 5 году изменяем процент на вкладе
		if (i == 12 * 5) {
			Alice.interest_percentage = 0.3;
			Bob.interest_percentage = 0.1;
		}

		// в 10 году цена квартиры увеличивается
		if (i == 12 * 10) {
			Bob.flat *= 1.02;
		}

		if (i % 12 == 0) {
			save_account_history(&Alice, i / 12);
			save_account_history(&Bob, i / 12);
		}

	}

	print_report(Alice);
	print_report(Bob);
	print_comparison(Alice, Bob);
	//free_name(&Alice);
	//free_name(&Bob);
}

void main() {
	simulation();
}

