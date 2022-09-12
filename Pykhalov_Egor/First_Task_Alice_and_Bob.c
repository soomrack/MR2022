#include <stdio.h>
#include <math.h>                                                           //Подключаем библиотеку для математических операций

#define K 0

int main() {

    int start_kap = 1000000,                                                //Объявляем целичисленные переменные
        perv_vznos = 300000,
        KommB = 10000,
        KommA = 40000,
        dohod = 150000,
        T=20,
        t_pov = 3,
        i,
        b;

    double
        ProcentKred = 0.12,
        ProcentVklad = 0.06,
        Dbvk = 0.06,
        PM = ProcentKred / 12,                                                          //Объявляем переменные с плавающей точкой
        PV = ProcentVklad / 12,
        PV1 = (ProcentVklad + Dbvk) / 12;

    printf( "\n"                                                     //Выводим начальную информацию
                "Bob\n"
                "\n"
                "Nachal'nyi kapital: %d\n"
                "Pervyi vznos: %d\n"
                "Kommunal'nye platezhi: %d\n"
                "Dohod: %d\n"
                "\n"
                "Alice\n"
                "\n"
                "Nachal'nyi kapital: %d\n"
                "Pervyi vznos: - \n"
                "Kommunal'nye platezhi: %d\n"
                "Dohod: %d\n"
                "\n"
                "Srok: %d\n"

                ,start_kap, perv_vznos, KommB, dohod, start_kap, KommA, dohod, T );


    int st_kv = perv_vznos*10;                                              //Высчитываем стоимость квартиры (Первый взнос - 10 процентов от стоимости)
            printf("Stoimost' kvartiry: %d\n", st_kv);


    double Platezh = (st_kv*PM)/(1-pow((1+PM),(-T*12)));              //Высчитываем аннуитентный ежемесячный платеж по формуле
            printf("Platezh: %lf\n", Platezh);


    double Vklad = start_kap-perv_vznos;                                    //Начальные суммы вкладов у Боба и Элис соответственно
    double VkladA = start_kap;

    printf("Vklad v nachale: %lf\n", Vklad);                         //Высчитываем ежемесячный баланс вклада у Боба

    if (K)
    {
        for (i = 1; i <= t_pov * 12; i++)
        {
            Vklad = Vklad + Vklad * PV;
            Vklad = Vklad + dohod - Platezh - KommB;
            printf("Vklad: %lf Spustya %d month\n", Vklad, i);
        }
        printf("Stavka povysilas': %lf\n", PV1);
        for (i = 1; i <= ((T-t_pov)*12); i++)
        {
            Vklad = Vklad + Vklad * PV1;
            Vklad = Vklad + dohod - Platezh - KommB;
            printf("Vklad: %lf Spustya %d month\n", Vklad, i);
        }
    }
    else
    {
        for (i = 1; i <= T * 12; i++)
        {
            Vklad = Vklad + Vklad * PV;
            Vklad = Vklad + dohod - Platezh - KommB;
            printf("Vklad: %lf Spustya %d month\n", Vklad, i);
        }
    }


    printf ("\nVklad v nachale: %lf\n", VkladA);                     //Высчитываем ежемесячный баланс вклада у Элис

    if (K)
    {
        for (i = 1; i <= t_pov * 12; i++)
        {
            VkladA = VkladA + VkladA*PV;
            VkladA = VkladA+dohod-KommA;
            printf ("Vklad: %lf Spustya %d month\n", VkladA, b);
        }
        printf("Stavka povysilas': %lf\n", PV1);
        for (i = 1; i <= ((T-t_pov)*12); i++)
        {
            VkladA = VkladA + VkladA*PV1;
            VkladA = VkladA+dohod-KommA;
            printf ("Vklad: %lf Spustya %d month\n", VkladA, b);
        }
    }
    else
    {
        for (i = 1; i <= T * 12; i++)
        {
            VkladA = VkladA + VkladA*PV;
            VkladA = VkladA+dohod-KommA;
            printf ("Vklad: %lf Spustya %d month\n", VkladA, b);
        }
    }


    double SAl = VkladA;                                                   //Считаем суммы имеющихся средств у каждого и выводим
    printf ("\n\nSumma Alice: %lf ", SAl);

    double SBoba = st_kv + Vklad;
    printf("\n\nSumma Boba: %lf\n", SBoba);

}
