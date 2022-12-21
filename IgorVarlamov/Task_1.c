#include <stdio.h>


int main()
{
	int price;
	double rate = 5;
	double rate_ip = 8;
	int term = 239;
	
	printf("Price of house : ");
	scanf_s("%d", &price);
	printf("\n \n");

	int first_pay_Bob = 300000;
	int pay_from_month_Bob = ((price - first_pay_Bob) * ((rate_ip / 100) + 1)/240) * 1.0007;
	printf("Pay from mouth : %d \n \n", pay_from_month_Bob);
	
	int BREAK = 1;
	int BREAK_1 = 1;
	int BREAK_2 = 1;
	int start_capital_Bob = 1000000;
	int start_capital_Alice = 1000000;
	int rent_Bob = 10000;
	int rent_Alice = 40000;
	int salary_Bob = 150000;
	int salary_Alice = 150000;

	if (pay_from_month_Bob > rent_Bob + salary_Bob)
	{
		printf("Bob must choose a cheaper house \n");
		BREAK = 1;
	
	}
	else
	{
		BREAK = 0;
	}

	int save_Bob = start_capital_Bob;
	int save_Alice = start_capital_Alice;
	int remain_Bob = price * ((rate_ip / 100) + 1) - first_pay_Bob;
	int remain_Alice = price;

	printf("Remain %d from Bob \n", remain_Bob);

	if (BREAK != 1)
	{
		for (int i = 0; i <= term; i++)
		{
			if (i == 35)
			{
				rate = 6;
			}
			
			int Interest_Bob = ((save_Bob * ((rate / 100) + 1)) - save_Bob) / 12;
			save_Bob = save_Bob + ((save_Bob * ((rate / 100) + 1)) - save_Bob) / 12;
			save_Bob = save_Bob + salary_Bob;
			remain_Bob = remain_Bob - pay_from_month_Bob;
			save_Bob = save_Bob - pay_from_month_Bob - rent_Bob;
			

			printf("After %d month left %d from Bob \n", i + 1, save_Bob);
			printf("Remain %d from Bob \n", remain_Bob);
			printf("Interest from the deposit Bob: %d \n \n", Interest_Bob);

			int Interest_Alice;

			if (save_Alice < price && BREAK_2 == 1)
			{
				Interest_Alice = ((save_Alice * ((rate / 100) + 1)) - save_Alice) / 12;
				save_Alice = save_Alice + Interest_Alice + salary_Alice - rent_Alice;


				printf("After %d month left %d from Alice \n", i + 1, save_Alice);
				printf("Interest from the deposit Alice: %d \n \n \n", Interest_Alice);
			}
			else if (save_Alice >= price && BREAK_2 == 1 )
			{
				printf("Alice buy a house \n");
				save_Alice = save_Alice - price;
				BREAK_1 = 0;
				BREAK_2 = 0;
			}

			if (BREAK_1 == 0)
			{
				Interest_Alice = ((save_Alice * ((rate / 100) + 1)) - save_Alice) / 12;
				save_Alice = save_Alice + Interest_Alice + salary_Alice - rent_Alice;
				printf("Alice has already bought a house \n");
			}
		}

		if (remain_Bob < 0)
		{
			remain_Bob = remain_Bob * -1;
			save_Bob = save_Bob + remain_Bob;
		}
		else
		{
			save_Bob = save_Bob - remain_Bob;
		}


		printf("Save Alice == %d \n", save_Alice);
		printf("Save Bob == %d \n \n", save_Bob);

		if (save_Alice > save_Bob)
		{
			printf("Alice saved up %d rubles more than a bean in 20 years \n", save_Alice - save_Bob);

		}
		else
		{
			printf("Bob saved up %d rubles more than a bean in 20 years \n", save_Bob - save_Alice);
		}
	}
}
