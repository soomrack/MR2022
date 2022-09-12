#include <stdio.h>

int main()
{
  int expensesA = 40000, salary = 150000, expensesB = 10000, downpayment = 600000, flat = 4000000, monthly_payment = 51480;
  double deposit = 0.00125, resultA = 1000000, contributionA = 0.0, moneyA = 1000000, resultB = 1000000 - downpayment,
    moneyB = 1000000, contributionB = 0.0;
  for (int i = 1; i <= 20 * 12; i++)
  {
    if (i > 3 * 12){
      deposit = 0.00167;
    }
    resultA = resultA + ((salary - expensesA) + deposit * contributionA);
    moneyA += salary - expensesA;
    contributionA += moneyA + contributionA * deposit;
    moneyA = 0;

    resultB = resultB + ((salary - expensesA - monthly_payment) + deposit * contributionB);
    moneyB += salary - expensesB - monthly_payment;
    contributionB += moneyB + contributionB * deposit;
    moneyB = 0;

    if (i % 12 == 0)
    {
      printf("%d) \t", i / 12);
      printf("Alice: %f\t", resultA);
      printf("Bob: %f\n", resultB + flat);
    }
  }
  return 0;
}