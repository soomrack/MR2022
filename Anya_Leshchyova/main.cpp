#include <iostream>
#include <stdio.h>

int main() {
    int beginning=1000000; // начальный капитал
    int beginning_contribution=300000; // начальная выплата по ипотеке
    int flat=6000000; // стоимость квартиры
    int income =150000; // доходы
    int expenses = 10000;  // расходы Боба
    int expenses2 = 40000; // расходы Алисы
    int time=20*12; // время на погашение ипотеки
    int a=beginning -beginning_contribution; // остаток Боба
    int b=beginning;
    int Bob, Alice;
    int monthly_payment= ((flat +flat*0.08)/ (time)) ; // стоим. кв. плюс проценты по ипотеке и поделим на месяцы
    int k=1, f=0; // вспомогательный счётчик
    printf( "Bob's calculations \n");
    for (int i=1; i<=time; i++) { // расчёт идёт по месяцам
        Bob = (a+(income)-(expenses) -(monthly_payment));
        a= Bob;
        if ( i > 3*12) {
            Bob= a*1.08;
        }                        // после трёх лет процент на вклад увеличился
        else {
            Bob=a*1.06;
        }                         // до трёх лет
        //printf ("Year%d  Bob= %d\n", k, Bob );
        if ( i/12==k) {   // результат выводится по прошедствию года
             printf ("                                  Year%d  Bob's Capital= %d\n", k, Bob );
            k =k+1;
        }
    }
    k=1;
    printf( "Alice's calculations \n");
    for (int j=1; j<=time; j++) {
        Alice = (b  + (income ) - (expenses2));
        b=Alice;
        if (j > 3*12) {
            Alice = (b*1.08);
        } else {
            Alice = (b* 1.06);
        }
       // printf (" Alice= %d\n", b );
        if (j / 12 == k) {   // результат выводится по прошедствию года
            printf("                                  Year%d  Alice's Capital= %d\n", k, Alice);
            k = k + 1;
            flat = flat *1.05; // каждый год квартира дорожает на 5%
        }
        if (Alice>= flat and f==0  ) {
            f=k;
        }
    }
    if (Bob >0){
        printf ("Bob paid off the mortgage \n");
    }
    printf ("Alice bought an apartment for %d years \n", f);
    printf ("Bob's Final Capital= %d\n", Bob);
    printf ("Alice's Final Capitale= %d\n", Alice );
    return 0;
}

