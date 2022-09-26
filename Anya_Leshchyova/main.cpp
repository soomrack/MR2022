#include <iostream>


// функция считает ежемесячный платёж
double monthly_payment_F (double beginning,double beginning_contribution,double flat, int time_month,
                          double percent_mortgages) {

    double monthly_payment = ((flat + flat * percent_mortgages)/ (time_month)); // вычисление ежемеячного платежа
    return monthly_payment;
}
//считает ипотеку и вклад
void ipoteka_and_deposit( int beginning,int beginning_contribution, int time_month, int expenses,int income,
                          int  monthly_payment,int deposit_interest,int percentage_increase, int time_year, int flat) {

    int k = 1, h=0;
    long double a = 0;

    if (monthly_payment != 0) { // ипотека
        printf("\nMortgage calculator for %d years\n",time_year);

        int residue = beginning - beginning_contribution; // остаток Боба
        for (int i = 1; i <= time_month; i++) {
            a = residue - expenses + income - monthly_payment;
            residue = a;
            if (i % 12 == 0) {
                if (i / 12 >=  time_year/2) {
                    residue = a * (deposit_interest + percentage_increase);
                }
                else {
                    residue = a * deposit_interest;
                }
                printf("          Years %d Bob's Capital= %d\n", k, residue);
                k = k + 1;
            }
        }
        printf ("Monthly_payment=%d\n", monthly_payment);
        if (residue>monthly_payment*time_month){
            printf ("Congratulations! You pay off the mortgage\n");
        }
    }
    else{
        printf("\nDeposit calculator for %d years\n",time_year);
        for (int i = 1; i <= time_month; i++) {
            a = beginning - expenses + income;
            beginning = a;
            if (i % 12 == 0) {
                if (i / 12 >= time_year/2) {
                    beginning = a * (deposit_interest + percentage_increase);
                }
                else {
                    beginning = a * deposit_interest;
                }
                printf("          Years %d Alice's Capital %d\n", k, beginning);
                k = k + 1;
                if (beginning>=flat and h==0){
                    h=i/12;
                }
            }
        }
        printf("You can buy an apartment in the %d year \n", h);
    }
}


int main() {
    int beginning=1000000.00; // начальный капитал
    int beginning_contribution=500000.00; // начальная выплата по ипотеке
    int flat=15550000.00; // стоимость квартиры
    int income =150000.00; // доходы
    int expenses = 10000.00;  // расходы Боба
    int expenses2 = 40000.00; // расходы Алисы
    int time_year=20; // время на погашение ипотеки, год
    int time_month=time_year*12;// время на погашение ипотеки в месяцах
    int percent_mortgages=0.1; // процент ипотеки
    int deposit_interest=1.06; // процент вклада
    int monthly_payment; // ежемесячный платёж
    int percentage_increase=0.02; // на сколько увеличился процент по прошедствию половины времени

    monthly_payment=monthly_payment_F( beginning,beginning_contribution, flat, time_month, percent_mortgages);
    ipoteka_and_deposit( beginning, beginning_contribution,  time_month, expenses, income, monthly_payment,
                         deposit_interest,percentage_increase, time_year, flat);
    ipoteka_and_deposit( beginning, 0,  time_month, expenses2, income, 0,
                         deposit_interest,percentage_increase, time_year,flat);

    return 0;
}

