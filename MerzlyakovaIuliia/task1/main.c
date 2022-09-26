#include <stdio.h>

#define DEB_PERCENT 0.08
#define SAL_ALICE 150000.0
#define SAL_BOB 150000.0
#define BOB_FLAT_PAYMENT 100000.0
#define COMM_ALICE 40000.0
#define COMM_BOB 10000.0
#define OVERALL_TIME 20
#define DEPOSIT 300000
#define FLAT_INCREACE_ONCE_YEAR 1,5

int main()
{
    float bankAlice = 1000000, bankBob = 1000000;
    bankBob -= DEPOSIT;

    for(int i = 0; i < (OVERALL_TIME*12); i++)
    {
        static int bobPayment = BOB_FLAT_PAYMENT;
        //bankAlice += SAL_ALICE - COMM_ALICE;
        bankAlice += bankAlice * (DEB_PERCENT/12);
        bankBob += SAL_BOB - (COMM_BOB + bobPayment);
        bankBob += bankBob * (DEB_PERCENT/12);
        if (i == 48)
        {
            bobPayment += bobPayment*(FLAT_INCREACE_ONCE_YEAR/12);
        }
    }

    printf("Alice's money: %f\n", bankAlice);
    printf("Bob's money: %f\n", bankBob);

    if(bankAlice>bankBob)
        printf("\nAlice has more money\n");
    else
        printf("\nBob has more money\n");

    return 0;
}
