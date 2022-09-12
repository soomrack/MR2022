#include <stdio.h>

int main( )
{
    unsigned long long int bank_a=100000000; //начальный капитал А
    unsigned long long int nach_b=100000000; //начальный капитал B
    int pv_b=30000000; //первый взнос В
    unsigned long long int dox=15000000; //Доход каждого
    int trat_a=4000000; //Траты А
    int trat_b=1000000; //Траты В
    unsigned long long int plat_b=5000000; //Платеж по ипотеке В
    int flat=700000000; //стоимость квартиры
    double stavka=0.08; //Ставка по вкладу
    unsigned long long int itog_a; //Итог А
    unsigned long long int itog_b; //Итог В

    unsigned long long int bank_b=nach_b-pv_b;
for (int year=1; year<=20; year++){
    for (int month=1; month<=12; month++){
        if (year>=4){
            stavka=0.10;
        }
        bank_a=(unsigned long long int)((bank_a+dox-trat_a)*(1.f+stavka/12));
        bank_b=(unsigned long long int)(bank_b+dox-trat_b-plat_b)*(1.f+stavka/12);
    }
    itog_a=bank_a;
    itog_b=(bank_b+flat);
    printf("%d year: ", year);
    printf("Alice = %d.%d ",(unsigned long long int ) itog_a/100,(unsigned long long int )itog_a%100);
    printf("Bob = %d.%d\n",(unsigned long long int ) itog_b/100, (unsigned long long int )itog_b%100);
}
    return 0;
}
