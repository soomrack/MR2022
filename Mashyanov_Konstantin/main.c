#include <stdio.h>

int main() {
    long int income, first_payment=30000000 ; //доходы, перв_платёж в копейках
    unsigned long long int bankA=100000000, bankB=100000000;
    int installment=5000000, utilitiesA=4000000,utilitiesB=1000000;// еж.взнос, ЖКХ
    long int price=600000000; //ст.квартиры
    float stake=0.07;// ставка по вкладу
    bankB -= first_payment;
    scanf ("Print sum of income %lu",&income);
    for(char year=1;year<=20;year++)   {
        for(char month=1;month<=12;month++) {
            bankA = (bankA + income - utilitiesA) * (1.f + stake / 12); //Alice
            bankB = (bankB + income - installment - utilitiesB) * (1.f + stake / 12); //Bob
        }
        printf("Alice's actives %llu\n Bob's actives %llu\n",bankA,bankB);
        printf("Current years - %d",year);}
    return 0;
}
