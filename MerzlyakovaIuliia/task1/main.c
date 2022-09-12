#include <stdio.h>

#define DEB_PERCENT 0.08
#define SAL_ALICE 150000.0
#define SAL_BOB 150000.0
#define COMM_ALICE 40000.0
#define COMM_BOB 10000.0
#define OVERALL_TIME 20
#define DEPOSIT 300000

int main() {
    float bankAlice = 1000000, bankBob = 1000000;
    bankBob -= DEPOSIT;

    for(int i = 0; i < OVERALL_TIME; i++)
    {
        bankAlice += SAL_ALICE - COMM_ALICE;
        bankAlice += bankAlice * DEB_PERCENT;
        bankBob += SAL_BOB - COMM_BOB;
        bankBob += bankBob * DEB_PERCENT;
    }

    printf("Alice's money: %f\n", bankAlice);
    printf("Bob's money: %f\n", bankBob);

    if(bankAlice>bankBob) printf("Alice has more money %f\n");
    else printf("\nBob has more money %f\n");

   // printf("Hello, World!\n");
    return 0;
}
