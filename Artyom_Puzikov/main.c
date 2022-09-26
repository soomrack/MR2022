#include <stdio.h>

int main()
{
    long long expensesA = 4000000, salaryA = 15000000, salaryB = 15000000, expensesB = 1000000, downpayment = 60000000, flat = 400000000, monthly_payment = 5148000;
    double deposit = 0.00125;
    long long resultA = 100000000, contributionA = 0, moneyA = 100000000, resultB = 100000000 - downpayment,
    moneyB = 100000000, contributionB = 0, cadastrFlat = flat/1.5, cadastrTax = 0.01*cadastrFlat;
    for (int i = 1; i <= 20 * 12; i++)
    {
        if (i > 3 * 12)
        {
            deposit = 0.00167;
        }

        // Рост цен на недвижимость на 5-ый год
        if (i == 5 * 12) {
            flat *= 1.5;
        }

        // Уменьшение дохода Алисы на через 10 лет на срок в 6 лет
        if (i == 10*12) {
            salaryA /= 1.5;
        }
        if (i == 16*12) {
            salaryA *= 1.5;
        }

        resultA = (long long) (resultA + ((salaryA - expensesA) + deposit * contributionA));
        moneyA += salaryA - expensesA;
        contributionA += (long long) (moneyA + contributionA * deposit);
        moneyA = 0;

        resultB = (long long) (resultB + ((salaryB - expensesA - monthly_payment - cadastrTax) + deposit * contributionB));
        moneyB += salaryB - expensesB - monthly_payment;
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