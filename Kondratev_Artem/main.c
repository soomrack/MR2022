#include <stdio.h>
#include <stdint.h>

int main()
    {
    int year = 22;  // количество лет, на которые взята ипотека
    double cr_percent = 8.0;  // процент ипотеки
    double dep_percent = 0.2;
    int flat_cost = (int)(9000000.32 * 100);  // стоимость квартиры
    int start = (int)(1000000.15 * 100);  // массив стартовый капитал
    int first_pay = (int)(300000.08 * 100);  // первый взнос
    int salary = (int)(150000.56 * 100);  // зарплата
    int a_com_pay = (int)(40000.14 * 100);  // коммунальные услуги Alice
    int b_com_pay = (int)(10000.02 * 100);  // коммунальные услуги Bob
    int month_deposit = (int)(70000.16 * 100);  // ежемесячные отчисления на вклад
    int64_t deposit, year_payment, year_deposit;
    long double delta_deposit, month_payment, flat_taxes;


    int64_t a_balance = start;  // активы Alice после покупки Bob квартиры
    long double a_balance_out = (double)a_balance / 100;

    int64_t b_balance = start + flat_cost - first_pay;  // активы Bob после покупки квартиры
    long double b_balance_out = (double)b_balance / 100;

    long double dif = b_balance_out - a_balance_out;
    int64_t rest = flat_cost - first_pay;  // оставшаяся задолженность Bob

    long double credit_payment = (flat_cost - first_pay) / (year * 12.0);  // фиксированная часть ежемесячной выплаты
    if(credit_payment - (int)credit_payment > 0)
        credit_payment = (int)credit_payment + 1;


    // вывод активов после покупки Bob квартиры:
    printf("  Year\t\t\tAlice\t\t  Bob\t\t\t\tDif\n");
    printf("year %2d: ", 0);
    printf("%14.2Lf%14.2Lf ", a_balance_out, b_balance_out);
    printf("  dif = %14.2Lf\n", dif);


    for (int i = 1; i <= year; i++)
    {
        if(i == 3)
            cr_percent = 13.0;

        if(i == 5)
            b_balance += 150000000;

        if(i == 7)
            salary = 5000000;

        year_payment = 0;
        year_deposit = 0;

        flat_taxes = flat_cost * 0.5 / 100;
        if(flat_taxes - (int)flat_taxes > 0)
            flat_taxes = (int)flat_taxes + 1;

        for(int j = 0; j < 12; j++)
        {
            month_payment = credit_payment + (double)rest * cr_percent / 100;
            if(month_payment - (int)month_payment > 0)
                month_payment = (int)month_payment + 1;

            year_payment += (int)month_payment;
            rest -= (int)month_payment;

            delta_deposit = month_deposit + (double)deposit * dep_percent / 100;
            if(delta_deposit - (int)delta_deposit > 0)
                delta_deposit = (int)delta_deposit + 1;
            deposit += (int)delta_deposit;
            year_deposit += (int)delta_deposit;
        }

        b_balance += (salary - b_com_pay - (int)flat_taxes) * 12 - year_payment + year_deposit;
        b_balance_out = (double)b_balance / 100;

        a_balance += (salary - a_com_pay) * 12 + year_deposit;
        a_balance_out = (double)a_balance / 100;

        dif = b_balance_out - a_balance_out;


        printf("year %2d: ", i);
        printf("%14.2Lf%14.2Lf ", a_balance_out, b_balance_out);
        printf("  dif = %14.2Lf\n", dif);
    }
    return 0;
    }
