#include <stdio.h>

int main()
{
  long long expensesA = 4000000, salary = 15000000, expensesB = 1000000, downpayment = 60000000, flat = 400000000, monthly_payment = 5148000;
  double deposit = 0.00125;
  long long resultA = 100000000, contributionA = 0, moneyA = 100000000, resultB =
    100000000 - downpayment, moneyB = 100000000,
    contributionB = 0;
  for (int i = 1; i <= 20 * 12; i++)
  {
    if (i > 3 * 12)
    {
      deposit = 0.00167;
    }
    resultA = (long long) (resultA + ((salary - expensesA) + deposit * contributionA));
    moneyA += salary - expensesA;
    contributionA += (long long) (moneyA + contributionA * deposit);
    moneyA = 0;

    resultB = (long long) (resultB + ((salary - expensesA - monthly_payment) + deposit * contributionB));
    moneyB += salary - expensesB - monthly_payment;
    contributionB += (long long) (moneyB + contributionB * deposit);
    moneyB = 0;

    if (i % 12 == 0)
    {
      printf("%d) \t", i / 12);
      printf("Alice: %lld,%lld\t", resultA / 100, resultA % 100);
      printf("Bob: %lld,%lld\n", (resultB + flat) / 100, resultB % 100);
    }
  }
  return 0;
}