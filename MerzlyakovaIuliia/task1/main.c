#include <stdint.h>
#include <stdio.h>


#define DEB_PERCENT 0.08
#define SAL_ALICE 150000
#define SAL_BOB 150000
#define BOB_FLAT_PAYMENT 100000.0
#define COMM_ALICE 40000
#define COMM_BOB 10000
#define OVERALL_TIME 20
#define DEPOSIT 300000.0
#define FLAT_INCREACE_ANNYAL 3.2

struct persona {
    double bank;
    uint16_t salary;
    uint16_t monthly_payment;
    double flat_cost;
};

uint8_t winner(struct persona, struct persona);
float year_finals(struct persona);
void flat_increace();


struct persona Alice = {1000000.0,  SAL_ALICE,  COMM_ALICE, 0.0};
struct persona Bob = {1000000.0 - DEPOSIT,  SAL_BOB,  COMM_BOB, BOB_FLAT_PAYMENT};






int main()
{
   
    if (winner(Alice, Bob)) 
       printf("\nAlice has more money\n");
    else 
        printf("\nBob has more money\n");

    printf("Alice's money: %f\n", Alice.bank);
    printf("Bob's money: %f\n", Bob.bank);
    return 0;

}



///////// Определение у кого больше денег
uint8_t winner(struct persona p1, struct persona p2)
{
    for(int8_t i = 0; i <= OVERALL_TIME; i++)
    {
        p1.bank += year_finals(p1);
        p2.bank += year_finals(p2);
        p1.bank += p1.bank * DEB_PERCENT;
        p2.bank += p2.bank * DEB_PERCENT;
        flat_increace();
    }
    if (p1.bank > p2.bank)
        return 1;
    else 
        return 0;
}
/////////


///////// Итоги за год
float year_finals(struct persona p)
{
    for (int8_t i = 0; i < 12; i++)
    p.bank += p.salary - p.monthly_payment - p.flat_cost;
    return p.bank;
}
////////


//////// Ежегодное увеличение цены квартиры Боба
void flat_increace()
{
    Bob.flat_cost *= FLAT_INCREACE_ANNYAL;
}
////////
