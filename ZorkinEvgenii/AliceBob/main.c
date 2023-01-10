#include <stdio.h>   // подключение стандартной библиотеки
#include <stdlib.h>  // подключение доп библиотеки с функциями для выделения памяти
#include <malloc.h>  // подключение доп бибилиотеки под динамич. память однако по идее данный заголовок есть в библиотеке выше

const int Total_m = 12*25;  // введение глобальной переменной под общее кол-во времени с разбивкой на месяцы

typedef struct {                             // СОЗДАНИЕ СТРУКТУРЫ ДЛЯ ПЕРСОН (Алиса и Боб)
    char *name;                              // имя клиента
    unsigned long long int bank;             // банк счет клиента
    unsigned long long int zp;               // все доходы клиента
    unsigned long long int rashod;           // все расходы клиента
    unsigned long long int komun;            // расходы за комунальные тарифы

    unsigned long long int mortgage;         // оплата по ипотеке
    unsigned long long int pv;               // 1 взнос по ипотеке
    unsigned long long int price_kv;         // стоимость квартиры

    unsigned long long int arenda_kv;        // стоимость аренды
    float dep_rate;                          // ставка по вкладу для клиента

    unsigned long long int bank_rubls;       // вывод счета в рублях
    unsigned long long int bank_cops;        // вывод счета в копейках


} Person;

void Alice( Person *alice){        // создание функции с исп структуры для Алисы
    alice->name = malloc(6);
    alice->name = "Alice";
    alice->bank = 1*1000*1000*100;
    alice->dep_rate = 0.09;
    alice->arenda_kv = 20 * 1000*100;
    alice->zp = 90*1000*100;
    alice->komun = 8*1000*100;

    alice->price_kv = 0;
    alice->mortgage = 0;
    alice->pv = 0;

}

void Bob(struct Person *bob){           // создание функции с исп структуры для Боба
    bob->name = malloc(4);
    bob->name = "Bob";
    bob->bank = 1*1000*1000*100;
    bob->zp = 90*1000*100;
    bob->komun = 8*1000*100;
    bob->price_kv = 9*1000*1000*100;
    bob->mortgage = 60*1000*100;
    bob->pv = 500*1000*100;

    bob->dep_rate = 0;
    bob->arenda_kv = 0;

}

void per_vznos(struct Person *client){              // создание функции первоначального взноса через структуру
    client->bank -= client->pv;                     // a = a + b  то же самое   a += b
}

void prihod_zp(struct Person *client){              // создание функции получение зп через структуру
    client->bank += client->zp;
}

void komun_rash(struct Person *client) {            // создание функции по комунальным расходам
    client->bank -= client->komun;
}

void arenda(struct Person *client){                 // создание функции по аренде
    client->bank -= client->arenda_kv;
}

void ipoteka_rash(struct Person *client) {          // создание функции по ипотечному платежжу
    client->bank -= client->mortgage;
}

void prihod_dep_rate(struct Person *client) {       // создание функции начисления процентов по вкладу
    client->bank = (unsigned long long int)(client->dep_rate/12.0+1.0)*client->bank;
}

void bank_cel_rub(struct Person *client) {
    client->bank_rubls = client->bank/100 + client->price_kv/100;
}

void bank_kopeik(struct Person *client) {
    client->bank_cops = client->bank%100 + client->price_kv%100;
}

/* введение какой либо динамики (начало)

void pov_kv(struct Person *client) {
    client->price_kv *= (unsigned long long int) 1.02;
} */
//  конец динамических процессов

void print_result(struct Person *client1, struct Person *client2) {       // функция для вывода результата
    printf("Person name: %s, Total property %llu rub and %llu kopeek\n", client1->name,client1->bank / 100, client1->bank % 100);
    printf("Person name: %s, Total property %llu rub and %llu kopeek\n", client2->name,client2->bank / 100 + client2->price_kv / 100, client2->bank % 100 + client2->price_kv % 100);


    if (client1->bank > (client2->bank + client2->price_kv)) {
        printf("%s plan is more profit than %s\n", client1->name, client2->name);
    } else if ((client2->bank + client2->price_kv) > client1->bank) {
        printf("%s plan is more profit than %s\n", client2->name, client1->name);
    } else {
        printf("Savings of both clients are equal\n");
    }
}


void simul () {

    struct Person alice;
    struct Person bob;
    Alice(&alice);
    Bob(&bob);

    for (int month = 1; month <= Total_m; month ++) {

        per_vznos(&alice);
        per_vznos(&bob);

        prihod_zp(&alice);
        prihod_zp(&bob);

        komun_rash(&alice);
        komun_rash(&bob);

        arenda(&alice);
        arenda(&bob);

        ipoteka_rash(&alice);
        ipoteka_rash(&bob);

        prihod_dep_rate(&alice);
        prihod_dep_rate(&bob);

        bank_cel_rub(&alice);
        bank_kopeik(&bob);

        if (month % 12 == 0) {
            print_result(&alice, &bob);
            printf("%d year\n", month / 12);
        }

        /*bank_cel_rub(&alice);
        bank_cel_rub(&bob);
        bank_kopeik(&alice);
        bank_kopeik(&bob);*/
    }
}


int main () {
    simul(); // вызов функции симуляции
    return 0;
}