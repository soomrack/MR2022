#include <stdio.h>

int srok = 20;
double credit_rate = 10; //процент по крудиту


typedef struct Person {
    long int NK;
    long long int perviy_vznos;
    long long int ezhemes_vznos;
    long long int plata_za_kvartiru; //комуналка или аренда
    long long int dohod;
    long long int stavka_po_vkladu;
    long long int kapital;
    long long int v_bank;
} Person;


int dannieA(struct Person *Alice){
    Alice->perviy_vznos = 0;
    Alice->NK = 1 * 1000 * 1000 * 100; //копейки
    Alice->ezhemes_vznos = 0;
    Alice->plata_za_kvartiru = 40 * 1000 * 100;//копейки
    Alice->dohod = 150 * 1000 * 100;
    Alice->stavka_po_vkladu = 6;
    Alice->v_bank = 500 * 1000 * 100;
};

int dannieB(struct Person *Bob){
    Bob->perviy_vznos = 300 * 1000 * 100; //крпейки
    Bob->NK = 1 * 1000 * 1000 * 100; //копейки
    Bob->ezhemes_vznos = 700 * 1000 * 100; //копейки
    Bob->plata_za_kvartiru = 10 * 1000 * 100;//копейки
    Bob->dohod = 150 * 1000 * 100; //копейки
    Bob->stavka_po_vkladu = 6;
    Bob->v_bank = 100 * 1000 * 100;
};
int ipoteka(struct Person *Bob){
    Bob->kapital = Bob->NK - Bob->perviy_vznos;
        for (int i = 1; i <= srok; i++){
            Bob->kapital += Bob->v_bank;
            Bob->kapital *= (1.0 + Bob->stavka_po_vkladu/12.0 / 100.0);
        };
};

int vklad(struct Person *Alice){
    Alice->kapital = Alice->NK;
    for (int i = 1; i <= srok; i++){
        Alice->kapital += Alice->v_bank;
        Alice->kapital = Alice->kapital * (1.0 + Alice->stavka_po_vkladu/12.0 / 100.0);
    };
};

int main() {
    Person Alice;
    Person Bob;
    dannieA(&Alice);
    vklad(&Alice);
    dannieB(&Bob);
    ipoteka(&Bob);

    printf("Vdlad Alice = %ld; Vdlad Bob + kvartira = %ld /n", Alice.kapital, Bob.kapital);
}
