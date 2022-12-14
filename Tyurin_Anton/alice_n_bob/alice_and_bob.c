#include <stdio.h>
#include <stdint.h>

int main() {
    int year = 20;  // количество лет, на которые взята ипотека
    double cr_percent = 8.0;  // процент ипотеки
    double dep_percent = 6 / 12;
    int flat_cost = (int)(9000000 * 100);  // стоимость квартиры
    int start = (int)(1000000 * 100);  // массив стартовый капитал
    int first_pay = (int)(300000 * 100);  // первый взнос
    int a_salary = (int)(150000 * 100);  // зарплата Alice
    int b_salary = (int)(150000 * 100);  // зарплата Bob
    int a_com_pay = (int)(40000 * 100);  // коммунальные услуги Alice
    int b_com_pay = (int)(10000 * 100);  // коммунальные услуги Bob
    int month_deposit = (int)(70000 * 100);  // ежемесячные отчисления на вклад
    long double deposit, year_payment, year_deposit,delta_deposit, month_payment,taxes;

    long double a_balance = start;  // активы Alice после покупки Bob квартиры
    long double a_balance_out = (double)a_balance / 100;

    long double b_balance = start + flat_cost - first_pay;  // активы Bob после покупки квартиры
    long double b_balance_out = (double)b_balance / 100;

    long double dif = b_balance_out - a_balance_out;
    long double rest = flat_cost - first_pay;  // оставшаяся задолженность Bob

    long double credit_payment = (flat_cost - first_pay) / (year * 12.0);  // фиксированная часть ежемесячной выплаты
    if(credit_payment - (int)credit_payment > 0)
        credit_payment = (int)credit_payment + 1;


    // вывод активов после покупки Bob квартиры:
    printf("Year|\t  Alice\t\t|\tBob\t| Difference|\n");
    printf("%-4d|\t",0);
    printf(" %10.2Lf\t|  %10.2Lf\t|", a_balance_out, b_balance_out);
    printf(" %10.2Lf|\t\n", dif);


    for (int i = 1; i <= year; i++)
    {
        if(i == 3)
        {
            cr_percent = 12;
        }

        year_payment = 0;
        year_deposit = 0;

        if(i==5)
        {
            b_balance+=flat_cost*0.5;
        }
        if(i==10)
        {
            b_salary-=5000000;
        }
        taxes=(double)flat_cost*(0.5/100);

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

        b_balance += (b_salary - b_com_pay) * 12 - taxes - year_payment + year_deposit;
        b_balance_out = (double)b_balance / 100;

        a_balance += (a_salary - a_com_pay) * 12 + year_deposit;
        a_balance_out = (double)a_balance / 100;

        dif = b_balance_out - a_balance_out;


        printf("%-4d|\t", i);
        printf(" %10.2Lf\t|  %10.2Lf\t| ", a_balance_out, b_balance_out);
        printf("%10.2Lf|\t\n", dif);
    }
    return 0;
}

