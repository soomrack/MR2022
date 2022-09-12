#include <stdio.h>

float flatChange(float flat);

void main() {
	int aliceSalary = 150000, bobSalary = 150000, aliceMonthly = 40000, bobMonthly = 10000, bobPayment = 100000, deposit = 300000;
	float aliceAccount = 1000000, bobAccount = 1000000, alicePercent = 0.07, bobPercent = 0.07, flat = 1700000;

	bobAccount -= deposit;

	for (int n = 1; n <= 20; n++) {
		aliceAccount += aliceSalary - aliceMonthly;
		aliceAccount *= 1 + alicePercent;

		bobAccount += bobSalary - bobPayment - bobMonthly;
		bobAccount *= 1 + bobPercent;

		flat = flatChange(flat);

		if (n == 3) {
			alicePercent = 0.1;
			bobPercent = 0.1;
		}
	}

	printf("On Alice's money: %f\n", aliceAccount);
	printf("On Bob's money: %f\n", bobAccount + flat);

	if (aliceAccount > bobAccount + flat) {
		printf("Alice has more money");
	}
	else if (aliceAccount < bobAccount + flat) {
		printf("Bob has more money");
	}
	else {
		printf("Alice and Bob have same amount of money");

	}
}

float flatChange(float flat) {
	flat *= 1.05;
	return flat;
}