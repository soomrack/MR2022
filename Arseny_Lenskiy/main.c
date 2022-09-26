#include <stdio.h>
#include <math.h>

int a_bank = 1000000;
int b_bank = 1000000;
int vklad = 300000;
int komunalka_a = 40000, komunalka_b = 10000;
int plateg = 26056;
int stoimost_kv_b = 3000000;
int doxod = 150000;
int srok = 20;
int mec = 20*12;
double stavka_vklad = 0.1;
int itogo;
int chist;
int percent;
int yearitog_a, yearitog_b;
int cent_a,cent_b;
int celoe_a,celoe_b;


int main () {

    // Alice
    printf("Alice");
    printf("\n");
    int i;
    for (i = 1; i <= srok; i++)
    {
        itogo=(doxod-komunalka_a)*12;
        chist = itogo+(double)a_bank;
        percent = chist * stavka_vklad;
        yearitog_a=percent+chist;
        a_bank=(int)yearitog_a;
        cent_a = modf(yearitog_a, &celoe_a);
        printf("%.f",celoe_a);
        printf(" Rub    ");
        printf("%d", (int)(100*cent_a));
        printf(" Cents    Year - ");
        printf("%0.2d", i);
        printf("\n");
    }

    // BOB
    printf("\n");
    printf("Bob");
    printf("\n");
    b_bank=b_bank-vklad;
    for (i = 1; i <= srok; i++)
    {
        if (i<=srok-1)
        {
            itogo = (doxod - komunalka_b - plateg) * 12;
            chist = itogo + (double) b_bank;
            percent = chist * stavka_vklad;
            yearitog_b = percent + chist;
            b_bank = (int) yearitog_b;
            cent_b = modf(yearitog_b, &celoe_b);
            printf("%.f", celoe_b);
            printf(" Rub    ");
            printf("%d", (int) (100 * cent_b));
            printf(" Cents    Year - ");
            printf("%0.2d", i);
            printf("\n");
        }
        else
        {itogo = (doxod - komunalka_b - plateg) * 12;
            chist = itogo + (double) b_bank;
            percent = chist * stavka_vklad;
            yearitog_b = percent + chist;
            b_bank = (int) yearitog_b;
            cent_b = modf(yearitog_b, &celoe_b);
            printf("%.f", celoe_b+stoimost_kv_b);
            printf(" Rub    ");
            printf("%d", (int) (100 * cent_b));
            printf(" Cents    Year - ");
            printf("%0.2d", i);
            printf("\n");}
    }
}