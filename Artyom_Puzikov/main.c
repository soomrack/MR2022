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

void initClient(struct Client *client, char *name,
                long long account_balance,
                long long salary,
                long long house_value,
                double bank_deposit_percent,
                long long monthly_arenda_payments,
                long long monthly_house_bills,
                long long monthly_mortgage_payments)
{
  client->name = name;
  client->account_balance = account_balance;
  client->salary = salary;
  client->house_value = house_value;
  client->bank_deposit_percent = bank_deposit_percent;
  client->monthly_arenda_payments = monthly_arenda_payments;
  client->monthly_house_bills = monthly_house_bills;
  client->monthly_mortgage_payments = monthly_mortgage_payments;
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
  initClient(&Alice, "Alice", 1000 * 1000 * 100, 150 * 1000 * 100, 0, 0.015, 40 * 1000 * 100, 10 * 1000 * 100, 0);
  initClient(&Bob, "Bob", 1000 * 1000 * 100, 150 * 1000 * 100,  4 * 1000 * 1000 * 100, 0.015, 0, 10 * 1000 * 100, 51480 * 100);

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