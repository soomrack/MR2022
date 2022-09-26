#include <stdio.h>

const int MONTH_NUMBER = 12 * 20;

struct Client
{
  char *name;
  long long account_balance;
  long long salary;
  long long house_value;
  double bank_deposit_percent;
  long long monthly_arenda_payments;
  long long monthly_house_bills;
  long long monthly_mortgage_payments;
};
struct Client Alice, Bob;

void aliceInit(struct Client *alice)
{
  alice->name = "Alice";
  alice->account_balance = 1000 * 1000 * 100;
  alice->salary = 150 * 1000 * 100;
  alice->house_value = 0;
  alice->bank_deposit_percent = 0.015;
  alice->monthly_arenda_payments = 40 * 1000 * 100;
  alice->monthly_house_bills = 10 * 1000 * 100;
  alice->monthly_mortgage_payments = 0;
}

void bobInit(struct Client *bob)
{
  bob->name = "Bob";
  bob->account_balance = 1000 * 1000 * 100;
  bob->salary = 150 * 1000 * 100;
  bob->house_value = 4 * 1000 * 1000 * 100;
  bob->bank_deposit_percent = 0.015;
  bob->monthly_arenda_payments = 0;
  bob->monthly_house_bills = 10 * 1000 * 100;
  bob->monthly_mortgage_payments = 51480 * 100;
}

void outClient(const struct Client *client)
{
  printf("%s: %lld,%lld", client->name, (client->account_balance + client->house_value) / 100,
         client->account_balance % 100);
}

void printResult(const struct Client *alice, const struct Client *bob, int month)
{
  if (month % 12 == 0)
  {
    printf("%d) \t", month / 12);
    outClient(alice);
    printf("\t");
    outClient(bob);
    printf("\n");
  }
}

void deposit_increase(struct Client *client)
{
  client->bank_deposit_percent *= 1.25;
}

void flat_cost_increase(struct Client *client)
{
  client->house_value *= 1.5;
}

void salary_rate_return(struct Client *client)
{
  client->salary = 150 * 1000 * 100;
}

void salary_decrease(struct Client *client)
{
  client->salary /= 1.5;
}

void bank_account_increase(struct Client *client)
{
  client->account_balance += (long long) (client->account_balance * client->bank_deposit_percent / 12 -
                                          client->monthly_mortgage_payments - client->monthly_house_bills -
                                          client->monthly_arenda_payments + client->salary);
}

int main()
{
  aliceInit(&Alice);
  bobInit(&Bob);

  for (int month = 1; month <= MONTH_NUMBER; month++)
  {
    if (month == 3 * 12)
    {
      deposit_increase(&Alice);
      deposit_increase(&Bob);
    }

    // Рост цен на недвижимость на 5-ый год
    if (month == 5 * 12)
    {
      flat_cost_increase(&Alice);
      flat_cost_increase(&Bob);
    }

    // Уменьшение дохода на через 10 лет на срок в 6 лет
    if (month == 10 * 12)
    {
      salary_decrease(&Alice);
      salary_decrease(&Bob);
    }
    if (month == 16 * 12)
    {
      salary_rate_return(&Alice);
      salary_rate_return(&Bob);
    }
    bank_account_increase(&Alice);
    bank_account_increase(&Bob);
    printResult(&Alice, &Bob, month);
  }
}