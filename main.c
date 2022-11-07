#include <stdio.h>
#include <math.h>

unsigned long long int a_bank = 100000000;
unsigned long long int b_bank = 100000000;
int vklad = 30000000;
int komunalka_a = 4000000, komunalka_b = 1000000;
int plateg = 2605600;
int stoimost_kv_b = 3000000;
int doxod = 15000000;
char srok = 20;
int mec = 20*12;
double stavka_vklad = 0.1;
unsigned long long int itogo;
unsigned long long int chist;
unsigned long long int percent;
unsigned long long int yearitog_a, yearitog_b;
unsigned long long int cent_a,cent_b;
unsigned long long int celoe_a,celoe_b;


int main () {

    // Alice
    printf("Alice");
    printf("\n");
    char i;
    for (i = 1; i <= srok; i++)
    {
        for (mec=1; mec<=12; mec++)
        {
            a_bank = (unsigned long long int)(a_bank+doxod-komunalka_a)*(1.f+stavka_vklad/12);
        }

        printf("%llu",a_bank/100);
        printf(" Rub    ");
        printf("%llu%llu", a_bank %100 /10, a_bank %100 %10 );
        printf(" Cents    Year - ");
        printf("%0.2d", i);
        printf("\n");
    }



    // Bob
    printf("\n");
    printf("Bob");
    printf("\n");
    b_bank=b_bank-vklad;
    for (i = 1; i <= srok; i++)
    {
        for (mec = 1; mec <= 12; mec++) {
            b_bank = (unsigned long long int) (b_bank + doxod - komunalka_b-plateg) * (1.f + stavka_vklad / 12);
        }

        printf("%llu", b_bank/100 + stoimost_kv_b);
        printf(" Rub    ");
        printf("%llu%llu", b_bank % 100 / 10, b_bank % 100 % 10);
        printf(" Cents    Year - ");
        printf("%0.2d", i);
        printf("\n");
    }

    // BOB

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